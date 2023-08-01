#include <Windows.h>

class DetourBase {
public:
    DetourBase(void* targetFunc) : m_targetFunc(targetFunc) {
        // 分配空间
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        m_pageSize = si.dwPageSize;
        m_allocSize = m_pageSize * 2;
        m_hookFunc = VirtualAlloc(NULL, m_allocSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (m_hookFunc == NULL) {
            throw "Failed to allocate memory";
        }

        // 备份原始函数
        memcpy(m_originalFunc, targetFunc, m_hookLength);
    }

    virtual ~DetourBase() {
        if (m_hookFunc != NULL) {
            VirtualFree(m_hookFunc, 0, MEM_RELEASE);
        }
    }

    void disable() {
        // 禁用钩子
        DWORD oldProtect;
        VirtualProtect(m_targetFunc, m_hookLength, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(m_targetFunc, m_originalFunc, m_hookLength);
        VirtualProtect(m_targetFunc, m_hookLength, oldProtect, &oldProtect);
    }

    void enable() {
        // 启用钩子
        DWORD oldProtect;
        VirtualProtect(m_targetFunc, m_hookLength, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(m_targetFunc, m_hookFunc, m_hookLength);
        VirtualProtect(m_targetFunc, m_hookLength, oldProtect, &oldProtect);
    }

    void setHardwareBreakpoint() {
        // 设置硬件断点
        CONTEXT context;
        context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
        GetThreadContext(GetCurrentThread(), &context);
        context.Dr0 = (DWORD_PTR)m_targetFunc;
        context.Dr7 = 0x00000001;
        SetThreadContext(GetCurrentThread(), &context);
    }

protected:
    virtual void handleException(EXCEPTION_RECORD* exception) = 0;

    void install() {
        // 安装钩子
        DWORD oldProtect;
        VirtualProtect(m_targetFunc, m_hookLength, PAGE_EXECUTE_READWRITE, &oldProtect);

        // 生成钩子代码
        generateHookCode(m_hookFunc, m_targetFunc, m_hookLength);

        VirtualProtect(m_targetFunc, m_hookLength, oldProtect, &oldProtect);

        // 设置异常处理函数
        m_oldExceptionHandler = SetUnhandledExceptionFilter(&DetourBase::exceptionHandler);
    }

    void uninstall() {
        // 卸载钩子
        SetUnhandledExceptionFilter(m_oldExceptionHandler);

        DWORD oldProtect;
        VirtualProtect(m_targetFunc, m_hookLength, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(m_targetFunc, m_originalFunc, m_hookLength);
        VirtualProtect(m_targetFunc, m_hookLength, oldProtect, &oldProtect);
    }

private:
    void* m_targetFunc;                 // 目标函数地址
    void* m_hookFunc;                   // 钩子函数地址
    int m_hookLength = 5;               // 默认钩子长度（暂时只支持5字节长度的钩子）
    int m_pageSize;                     // 内存页大小
    int m_allocSize;                    // 分配的内存大小
    unsigned char m_originalFunc[32];   // 原始函数代码备份
    LPTOP_LEVEL_EXCEPTION_FILTER m_oldExceptionHandler;   // 旧的异常处理函数

    static LONG WINAPI exceptionHandler(EXCEPTION_POINTERS* exceptionPtr) {
        EXCEPTION_RECORD* exception = exceptionPtr->ExceptionRecord;
        if (exception->ExceptionCode == EXCEPTION_SINGLE_STEP) {
            // 硬件断点触发
            DetourBase* detour = reinterpret_cast<DetourBase*>(exceptionPtr->ContextRecord->Eax);
            detour->handleException(exception);
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }

    void generateHookCode(void* hookFunc, void* targetFunc, int hookLength) {
        // 默认生成一个5字节的跳转指令
        unsigned char code[5] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
        int relativeOffset = (int)hookFunc - (int)targetFunc - hookLength;
        memcpy(&code[1], &relativeOffset, sizeof(int));
        memcpy(hookFunc, code, sizeof(code));
    }
};