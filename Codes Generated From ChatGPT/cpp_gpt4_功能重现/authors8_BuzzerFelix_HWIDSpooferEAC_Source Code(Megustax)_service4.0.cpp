#include <iostream>
#include <windows.h>
#include <tchar.h>

// 函数声明
SC_HANDLE OpenSCManagerWrapper();
bool CheckServiceExists(const TCHAR* serviceName);
bool RegisterService(const TCHAR* serviceName, const TCHAR* binaryPath);
bool StartService(const TCHAR* serviceName);
bool StopService(const TCHAR* serviceName);
bool DeleteService(const TCHAR* serviceName);

SC_HANDLE OpenSCManagerWrapper() {
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!hSCManager) {
        std::cerr << "OpenSCManager failed, error: " << GetLastError() << std::endl;
    }
    return hSCManager;
}

bool CheckServiceExists(const TCHAR* serviceName) {
    bool exists = false;
    SC_HANDLE hSCManager = OpenSCManagerWrapper();
    if (hSCManager) {
        SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_QUERY_STATUS);
        if (hService) {
            exists = true;
            CloseServiceHandle(hService);
        }
        CloseServiceHandle(hSCManager);
    }
    return exists;
}

bool RegisterService(const TCHAR* serviceName, const TCHAR* binaryPath) {
    SC_HANDLE hSCManager = OpenSCManagerWrapper();
    if (!hSCManager) {
        return false;
    }

    SC_HANDLE hService = CreateService(
        hSCManager,
        serviceName,
        serviceName,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        binaryPath,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);

    if (!hService) {
        std::cerr << "CreateService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hSCManager);
        return false;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

bool StartService(const TCHAR* serviceName) {
    SC_HANDLE hSCManager = OpenSCManagerWrapper();
    if (!hSCManager) {
        return false;
    }

    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_START);
    if (!hService) {
        std::cerr << "OpenService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hSCManager);
        return false;
    }
    if (!::StartService(hService, 0, NULL)) {
        std::cerr << "StartService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return false;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

bool StopService(const TCHAR* serviceName) {
    SC_HANDLE hSCManager = OpenSCManagerWrapper();
    if (!hSCManager) {
        return false;
    }
    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_STOP);
    if (!hService) {
        std::cerr << "OpenService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hSCManager);
        return false;
    }

    SERVICE_STATUS serviceStatus;
    if (!ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus)) {
        std::cerr << "ControlService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return false;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}

bool DeleteService(const TCHAR* serviceName) {
    SC_HANDLE hSCManager = OpenSCManagerWrapper();
    if (!hSCManager) {
        return false;
    }
    SC_HANDLE hService = OpenService(hSCManager, serviceName, DELETE);
    if (!hService) {
        std::cerr << "OpenService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hSCManager);
        return false;
    }

    if (!::DeleteService(hService)) {
        std::cerr << "DeleteService failed, error: " << GetLastError() << std::endl;
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return false;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return true;
}


