#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <intrin.h>

#pragma comment(lib, "ntdll.lib")

// 定义函数指针类型
typedef NTSTATUS(NTAPI *pNtCreateThreadEx)(
    OUT PHANDLE ThreadHandle,
    IN ACCESS_MASK DesiredAccess,
    IN PVOID ObjectAttributes,
    IN HANDLE ProcessHandle,
    IN PVOID StartRoutine,
    IN PVOID Argument,
    IN ULONG CreateFlags,
    IN ULONG_PTR ZeroBits,
    IN ULONG_PTR StackSize,
    IN ULONG_PTR MaximumStackSize,
    IN PVOID AttributeList);

// 获取进程的PEB指针
PPEB fetchPEB(HANDLE hProcess)
{
    PROCESS_BASIC_INFORMATION pbi;
    ULONG returnLength = 0;
    _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryInformationProcess");

    NTSTATUS status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &returnLength);
    if (status != 0x0)
    {
        return NULL;
    }

    return pbi.PebBaseAddress;
}

// 获取PE映像的入口点RVA
DWORD get_entry_point_rva(const LPBYTE lpBuffer)
{
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)lpBuffer;
    PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)(lpBuffer + dosHeader->e_lfanew);
    return ntHeader->OptionalHeader.AddressOfEntryPoint;
}

// 将PRTL_USER_PROCESS_PARAMETERS结构体写入指定进程
BOOL write_params_into_process(HANDLE hProcess, PRTL_USER_PROCESS_PARAMETERS params, LPVOID remoteParams)
{
    SIZE_T bytesWritten = 0;
    BOOL success = WriteProcessMemory(hProcess, remoteParams, params, sizeof(RTL_USER_PROCESS_PARAMETERS), &bytesWritten);
    return success && (bytesWritten == sizeof(RTL_USER_PROCESS_PARAMETERS));
}

// 更新目标进程PEB中的地址
BOOL updatePtr_ProcessParam(HANDLE hProcess, PPEB peb, LPVOID remoteParams)
{
    SIZE_T bytesWritten = 0;
    BOOL success = WriteProcessMemory(hProcess, (LPBYTE)peb + offsetof(PEB, ProcessParameters), &remoteParams, sizeof(LPVOID), &bytesWritten);
    return success && (bytesWritten == sizeof(LPVOID));
}

// 加载路径名到PRTL_USER_PROCESS_PARAMETERS，并写入到指定进程中
BOOL setup_process_parameters(HANDLE hProcess, PPEB peb, LPCWSTR pathName)
{
    RTL_USER_PROCESS_PARAMETERS params;
    ZeroMemory(&params, sizeof(RTL_USER_PROCESS_PARAMETERS));

    // 配置参数
    params.Length = sizeof(RTL_USER_PROCESS_PARAMETERS);
    params.MaximumLength = sizeof(RTL_USER_PROCESS_PARAMETERS);
    params.ImagePathName.Buffer = (PWSTR)pathName;
    params.ImagePathName.Length = wcslen(pathName) * sizeof(WCHAR);
    params.ImagePathName.MaximumLength = (wcslen(pathName) + 1) * sizeof(WCHAR);

    LPVOID remoteParams = VirtualAllocEx(hProcess, NULL, sizeof(RTL_USER_PROCESS_PARAMETERS), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteParams)
    {
        return FALSE;
    }
    if (!write_params_into_process(hProcess, &params, remoteParams))
    {
        VirtualFreeEx(hProcess, remoteParams, 0, MEM_RELEASE);
        return FALSE;
    }

    if (!updatePtr_ProcessParam(hProcess, peb, remoteParams))
    {
        VirtualFreeEx(hProcess, remoteParams, 0, MEM_RELEASE);
        return FALSE;
    }

    return TRUE;
}

// 收集所有参数，加载目标PE，创建新进程和线程
BOOL spawnProcess(LPCWSTR pathName)
{
    // 读取PE文件到内存
    HANDLE hFile = CreateFile(pathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    LPBYTE lpBuffer = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, fileSize);
    DWORD bytesRead = 0;
    BOOL success = ReadFile(hFile, lpBuffer, fileSize, &bytesRead, NULL);
    CloseHandle(hFile);

    if (!success || bytesRead != fileSize)
    {
        HeapFree(GetProcessHeap(), 0, lpBuffer);
        return FALSE;
    }

    // 创建一个挂起的新进程
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    success = CreateProcess(NULL, (LPWSTR)pathName, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    if (!success)
    {
        HeapFree(GetProcessHeap(), 0, lpBuffer);
        return FALSE;
    }

    // 获取新进程的PEB
    PPEB peb = fetchPEB(pi.hProcess);
    if (!peb)
    {
        TerminateProcess(pi.hProcess, 0);
        HeapFree(GetProcessHeap(), 0, lpBuffer);
        return FALSE;
    }

    // 设置进程参数
    if (!setup_process_parameters(pi.hProcess, peb, pathName))
    {
        TerminateProcess(pi.hProcess, 0);
        HeapFree(GetProcessHeap(), 0, lpBuffer);
        return FALSE;
    }

    // 计算入口点地址
    LPVOID remoteEntryPoint = (LPVOID)((LPBYTE)peb->ImageBaseAddress + get_entry_point_rva(lpBuffer));

    // 创建远程线程
    pNtCreateThreadEx NtCreateThreadEx = (pNtCreateThreadEx)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtCreateThreadEx");
    HANDLE hThread = NULL;
    NTSTATUS status = NtCreateThreadEx(&hThread, THREAD_ALL_ACCESS, NULL, pi.hProcess, remoteEntryPoint, NULL, 0, 0, 0, 0, NULL);

    if (status != 0x0)
    {
        TerminateProcess(pi.hProcess, 0);
        HeapFree(GetProcessHeap(), 0, lpBuffer);
        return FALSE;
    }

    ResumeThread(hThread);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    HeapFree(GetProcessHeap(), 0, lpBuffer);
    return TRUE;
}

int main()
{
    LPCWSTR targetPath = L"C:\\path\\to\\target.exe";
    if (spawnProcess(targetPath))
    {
        std::cout << "Process spawned successfully!" << std::endl;
    } else
    {
        std::cout << "Failed to spawn process." << std::endl;
    }

    return 0;
}

