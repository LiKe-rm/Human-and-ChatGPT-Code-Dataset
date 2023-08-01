#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

// 自定义IO控制码
#define IOCTL_MUL_FUNCTION CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_COPY_FUNCTION CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_EVENT_FUNCTION CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)

// 用于注册表操作的线程函数
DWORD WINAPI RegThreadFunc(LPVOID lpParam);

int main()
{
    HANDLE hDevice;
    DWORD dwBytesReturned;
    std::string deviceName = "\\\\.\\MyFirstDevice";

    // 打开设备文件
    hDevice = CreateFileA(deviceName.c_str(),
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open the device: " << GetLastError() << std::endl;
        return 1;
    }

    // 创建两个事件对象
    HANDLE hEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);

    // 创建线程
    DWORD dwThreadId;
    HANDLE hThread = CreateThread(NULL, 0, RegThreadFunc, NULL, 0, &dwThreadId);

    if (!hThread) {
        std::cerr << "Failed to create thread: " << GetLastError() << std::endl;
        CloseHandle(hDevice);
        return 1;
    }

    // 执行乘法功能
    struct {
        int x;
        int y;
    } mulInput = {2, 3};
    int mulResult;

    DeviceIoControl(hDevice,
                    IOCTL_MUL_FUNCTION,
                    &mulInput,
                    sizeof(mulInput),
                    &mulResult,
                    sizeof(mulResult),
                    &dwBytesReturned,
                    NULL);

    std::cout << "Mul Function: " << mulInput.x << " * " << mulInput.y << " = " << mulResult << std::endl;

    // 执行复制功能
    std::string source = "Hello, World!";
    char dest[20] = {0};

    DeviceIoControl(hDevice,
                    IOCTL_COPY_FUNCTION,
                    (LPVOID)source.c_str(),
                    source.length(),
                    dest,
                    sizeof(dest),
                    &dwBytesReturned,
                    NULL);

    std::cout << "Copy Function: \"" << source << "\" -> \"" << dest << "\"" << std::endl;

    // 测试事件处理功能
    struct {
        HANDLE hEvent1;
        HANDLE hEvent2;
    } eventInput = {hEvent1, hEvent2};

    DeviceIoControl(hDevice,
                    IOCTL_TEST_EVENT_FUNCTION,
                    &eventInput,
                    sizeof(eventInput),
                    NULL,
                    0,
                    &dwBytesReturned,
                    NULL);

    WaitForSingleObject(hEvent1, INFINITE);
    WaitForSingleObject(hEvent2, INFINITE);

    std::cout << "Test Event Function: Both events are signaled." << std::endl;

    // 等待线程结束
    WaitForSingleObject(hThread, INFINITE);

    // 关闭句柄
    CloseHandle(hEvent1);
    CloseHandle(hEvent2);
    CloseHandle(hThread);
    CloseHandle(hDevice);

    return 0;
}

DWORD WINAPI RegThreadFunc(LPVOID lpParam)
{
    HKEY hKey;
    DWORD dwAddNumber = 42;
    const char* szKeyName = "Software\MyFirstDevice";
    const char* szValueName = "AddNumber";

    // 打开注册表键
    if (RegCreateKeyExA(HKEY_CURRENT_USER,
                        szKeyName,
                        0,
                        NULL,
                        REG_OPTION_NON_VOLATILE,
                        KEY_WRITE,
                        NULL,
                        &hKey,
                        NULL) != ERROR_SUCCESS) {
        std::cerr << "Failed to open registry key: " << GetLastError() << std::endl;
        return 1;
    }

    // 设置注册表键值
    if (RegSetValueExA(hKey,
                       szValueName,
                       0,
                       REG_DWORD,
                       (const BYTE*)&dwAddNumber,
                       sizeof(dwAddNumber)) != ERROR_SUCCESS) {
        std::cerr << "Failed to set registry value: " << GetLastError() << std::endl;
        RegCloseKey(hKey);
        return 1;
    }

    std::cout << "Registry Thread: Set value \"" << szValueName << "\" to " << dwAddNumber << std::endl;

    // 关闭注册表键
    RegCloseKey(hKey);

    return 0;
}