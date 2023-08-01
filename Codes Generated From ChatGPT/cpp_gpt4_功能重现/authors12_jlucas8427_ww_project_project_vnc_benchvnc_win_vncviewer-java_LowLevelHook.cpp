#include <iostream>
#include <Windows.h>
#include <mutex>

std::mutex mtx;
HHOOK hHook = NULL;

// VNC客户端类
class VNCClient {
public:
    // 发送键盘事件到VNC服务器的函数
    void sendKeyEvent(UINT message, WPARAM wParam, LPARAM lParam) {
        // 在这里实现将按键事件发送到VNC服务器的代码
        std::cout << "Sending key event to VNC server" << std::endl;
    }
};

VNCClient vncClient;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT *kbHookStruct = (KBDLLHOOKSTRUCT *)lParam;

    // 截获ALT+TAB、ALT+ESC和CTRL+ESC组合键
    if ((kbHookStruct->vkCode == VK_TAB && (GetAsyncKeyState(VK_MENU) & 0x8000)) ||
        (kbHookStruct->vkCode == VK_ESCAPE && (GetAsyncKeyState(VK_MENU) & 0x8000)) ||
        (kbHookStruct->vkCode == VK_ESCAPE && (GetAsyncKeyState(VK_CONTROL) & 0x8000))) {

        std::unique_lock<std::mutex> lock(mtx);
        vncClient.sendKeyEvent(wParam, kbHookStruct->vkCode, kbHookStruct->flags);
        lock.unlock();

        return 1;
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void InstallHook() {
    if (hHook != NULL) {
        std::cout << "Hook is already installed" << std::endl;
        return;
    }

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (hHook == NULL) {
        std::cout << "Failed to install hook" << std::endl;
    } else {
        std::cout << "Hook installed successfully" << std::endl;
    }
}

void UninstallHook() {
    if (hHook == NULL) {
        std::cout << "Hook is not installed" << std::endl;
        return;
    }

    if (UnhookWindowsHookEx(hHook)) {
        hHook = NULL;
        std::cout << "Hook uninstalled successfully" << std::endl;
    } else {
        std::cout << "Failed to uninstall hook" << std::endl;
    }
}

int main() {
    InstallHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UninstallHook();

    return 0;
}
