#include <Windows.h>
#include <Psapi.h>
#include <iostream>

#pragma comment(lib, "Psapi.lib")

class ETHREADSearch {
    public:
        // 构造函数，传入目标进程名称
    ETHREADSearch(const char* targetProcessName);

    // 在给定缓冲区中搜索ETHREAD对象
    bool SearchETHREADs(const void* buffer, size_t bufferSize);

    // 创建Artefact对象
    void CreateArtefact();

    private:
    const char* m_targetProcessName;
    DWORD m_targetPID;
    DWORD m_ETHREADSize;
    DWORD m_ETHREADFlinkOffset;
    DWORD m_ETHREADBlinkOffset;
    DWORD m_ETHREADPIDOffset;
    DWORD m_ETHREADAddressSpaceOffset;
    // 其他私有成员变量
    // ...

    // 为目标Windows版本设置默认的偏移量和大小
    void SetDefaultOffsetsAndSizes();

    // 获取当前系统上运行的进程的PID列表
    void GetProcessList();

    // 检查地址是否包含ETHREAD对象
    bool CheckAddressForETHREAD(DWORD_PTR address, DWORD_PTR baseAddress, DWORD_PTR endAddress);

    // 其他私有方法
    // ...
};

ETHREADSearch::ETHREADSearch(const char* targetProcessName) {
    // 初始化对象名称和标签
    // 创建表示“abstract”ETHREAD符号
    // 指定所有相关的ETHREAD成员
    // 创建_KTHREAD和_KWAIT_BLOCK符号

    // 为目标Windows版本设置默认的偏移量和大小
    SetDefaultOffsetsAndSizes();

    // 获取当前系统上运行的进程的PID列表，并筛选出目标进程的PID
    GetProcessList();

    m_targetProcessName = targetProcessName;
}

void ETHREADSearch::SetDefaultOffsetsAndSizes() {
    // 获取Windows版本信息
    OSVERSIONINFO osVersionInfo;
    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osVersionInfo);

    // 根据Windows版本设置偏移量和大小
    if (osVersionInfo.dwMajorVersion == 10 && osVersionInfo.dwBuildNumber >= 16299) {
        m_ETHREADSize = 0x620;
        m_ETHREADFlinkOffset = 0x2f0;
        m_ETHREADBlinkOffset = 0x2f8;
        m_ETHREADPIDOffset = 0x3b0;
        m_ETHREADAddressSpaceOffset = 0x3e0;
    } else if (osVersionInfo.dwMajorVersion == 6 && osVersionInfo.dwMinorVersion == 3) {
        m_ETHREADSize = 0x4b0;
        m_ETHREADFlinkOffset = 0x258;
        m_ETHREADBlinkOffset = 0x260;
        m_ETHREADPIDOffset = 0x3b8;
        m_ETHREADAddressSpaceOffset = 0x3d8;
    } else {
        // 不支持的Windows版本
        std::cerr << "Unsupported Windows version." << std::endl;
        exit(-1);
    }
}

void ETHREADSearch::GetProcessList() {
    // 获取当前系统上运行的进程的PID列表
    DWORD processIds[1024];
    DWORD bytesReturned;
    EnumProcesses(processIds, sizeof(processIds), &bytesReturned);
    DWORD processCount = bytesReturned / sizeof(DWORD);

    // 遍历进程列表，查找目标进程
    bool foundTargetProcess = false;
    for (DWORD i = 0; i < processCount; i++) {
        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[i]);
        if (processHandle) {
            char processName[MAX_PATH];
            if (GetModuleFileNameExA(processHandle, NULL, processName, MAX_PATH)) {
                if (strstr(processName, m_targetProcessName)) {
                    m_targetPID = processIds[i];
                    foundTargetProcess = true;
                    break;
                }
            }
            CloseHandle(processHandle);
        }
    }

    // 没有找到目标进程
    if (!foundTargetProcess) {
        std::cerr << "Target process not found." << std::endl;
        exit(-1);
    }
}
bool ETHREADSearch::SearchETHREADs(const void* buffer, size_t bufferSize) {
    // 在给定缓冲区中搜索ETHREAD对象
    bool foundETHREAD = false;
    DWORD_PTR baseAddress = (DWORD_PTR)buffer;
    DWORD_PTR endAddress = baseAddress + bufferSize - m_ETHREADSize;

    for (DWORD_PTR address = baseAddress; address < endAddress; address += 8) {
        if (CheckAddressForETHREAD(address, baseAddress, endAddress)) {
            // 找到了ETHREAD对象
            foundETHREAD = true;

            // 获取PID和地址空间指针
            DWORD_PTR PIDAddress = address + m_ETHREADPIDOffset;
            DWORD_PTR addressSpaceAddress = address + m_ETHREADAddressSpaceOffset;
            DWORD pid = 0;
            HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, m_targetPID);
            if (ReadProcessMemory(processHandle, (LPCVOID)PIDAddress, &pid, sizeof(DWORD), NULL)) {
                if (pid == m_targetPID) {
                    // 找到了目标进程的ETHREAD对象，更新Flink和Blink指针并删除线程块
                    DWORD_PTR flinkAddress = address + m_ETHREADFlinkOffset;
                    DWORD_PTR blinkAddress = address + m_ETHREADBlinkOffset;

                    DWORD_PTR flink = 0, blink = 0;
                    ReadProcessMemory(processHandle, (LPCVOID)flinkAddress, &flink, sizeof(DWORD_PTR), NULL);
                    ReadProcessMemory(processHandle, (LPCVOID)blinkAddress, &blink, sizeof(DWORD_PTR), NULL);

                    if (flink && blink) {
                        // 更新Flink和Blink指针
                        WriteProcessMemory(processHandle, (LPVOID)flinkAddress, &blink, sizeof(DWORD_PTR), NULL);
                        WriteProcessMemory(processHandle, (LPVOID)blinkAddress, &flink, sizeof(DWORD_PTR), NULL);

                        // 删除线程块
                        VirtualFreeEx(processHandle, (LPVOID)address, m_ETHREADSize, MEM_RELEASE);
                    }
                }
            }
            CloseHandle(processHandle);
        }
    }

    return foundETHREAD;
}
bool ETHREADSearch::CheckAddressForETHREAD(DWORD_PTR address, DWORD_PTR baseAddress, DWORD_PTR endAddress) {
    // 检查地址是否包含ETHREAD对象
    bool result = false;
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, m_targetPID);
    if (processHandle) {
        DWORD bytesRead;
        BYTE buffer[sizeof(DWORD_PTR)];

        if (ReadProcessMemory(processHandle, (LPCVOID)address, buffer, sizeof(buffer), &bytesRead)) {
            if (bytesRead == sizeof(buffer)) {
                DWORD_PTR value = 0;
                for (DWORD i = 0; i < sizeof(buffer); i++) {
                    value |= ((DWORD_PTR)buffer[i]) << (8 * i);
                }

                if (value > baseAddress && value < endAddress) {
                    DWORD_PTR PIDAddress = value + m_ETHREADPIDOffset;
                    DWORD pid = 0;
                    if (ReadProcessMemory(processHandle, (LPCVOID)PIDAddress, &pid, sizeof(DWORD), NULL)) {
                        if (pid == m_targetPID) {
                            result = true;
                            break;
                        }
                    }
                }
            }
        }

        CloseHandle(processHandle);
    }

    return result;
}
