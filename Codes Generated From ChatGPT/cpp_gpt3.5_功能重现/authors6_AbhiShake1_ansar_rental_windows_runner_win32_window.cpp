#include <Windows.h>
#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>

class WindowClassRegistrar {
    public:
    WindowClassRegistrar(const WNDCLASS& wnd_class): wnd_class_(wnd_class) {
        const auto instance = GetModuleHandle(nullptr);
        if (RegisterClass(&wnd_class_) == 0) {
            const auto error_code = GetLastError();
            if (error_code != ERROR_CLASS_ALREADY_EXISTS) {
              // Handle the error.
            }
        }
    }

    ~WindowClassRegistrar() {
        UnregisterClass(wnd_class_.lpszClassName, GetModuleHandle(nullptr));
    }

    private:
    const WNDCLASS& wnd_class_;
};

class Win32Window {
    public:
    Win32Window(const wchar_t* title, int x, int y, int width, int height)
        : instance_(GetModuleHandle(nullptr)), title_(title), x_(x), y_(y),
        width_(width), height_(height) {}

    bool Create() {
      // Enable non-client DPI scaling.
        EnableNonClientDpiScaling(hwnd_);

        hwnd_ = CreateWindowEx(
            WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, wnd_class_name_, title_.c_str(),
            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, x_, y_, width_,
            height_, nullptr, nullptr, instance_, this);

        return hwnd_ != nullptr;
    }

    void Destroy() {
        DestroyWindow(hwnd_);
    }

    void SetChildContent(HWND child_hwnd, int x, int y, int width, int height) {
        SetParent(child_hwnd, hwnd_);
        SetWindowPos(child_hwnd, nullptr, x, y, width, height,
            SWP_NOZORDER | SWP_SHOWWINDOW);
    }

    virtual void OnSize() {}

    virtual void OnDpiChanged(int dpi_x, int dpi_y, RECT* suggested_rect) {
        SetWindowPos(hwnd_, nullptr, suggested_rect->left, suggested_rect->top,
            suggested_rect->right - suggested_rect->left,
            suggested_rect->bottom - suggested_rect->top,
            SWP_NOZORDER | SWP_NOACTIVATE);
    }

    HWND hwnd() const { return hwnd_; }

    protected:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
        LPARAM lParam) {
        if (uMsg == WM_CREATE) {
            auto create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            auto self = reinterpret_cast<Win32Window*>(create_struct->lpCreateParams);
            self->hwnd_ = hwnd;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
        } else {
            auto self = reinterpret_cast<Win32Window*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (self != nullptr) {
                switch (uMsg) {
                    case WM_SIZE:
                        self->OnSize();
                        break;
                    case WM_DPICHANGED: {
                            const auto dpi_x = HIWORD(wParam);
                            const auto dpi_y = LOWORD(wParam);
                            RECT* suggested_rect = reinterpret_cast<RECT*>(lParam);
                            self->OnDpiChanged(dpi_x, dpi_y, suggested_rect);
                            break;
                        }
                    default:
                        break;
                }
            }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    HWND hwnd_{ nullptr };
    HINSTANCE instance_;
    std::wstring title_;
    int x_;
    int y_;
    int width_;
    int height_;
    const wchar_t* wnd_class_name_{ L"FlutterWindowClass" };
};

// Helper function to get the DPI of a given monitor.
int FlutterDesktopGetDpiForMonitor(HMONITOR monitor) {
    UINT dpi_x;
    UINT dpi_y;
    if (SUCCEEDED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpi_x, &dpi_y))) {
        return dpi_x;
    } else {
        return USER_DEFAULT_SCREEN_DPI;
    }
}

// Enable non-client DPI scaling for the given window.
void EnableNonClientDpiScaling(HWND hwnd) {
    const auto enable_non_client_dpi_scaling = static_cast<UINT>(TRUE);
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    SetWindowCompositionAttribute(hwnd, &WINDOWCOMPOSITIONATTRIBDATA{
    WCA_NCP_DPI_SCALING,
    &enable_non_client_dpi_scaling,
    sizeof(enable_non_client_dpi_scaling) });
}
