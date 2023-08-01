#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

// Function 1: Get the address of the specified function in the dynamic-link library
FARPROC GetFunctionAddress(const std::string& moduleName, const std::string& funcName) {
    HMODULE hModule = GetModuleHandleA(moduleName.c_str());
    if (!hModule) {
        return nullptr;
    }
    return GetProcAddress(hModule, funcName.c_str());
}

// Function 2: Get process ID by given process name
DWORD GetProcessIdByName(const std::string& processName) {
    DWORD processId = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, processName.c_str()) == 0) {
                processId = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return processId;
}

// Function 3: Modify process privileges
bool ModifyProcessPrivileges(DWORD processId) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS) {
        return false;
    }

    CloseHandle(hToken);
    return true;
}

// Function 4: Create a process and attach it to explorer.exe
bool CreateProcessAndAttachToExplorer(const std::string& processPath) {
    DWORD explorerPID = GetProcessIdByName("explorer.exe");
    if (explorerPID == 0) {
        return false;
    }

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    BOOL success = CreateProcess(
        processPath.c_str(), NULL, NULL, NULL, FALSE,
        CREATE_SUSPENDED | CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

    if (!success) {
        return false;
    }

    HANDLE hExplorer = OpenProcess(PROCESS_ALL_ACCESS, FALSE, explorerPID);
    if (!hExplorer) {
        TerminateProcess(pi.hProcess, 0);
        return false;
    }

    PVOID remoteThread = VirtualAllocEx(hExplorer, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!remoteThread) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(hExplorer);
        return false;
    }

    success = WriteProcessMemory(hExplorer, remoteThread, &pi.hProcess, sizeof(HANDLE), NULL);
    if (!success) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(hExplorer);
        return false;
    }

    HANDLE hRemoteThread = CreateRemoteThread(hExplorer, NULL, 0, (LPTHREAD_START_ROUTINE)remoteThread, NULL, 0, NULL);
        if (!hRemoteThread) {
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(hExplorer);
            return false;
        }
        ResumeThread(pi.hThread);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        CloseHandle(hExplorer);
        return true;
}

// Function 5: Read specified number of bytes from a file and return the number of bytes read
DWORD ReadBytesFromFile(const std::string& filePath, LPVOID buffer, DWORD bytesToRead) {
    HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return 0;
    }
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, bytesToRead, &bytesRead, NULL)) {
        bytesRead = 0;
    }

    CloseHandle(hFile);
    return bytesRead;
}

// Function 6: Get the current process integrity level
DWORD GetCurrentProcessIntegrityLevel() {
    DWORD integrityLevel = 0;
    HANDLE hToken;
    DWORD tokenILLength = 0;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
    return 0;
    }

    GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &tokenILLength);
    PTOKEN_MANDATORY_LABEL pTokenIL = (PTOKEN_MANDATORY_LABEL)LocalAlloc(0, tokenILLength);

    if (pTokenIL != NULL) {
        if (GetTokenInformation(hToken, TokenIntegrityLevel, pTokenIL, tokenILLength, &tokenILLength)) {
            integrityLevel = *GetSidSubAuthority(pTokenIL->Label.Sid,
                (DWORD)(UCHAR)(*GetSidSubAuthorityCount(pTokenIL->Label.Sid) - 1));
        }
        LocalFree(pTokenIL);
    }

    CloseHandle(hToken);
    return integrityLevel;
}
