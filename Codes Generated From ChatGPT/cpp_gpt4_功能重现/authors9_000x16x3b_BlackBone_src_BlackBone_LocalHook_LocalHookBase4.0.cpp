#include <Windows.h>
#include <vector>
#include <stdexcept>
#include <memory>

class DetourBase {
public:
    DetourBase() = delete;
    DetourBase(const DetourBase&) = delete;
    DetourBase& operator=(const DetourBase&) = delete;

    DetourBase(void* targetFunc, void* detourFunc) :
        m_targetFunc(targetFunc), m_detourFunc(detourFunc), m_hookEnabled(false), m_trampoline(nullptr) {
        BackupOriginalCode();
        AllocateTrampoline();
    }

    virtual ~DetourBase() {
        if (m_hookEnabled) {
            DisableHook();
        }
        if (m_trampoline) {
            VirtualFree(m_trampoline, 0, MEM_RELEASE);
        }
    }

    void EnableHook() {
        if (!m_hookEnabled) {
            DWORD oldProtect;
            VirtualProtect(m_targetFunc, m_backup.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
            WriteJump(m_targetFunc, m_detourFunc);
            VirtualProtect(m_targetFunc, m_backup.size(), oldProtect, &oldProtect);
            m_hookEnabled = true;
        }
    }

    void DisableHook() {
        if (m_hookEnabled) {
            DWORD oldProtect;
            VirtualProtect(m_targetFunc, m_backup.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
            memcpy(m_targetFunc, m_backup.data(), m_backup.size());
            VirtualProtect(m_targetFunc, m_backup.size(), oldProtect, &oldProtect);
            m_hookEnabled = false;
        }
    }

    void* GetTrampoline() {
        return m_trampoline;
    }

protected:
    virtual size_t GetInstructionLength(void* address) = 0;

private:
    void BackupOriginalCode() {
        size_t len = 0;
        while (len < sizeof(JumpInstruction)) {
            len += GetInstructionLength(static_cast<char*>(m_targetFunc) + len);
        }
        m_backup.resize(len);
        memcpy(m_backup.data(), m_targetFunc, len);
    }

    void AllocateTrampoline() {
        m_trampoline = VirtualAllocEx(GetCurrentProcess(), nullptr, m_backup.size() + sizeof(JumpInstruction),
                                      MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!m_trampoline) {
            throw std::runtime_error("Failed to allocate trampoline.");
        }
        memcpy(m_trampoline, m_backup.data(), m_backup.size());
        WriteJump(static_cast<char*>(m_trampoline) + m_backup.size(), static_cast<char*>(m_targetFunc) + m_backup.size());
    }

    void WriteJump(void* from, void* to) {
        uintptr_t src = reinterpret_cast<uintptr_t>(from);
        uintptr_t dst = reinterpret_cast<uintptr_t>(to);
        uintptr_t relativeAddress = dst - src - sizeof(JumpInstruction);
        JumpInstruction jmp;
        jmp.opcode = 0xE9;
        memcpy(jmp.operand, &relativeAddress, sizeof(jmp.operand));

        memcpy(from, &jmp, sizeof(jmp));
    }

    struct JumpInstruction {
        uint8_t opcode;
        uint32_t operand;
    };

    void* m_targetFunc;
    void* m_detourFunc;
    bool m_hookEnabled;
    void* m_trampoline;
    std::vector<uint8_t> m_backup;
};

