#include <iostream>
#include <windows.h>
#include <winternl.h>
#include <tchar.h>

typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

bool checkPEBBeingDebugged() {
    DWORD_PTR dwPEB = NULL;
    BOOL bIsDebugged = FALSE;

    __asm {
        mov eax, fs: [0x30]
        mov dwPEB, eax
    }

    bIsDebugged = *(BOOL *)(dwPEB + 0x02);
    return bIsDebugged;
}

bool checkProcessDebug() {
    HANDLE hParentProcess = NULL;
    DWORD dwParentProcessID = NULL;

    dwParentProcessID = (DWORD)GetCurrentProcessId();
    hParentProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwParentProcessID);

    if (hParentProcess == NULL) {
        return false;
    }

    pNtQueryInformationProcess NtQueryInfoProcess = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
    if (NtQueryInfoProcess == NULL) {
        CloseHandle(hParentProcess);
        return false;
    }

    DWORD_PTR dwDebugPort = 0;
    NTSTATUS status = NtQueryInfoProcess(hParentProcess, ProcessDebugPort, &dwDebugPort, sizeof(dwDebugPort), NULL);
    CloseHandle(hParentProcess);

    if (status == 0x00000000 && dwDebugPort != 0) {
        return true;
    }

    return false;
}

bool checkPEBNtGlobalFlag() {
    DWORD_PTR dwPEB = NULL;
    DWORD dwNtGlobalFlag = 0;

    __asm {
        mov eax, fs: [0x30]
        mov dwPEB, eax
    }

    dwNtGlobalFlag = *(DWORD *)(dwPEB + 0x68);
    return (dwNtGlobalFlag & 0x00000070) != 0;
}

bool checkProcessDebugFlags() {
    HANDLE hProcess = NULL;
    DWORD dwProcessID = NULL;

    dwProcessID = (DWORD)GetCurrentProcessId();
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);

    if (hProcess == NULL) {
        return false;
    }

    pNtQueryInformationProcess NtQueryInfoProcess = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
    if (NtQueryInfoProcess == NULL) {
        CloseHandle(hProcess);
        return false;
    }

    DWORD dwNoDebugInherit = 0;
    NTSTATUS status = NtQueryInfoProcess(hProcess, ProcessDebugFlags, &dwNoDebugInherit, sizeof(dwNoDebugInherit), NULL);
    CloseHandle(hProcess);

    if (status == 0x00000000 && dwNoDebugInherit == 0) {
        return true;
    }

    return false;
}

bool hideFromDebugger() {
    pNtQueryInformationProcess NtQueryInfoProcess = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
    if (NtQueryInfoProcess == NULL) {
        return false;
    }

    NTSTATUS status = NtQueryInfoProcess(GetCurrentThread(), ThreadHideFromDebugger, NULL, 0, NULL);
    return status == 0x00000000;
}
bool checkMemoryBreakpoint() {
    const SIZE_T dwSize = 0x1000;
    LPVOID lpBuffer = NULL;

    lpBuffer = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (lpBuffer == NULL) {
        return false;
    }

    memset(lpBuffer, 0xCC, dwSize);

    MEMORY_BASIC_INFORMATION mbi = {0};
    if (VirtualQuery(lpBuffer, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0) {
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        return false;
    }

    if (mbi.Protect & PAGE_GUARD) {
        VirtualFree(lpBuffer, 0, MEM_RELEASE);
        return true;
    }

    VirtualFree(lpBuffer, 0, MEM_RELEASE);
    return false;
}

int main() {
    if (checkPEBBeingDebugged()) {
        std::cout << "Debugger detected: PEB.BeingDebugged" << std::endl;
    }
    if (checkProcessDebug()) {
        std::cout << "Debugger detected: Check Process Debug" << std::endl;
    }
    if (checkPEBNtGlobalFlag()) {
        std::cout << "Debugger detected: PEB.NtGlobalFlag" << std::endl;
    }
    if (checkProcessDebugFlags()) {
        std::cout << "Debugger detected: Check Process Debug Flags" << std::endl;
    }
    if (hideFromDebugger()) {
        std::cout << "Debugger detected: Hide From Debugger" << std::endl;
    }
    if (checkMemoryBreakpoint()) {
        std::cout << "Debugger detected: Memory Breakpoint" << std::endl;
    }

    std::cout << "No debugger detected." << std::endl;
    return 0;
}
