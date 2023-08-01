#include <Windows.h>
#include <string>

class WindowClassRegistrar;

class Win32Window {
    public:
    Win32Window();
    ~Win32Window();

    bool Create(const std::wstring& title, int width, int height);
    void Show(int cmd_show);
    void Close();

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    protected:
    virtual void OnCreate() {}
    virtual void OnMove(int x, int y) {}
    virtual void OnSize(int width, int height) {}
    virtual void OnDestroy() {}

    private:
    HWND hwnd_;
    static int g_active_window_count;
    static WindowClassRegistrar window_class_registrar_;

    static int Scale(int value);
    static void EnableFullDpiSupportIfAvailable();
};

class WindowClassRegistrar {
    public:
    WindowClassRegistrar();
    ~WindowClassRegistrar();

    const wchar_t* GetWindowClass();
    void UnregisterWindowClass();

    private:
    bool class_registered_;
    std::wstring class_name_;
};

int Win32Window::g_active_window_count = 0;
WindowClassRegistrar Win32Window::window_class_registrar_;

Win32Window::Win32Window(): hwnd_(nullptr) {
    EnableFullDpiSupportIfAvailable();
}

Win32Window::~Win32Window() {
    Close();
}

bool Win32Window::Create(const std::wstring& title, int width, int height) {
    if (hwnd_)
        return false;

    hwnd_ = CreateWindowEx(0, window_class_registrar_.GetWindowClass(), title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Scale(width),
        Scale(height), nullptr, nullptr, GetModuleHandle(nullptr), this);

    return hwnd_ != nullptr;
}

void Win32Window::Show(int cmd_show) {
    if (hwnd_)
        ShowWindow(hwnd_, cmd_show);
}

void Win32Window::Close() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
        hwnd_ = nullptr;
    }
}

LRESULT CALLBACK Win32Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    Win32Window* window = nullptr;

    if (msg == WM_NCCREATE) {
        window = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        window->hwnd_ = hwnd;
        ++g_active_window_count;
    } else {
        window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window) {
        switch (msg) {
            case WM_CREATE:
                window->OnCreate();
                break;
            case WM_MOVE:
                window->OnMove(LOWORD(lparam), HIWORD(lparam));
                break;
            case WM_SIZE:
                window->OnSize(LOWORD(lparam), HIWORD(lparam));
                break;
            case WM_DESTROY:
                window->OnDestroy();
                --g_active_window_count;
                if (g_active_window_count == 0)
                    window_class_registrar_.UnregisterWindowClass();
                break;
        }
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int Win32Window::Scale(int value) {
// Implement DPI scaling logic here.
    return value;
}

void Win32Window::EnableFullDpiSupportIfAvailable() {
// Enable full DPI support if available on the system.
}

WindowClassRegistrar::WindowClassRegistrar(): class_registered_(false) {
// Generate a unique class name.
    class_name_ = L"Win32WindowClass_" + std::to_wstring(reinterpret_cast<uintptr_t>(this));
}

WindowClassRegistrar::~WindowClassRegistrar() {
    UnregisterWindowClass();
}

const wchar_t* WindowClassRegistrar::GetWindowClass() {
    if (!class_registered_) {
        WNDCLASSEX wc ={ 0 };
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = Win32Window::WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name_.c_str();
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

        if (RegisterClassEx(&wc)) {
            class_registered_ = true;
        }
    }

    return class_name_.c_str();
}

void WindowClassRegistrar::UnregisterWindowClass() {
    if (class_registered_) {
        UnregisterClass(class_name_.c_str(), GetModuleHandle(nullptr));
        class_registered_ = false;
    }
}