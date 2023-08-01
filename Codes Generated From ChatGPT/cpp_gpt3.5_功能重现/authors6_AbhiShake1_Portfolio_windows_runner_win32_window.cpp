#include <Windows.h>
#include <string>
#include <memory>

namespace kWindowClassName {
    const wchar_t* const kWindowClass = L"Win32Window";
}

class WindowClassRegistrar {
    public:
    static WindowClassRegistrar& GetInstance() {
        static WindowClassRegistrar instance;
        return instance;
    }

    const wchar_t* GetWindowClass() const {
        return kWindowClassName::kWindowClass;
    }

    void UnregisterWindowClass() {
        UnregisterClass(kWindowClassName::kWindowClass, GetModuleHandle(nullptr));
    }

    private:
    WindowClassRegistrar() {
        WNDCLASSEXW wc ={};
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = DefWindowProcW;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wc.lpszClassName = kWindowClassName::kWindowClass;

        RegisterClassExW(&wc);
    }

    ~WindowClassRegistrar() {
        UnregisterWindowClass();
    }

    WindowClassRegistrar(const WindowClassRegistrar&) = delete;
    WindowClassRegistrar& operator=(const WindowClassRegistrar&) = delete;
};

class Win32Window {
    public:
    explicit Win32Window(const std::wstring& title): title_(title) {}

    HWND CreateAndShow(int nCmdShow) {
        WindowClassRegistrar::GetInstance();

        const DWORD window_style = WS_OVERLAPPEDWINDOW;
        RECT window_rect ={ 0, 0, 640, 480 };
        AdjustWindowRect(&window_rect, window_style, FALSE);

        hwnd_ = CreateWindowExW(0,
            kWindowClassName::kWindowClass,
            title_.c_str(),
            window_style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            window_rect.right - window_rect.left,
            window_rect.bottom - window_rect.top,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            this);

        if (!hwnd_) {
            return nullptr;
        }

        ShowWindow(hwnd_, nCmdShow);
        UpdateWindow(hwnd_);

        return hwnd_;
    }

    void Close() {
        DestroyWindow(hwnd_);
    }

    void Maximize() {
        ShowWindow(hwnd_, SW_MAXIMIZE);
    }

    void Minimize() {
        ShowWindow(hwnd_, SW_MINIMIZE);
    }

    void Restore() {
        ShowWindow(hwnd_, SW_RESTORE);
    }

    void SetTitle(const std::wstring& title) {
        title_ = title;
        SetWindowTextW(hwnd_, title_.c_str());
    }

    std::wstring GetTitle() const {
        const int title_length = GetWindowTextLengthW(hwnd_);
        std::wstring title(title_length, L'\0');
        GetWindowTextW(hwnd_, title.data(), title_length + 1);
        return title;
    }

    void SetSize(int width, int height) {
        SetWindowPos(hwnd_, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    }

    void SetPosition(int x, int y) {
        SetWindowPos(hwnd_, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    int GetWidth() const {
        RECT rect ={};
        GetClientRect(hwnd_, &rect);
        return rect.right - rect.left;
    }

    int GetHeight() const {
        RECT rect ={};
        GetClientRect(hwnd_, &rect);
        return rect.bottom -top;
    }
    void SetFullScreen(bool full_screen) {
        if (full_screen) {
            SetWindowLongPtrW(hwnd_, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(hwnd_, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
        } else {
            SetWindowLongPtrW(hwnd_, GWL_STYLE, WS_OVERLAPPEDWINDOW);
            SetWindowPos(hwnd_, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }
    }

    void* GetUserData() const {
        return GetWindowLongPtrW(hwnd_, GWLP_USERDATA);
    }

    void SetUserData(void* data) {
        SetWindowLongPtrW(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
    }
    protected:
    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_CREATE:
                SetUserData(reinterpret_cast<void*>(this));
                OnCreate();
                break;
            case WM_DESTROY:
                SetUserData(nullptr);
                OnDestroy();
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProcW(hwnd_, message, wParam, lParam);
        }
        return 0;
    }
    private:
    std::wstring title_;
    HWND hwnd_;
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        if (window) {
            return window->WndProc(message, wParam, lParam);
        }
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
    top;
}

scss
Copy code
void SetFullScreen(bool full_screen) {
    if (full_screen) {
        SetWindowLongPtrW(hwnd_, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hwnd_, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
    } else {
        SetWindowLongPtrW(hwnd_, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPos(hwnd_, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

void* GetUserData() const {
    return GetWindowLongPtrW(hwnd_, GWLP_USERDATA);
}

void SetUserData(void* data) {
    SetWindowLongPtrW(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
}
    protected:
    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_CREATE:
                SetUserData(reinterpret_cast<void*>(this));
                OnCreate();
                break;
            case WM_DESTROY:
                SetUserData(nullptr);
                OnDestroy();
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProcW(hwnd_, message, wParam, lParam);
        }

        kotlin
            Copy code
            return 0;
    }
    private:
    std::wstring title_;
    HWND hwnd_;

    scss
        Copy code
        static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        if (window) {
            return window->WndProc(message, wParam, lParam);
        }
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
};

void EnableFullDpiSupportIfAvailable() {
    HINSTANCE hUser32 = LoadLibraryExW(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (hUser32) {
        typedef BOOL(WINAPI* EnableNonClientDpiScalingProc)(HWND);
        EnableNonClientDpiScalingProc enable_non_client_dpi_scaling = reinterpret_cast<EnableNonClientDpiScalingProc>(
            GetProcAddress(hUser32, "EnableNonClientDpiScaling"));
        if (enable_non_client_dpi_scaling) {
            HWND hwnd = CreateWindowExW(0,
                kWindowClassName::kWindowClass,
                L"",
                WS_OVERLAPPEDWINDOW,
                0, 0,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                nullptr,
                nullptr,
                GetModuleHandle(nullptr),
                nullptr);
            enable_non_client_dpi_scaling(hwnd);
            DestroyWindow(hwnd);
        }
        FreeLibrary(hUser32);
    }
}

float Scale(int value) {
    static const float dpi_scale = static_cast<float>(GetDpiForSystem()) / 96.0f;
    return static_cast<float>(value) * dpi_scale;
}