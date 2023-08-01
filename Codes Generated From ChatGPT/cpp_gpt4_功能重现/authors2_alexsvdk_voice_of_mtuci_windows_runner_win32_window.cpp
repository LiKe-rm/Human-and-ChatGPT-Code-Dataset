#include <Windows.h>
#include <string>

class WindowClassRegistrar;
class Win32Window;

static int g_active_window_count = 0;

class Win32Window {
    public:
    Win32Window(const std::wstring& title, int width, int height);
    ~Win32Window();

    HWND GetHandle() const { return hwnd_; }

    protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    virtual void OnClose() { DestroyWindow(hwnd_); }
    virtual void OnMove(int x, int y) {}
    virtual void OnResize(int width, int height) {}

    private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    void RegisterWindowClass();
    void CreateWindowInstance(const std::wstring& title, int width, int height);
    void EnableFullDpiSupportIfAvailable();

    int Scale(int value) const;
    HWND hwnd_ = nullptr;
    static WindowClassRegistrar* window_class_registrar_;
};

class WindowClassRegistrar {
    public:
    WindowClassRegistrar(const std::wstring& class_name);
    ~WindowClassRegistrar();

    const std::wstring& GetWindowClass() const { return class_name_; }
    bool IsClassRegistered() const { return class_registered_; }

    void RegisterWindowClass();
    void UnregisterWindowClass();

    private:
    std::wstring class_name_;
    bool class_registered_ = false;
};

WindowClassRegistrar* Win32Window::window_class_registrar_ = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    Win32Window window(L"Win32 Window Manager", 800, 600);
    ShowWindow(window.GetHandle(), nCmdShow);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

Win32Window::Win32Window(const std::wstring& title, int width, int height) {
    RegisterWindowClass();
    CreateWindowInstance(title, width, height);
    EnableFullDpiSupportIfAvailable();
    ++g_active_window_count;
}

Win32Window::~Win32Window() {
    if (--g_active_window_count == 0) {
        window_class_registrar_->UnregisterWindowClass();
        delete window_class_registrar_;
        window_class_registrar_ = nullptr;
    }
}

LRESULT Win32Window::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CLOSE:
            OnClose();
            return 0;
        case WM_MOVE:
            OnMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_SIZE:
            OnResize(LOWORD(lParam), HIWORD(lParam));
            return 0;
        default:
            return DefWindowProc(hwnd_, message, wParam, lParam);
    }
}

LRESULT CALLBACK Win32Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Win32Window* window = nullptr;

    if (message == WM_CREATE) {
        CREATESTRUCT* create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = static_cast<Win32Window*>(create_struct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        window->hwnd_ = hwnd;
    } else {
        window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window) {
        return window->WindowProc(message, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

void Win32Window::RegisterWindowClass() {
    if (!window_class_registrar_) {
        window_class_registrar_ = new WindowClassRegistrar(L"Win32Window");
        window_class_registrar_->RegisterWindowClass();
    }
}

void Win32Window::CreateWindowInstance(const std::wstring& title, int width, int height) {
    hwnd_ = CreateWindowEx(0, window_class_registrar_->GetWindowClass().c_str(), title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), this);
}

void Win32Window::EnableFullDpiSupportIfAvailable() {
    HMODULE user32_module = GetModuleHandle(L"user32.dll");
    if (user32_module) {
        auto SetProcessDpiAwarenessContext = reinterpret_cast<decltype(&::SetProcessDpiAwarenessContext)>(
            GetProcAddress(user32_module, "SetProcessDpiAwarenessContext"));
        if (SetProcessDpiAwarenessContext) {
            SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        }
    }
}

int Win32Window::Scale(int value) const {
    const int dpi




        528893699h@gmail.com
        continue
        = GetDpiForWindow(hwnd_);
    return MulDiv(value, dpi, 96);
}

WindowClassRegistrar::WindowClassRegistrar(const std::wstring& class_name)
    : class_name_(class_name) {}

WindowClassRegistrar::~WindowClassRegistrar() {
    UnregisterWindowClass();
}

void WindowClassRegistrar::RegisterWindowClass() {
    if (!class_registered_) {
        WNDCLASS wc ={};
        wc.lpfnWndProc = Win32Window::WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = class_name_.c_str();
        if (RegisterClass(&wc)) {
            class_registered_ = true;
        } else {
            throw std::runtime_error("Failed to register window class");
        }
    }
}

void WindowClassRegistrar::UnregisterWindowClass() {
    if (class_registered_) {
        UnregisterClass(class_name_.c_str(), GetModuleHandle(nullptr));
        class_registered_ = false;
    }
}