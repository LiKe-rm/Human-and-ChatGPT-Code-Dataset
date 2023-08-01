#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <strsafe.h>

#pragma comment(lib, "ntdll.lib")

using namespace std;

// LogToConsole: 将信息输出到控制台
void LogToConsole(const wchar_t* message) {
    // 获取控制台句柄
    if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
        AllocConsole();
    }
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // 输出信息到控制台
    StringCbVPrintf(nullptr, 0, message, nullptr);
    wchar_t* buffer = new wchar_t[wcslen(message) + 1];
    StringCbVPrintf(buffer, wcslen(message) * sizeof(wchar_t) + 1, message, nullptr);
    WriteConsole(console_handle, buffer, (DWORD)wcslen(buffer), nullptr, nullptr);
    delete[] buffer;
}

// GetCurrentDllFileName: 获取当前 DLL 的文件名
wstring GetCurrentDllFileName() {
    wchar_t module_path[MAX_PATH];
    GetModuleFileName(nullptr, module_path, MAX_PATH);
    return wstring(module_path);
}

// DeleteKnownDllEntry: 删除 KnownDll Entry
void DeleteKnownDllEntry() {
    wstring dll_file_name = GetCurrentDllFileName();
    // 构造 KnownDll Entry 的路径
    wstring known_dll_entry_path = L"\\KnownDlls\\" + dll_file_name.substr(dll_file_name.rfind(L"\\") + 1);
    // 打开 KnownDll Entry 并设置 DACL 为空
    HANDLE sym_link_handle = nullptr;
    UNICODE_STRING sym_link_name;
    RtlInitUnicodeString(&sym_link_name, known_dll_entry_path.c_str());
    OBJECT_ATTRIBUTES sym_link_attr;
    InitializeObjectAttributes(&sym_link_attr, &sym_link_name, OBJ_CASE_INSENSITIVE, nullptr, nullptr);
    NTSTATUS status = NtOpenSymbolicLinkObject(&sym_link_handle, SYMBOLIC_LINK_ALL_ACCESS, &sym_link_attr);
    if (NT_SUCCESS(status)) {
        SECURITY_DESCRIPTOR sd;
        InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&sd, TRUE, nullptr, FALSE);
        status = NtSetSecurityObject(sym_link_handle, DACL_SECURITY_INFORMATION, &sd);
        if (!NT_SUCCESS(status)) {
            LogToConsole(L"Failed to set DACL for symbolic link, error code: %d\n", status);
            NtClose(sym_link_handle);
            return;
        }
    } else {
        LogToConsole(L"Failed to open symbolic link, error code: %d\n", status);
        return;
    }
    // 将 KnownDll Entry 变成临时对象
    HANDLE temp_handle = nullptr;
    status = NtMakeTemporaryObject(sym_link_handle, &temp_handle);
    if (!NT_SUCCESS(status)) {
        LogToConsole(L"Failed to make symbolic link temporary, error code: %d\n", status);
        NtClose(sym_link_handle);
        return;
    }
    // 关闭句柄，使得 KnownDll Entry 被删除
    NtClose(temp_handle);
    NtClose(sym_link_handle);
    LogToConsole(L"KnownDll Entry has been successfully deleted.\n");
}

// DLL 入口函数
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        // DLL 被加载时调用
            LogToConsole(L"This DLL has been loaded.\n");
            DeleteKnownDllEntry(); // 删除 KnownDll Entry
            break;
        case DLL_PROCESS_DETACH:
        // DLL 被卸载时调用
            LogToConsole(L"This DLL has been unloaded.\n");
            break;
        default:
            break;
    }
    return TRUE;
}