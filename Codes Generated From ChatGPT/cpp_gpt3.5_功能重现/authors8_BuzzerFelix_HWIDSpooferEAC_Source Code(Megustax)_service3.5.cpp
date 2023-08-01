#include <Windows.h>
#include <iostream>
#include <string>

// 检查是否存在同名服务
bool CheckServiceExists(const std::string& serviceName)
{
    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (scm == nullptr)
    {
        return false;
    }
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_QUERY_STATUS);
    if (service == nullptr)
    {
        CloseServiceHandle(scm);
        return false;
    }
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return true;
}

// 注册Windows服务
bool RegisterService(const std::string& serviceName, const std::string& displayName, const std::string& exePath)
{
    if (CheckServiceExists(serviceName))
    {
        std::cout << "Service " << serviceName << " already exists." << std::endl;
        return false;
    }
    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
    if (scm == nullptr)
    {
        std::cout << "Failed to open SCManager." << std::endl;
        return false;
    }
    SC_HANDLE service = CreateServiceA(scm, serviceName.c_str(), displayName.c_str(), SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, exePath.c_str(), nullptr, nullptr, nullptr, nullptr, nullptr);
    if (service == nullptr)
    {
        std::cout << "Failed to create service." << std::endl;
        CloseServiceHandle(scm);
        return false;
    }
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return true;
}

// 启动Windows服务
bool StartService(const std::string& serviceName)
{
    if (!CheckServiceExists(serviceName))
    {
        std::cout << "Service " << serviceName << " does not exist." << std::endl;
        return false;
    }
    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (scm == nullptr)
    {
        std::cout << "Failed to open SCManager." << std::endl;
        return false;
    }
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_START);
    if (service == nullptr)
    {
        std::cout << "Failed to open service." << std::endl;
        CloseServiceHandle(scm);
        return false;
    }
    if (!StartServiceA(service, 0, nullptr))
    {
        std::cout << "Failed to start service." << std::endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return false;
    }
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return true;
}

// 停止Windows服务
bool StopService(const std::string& serviceName)
{
    if (!CheckServiceExists(serviceName))
    {
        std::cout << "Service " << serviceName << " does not exist." << std::endl;
        return false;
    }
    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (scm == nullptr)
    {
        std::cout << "Failed to open SCManager." << std::endl;
        return false;
    }
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_CONTROL_STOP);
    // 打开服务
    if (service == nullptr)
    {
        std::cout << "Failed to open service." << std::endl;
        CloseServiceHandle(scm);
        return false;
    }
    SERVICE_STATUS status;
    if (!ControlService(service, SERVICE_CONTROL_STOP, &status))
    {
        std::cout << "Failed to stop service." << std::endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return false;
    }
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return true;
}

    // 删除Windows服务
bool DeleteService(const std::string& serviceName)
{
    if (!CheckServiceExists(serviceName))
    {
        std::cout << "Service " << serviceName << " does not exist." << std::endl;
        return false;
    }
    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (scm == nullptr)
    {
        std::cout << "Failed to open SCManager." << std::endl;
        return false;
    }
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_STOP | DELETE);
    if (service == nullptr)
    {
        std::cout << "Failed to open service." << std::endl;
        CloseServiceHandle(scm);
        return false;
    }
    if (!DeleteService(service))
    {
        std::cout << "Failed to delete service." << std::endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return false;
    }
    CloseServiceHandle(service);
    CloseServiceHandle(scm);
    return true;
}

