#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <vector>

// 1. 获取ReflectiveLoader函数在内存中的偏移量
DWORD GetReflectiveLoaderOffset(const BYTE* dllBuffer) {
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)dllBuffer;
    IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)(dllBuffer + dosHeader->e_lfanew);

    DWORD exportDirectoryRVA = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    IMAGE_EXPORT_DIRECTORY* exportDirectory = (IMAGE_EXPORT_DIRECTORY*)(dllBuffer + exportDirectoryRVA);

    DWORD* nameRVAs = (DWORD*)(dllBuffer + exportDirectory->AddressOfNames);
    WORD* nameOrdinals = (WORD*)(dllBuffer + exportDirectory->AddressOfNameOrdinals);
    DWORD* functionRVAs = (DWORD*)(dllBuffer + exportDirectory->AddressOfFunctions);

    for (DWORD i = 0; i < exportDirectory->NumberOfNames; i++) {
        const char* functionName = (const char*)(dllBuffer + nameRVAs[i]);
        if (strcmp(functionName, "ReflectiveLoader") == 0) {
            WORD ordinal = nameOrdinals[i];
            DWORD offset = functionRVAs[ordinal];
            return offset;
        }
    }

    return 0;
}

// 2. 将DLL文件加载到当前进程
bool LoadDLLIntoCurrentProcess(const char* dllPath) {
    std::ifstream dllFile(dllPath, std::ios::binary | std::ios::ate);
    std::streamsize size = dllFile.tellg();
    dllFile.seekg(0, std::ios::beg);

    std::vector<BYTE> dllBuffer(size);
    if (!dllFile.read((char*)dllBuffer.data(), size)) {
        return false;
    }

    DWORD reflectiveLoaderOffset = GetReflectiveLoaderOffset(dllBuffer.data());
    if (!reflectiveLoaderOffset) {
        return false;
    }

    LPVOID remoteMemory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteMemory) {
        return false;
    }

    memcpy(remoteMemory, dllBuffer.data(), size);
    DWORD oldProtect;
    VirtualProtect(remoteMemory, size, PAGE_EXECUTE_READ, &oldProtect);

    LPVOID reflectiveLoader = (LPVOID)((BYTE*)remoteMemory + reflectiveLoaderOffset);
    HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)reflectiveLoader, NULL, 0, NULL);
    if (!thread) {
        VirtualFree(remoteMemory, 0, MEM_RELEASE);
        return false;
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    VirtualFree(remoteMemory, 0, MEM_RELEASE);

    return true;
}

// 3. 将DLL文件加载到远程进程
bool LoadDLLIntoRemoteProcess(DWORD processId, const char* dllPath) {
    HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processId);
    if (!hProcess) {
        return false;
    }

    std::ifstream dllFile(dllPath, std::ios::binary | std::ios::ate);
    std::streamsize size = dllFile.tellg();
    dllFile.seekg(0, std::ios::beg);

    std::vector<BYTE> dllBuffer(size);
    if (!dllFile.read((char*)dllBuffer.data(), size)) {
        CloseHandle(hProcess);
        return false;
    }

    DWORD reflectiveLoaderOffset = GetReflectiveLoaderOffset(dllBuffer.data());
    if (!reflectiveLoaderOffset) {
        CloseHandle(hProcess);
        return false;
    }

    LPVOID remoteMemory = VirtualAllocEx(hProcess, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteMemory) {
        CloseHandle(hProcess);
        return false;
    }

    SIZE_T written;
    WriteProcessMemory(hProcess, remoteMemory, dllBuffer.data(), size, &written);

    DWORD oldProtect;
    VirtualProtectEx(hProcess, remoteMemory, size, PAGE_EXECUTE_READ, &oldProtect);

    LPVOID reflectiveLoader = (LPVOID)((BYTE*)remoteMemory + reflectiveLoaderOffset);
    HANDLE thread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)reflectiveLoader, NULL, 0, NULL);
    if (!thread) {
        VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
    CloseHandle(hProcess);

    return true;
}

