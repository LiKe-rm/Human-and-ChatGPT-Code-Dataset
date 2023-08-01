#include <s2e/s2e.h>
#include <s2e/Plugin.h>
#include <s2e/SymbolicHardwareHook.h>
#include <s2e/Utils.h>

class Ret2stack : public Plugin {
private:
    uint64_t m_shellcodeAddr;
    std::string m_exploitConstraint;

public:
    Ret2stack(S2E *s2e) : Plugin(s2e) {
        // 初始化shellcode，即攻击代码
        uint8_t shellcode[] = { /* shellcode bytes */ };
        m_shellcodeAddr = s2e->getExecutor()->getGlobalVariable((uint64_t) shellcode, sizeof(shellcode), "shellcode");

        // 遍历symbolic memory block，并调用函数1进行分析
        SymbolicHardwareHook *hwHook = s2e->getPlugin<SymbolicHardwareHook>();
        foreach2 (it, hwHook->getSymbolicRegions().begin(), hwHook->getSymbolicRegions().end()) {
            const SymbolicHardwareAccessType &access = it->second;
            if (access.addressSpace != MEM_STACK) {
                continue;
            }

            uint64_t start = it->first;
            uint64_t size = access.size;

            // 调用函数1进行分析
            uint64_t maxSledLen = analyzeSled(start, size);
            if (maxSledLen != 0) {
                // 生成exploitConstraint
                generateExploitConstraint(start, maxSledLen);

                // 如果exploitConstraint不为空，则调用函数2返回RopPayload列表
                if (!m_exploitConstraint.empty()) {
                    std::vector<RopPayload> payloads = getRopPayloads();
                    // do something with the payloads
                }
            }
        }
    }

private:
    uint64_t analyzeSled(uint64_t start, uint64_t size) {
        // 使用二分法来搜索NOP sled的最大长度
        uint64_t l = 0, r = size;
        while (l < r) {
            uint64_t mid = (l + r + 1) / 2;
            std::string sled = "A" * mid + "\x90\x90\x90\x90\x90";
            if (strstr((const char *) (start + size - sled.size()), sled.c_str()) != NULL) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }

    void generateExploitConstraint(uint64_t start, uint64_t sledLen) {
        // 生成exploitConstraint
        std::ostringstream ss;
        ss << "(assert (= eax_0x4 (bvadd #x" << std::hex << m_shellcodeAddr << " (_ bv" << sledLen << " 32))))";
        m_exploitConstraint = ss.str();
    }

    std::vector<RopPayload> getRopPayloads() {
        // 实现函数2的代码
        std::vector<RopPayload> payloads;
        // generate RopPayloads
        return payloads;
    }
};
