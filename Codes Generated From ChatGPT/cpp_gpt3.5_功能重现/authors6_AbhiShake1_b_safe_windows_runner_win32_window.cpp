#include <Windows.h>
#include <map>

class Win32Window {
    public:
    Win32Window(const wchar_t* title, int width, int height);
    virtual ~Win32Window();

    HWND GetHandle() const { return m_hwnd; }
    void Show();
    void Close();

    virtual void OnCreate() {}
    virtual void OnUpdate() {}
    virtual void OnDestroy() {}
    virtual void OnDpiChanged(int dpi) {}

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    protected:
    HWND m_hwnd;
    int m_width;
    int m_height;
};

Win32Window::Win32Window(const wchar_t* title, int width, int height)
    : m_hwnd(nullptr), m_width(width), m_height(height)
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WNDCLASSEX wcex ={};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = L"MyWindowClass";
    RegisterClassEx(&wcex);

    m_hwnd = CreateWindowEx(0, L"MyWindowClass", title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, Scale(width), Scale(height),
        nullptr, nullptr, hInstance, this);

    if (!m_hwnd) {
        throw std::runtime_error("Failed to create window");
    }
}

Win32Window::~Win32Window()
{
    if (m_hwnd) {
        CloseWindow(m_hwnd);
    }
}

void Win32Window::Show()
{
    ShowWindow(m_hwnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hwnd);
}

void Win32Window::Close()
{
    DestroyWindow(m_hwnd);
}

LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Win32Window* pWindow = nullptr;

    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pWindow = static_cast<Win32Window*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
    } else {
        pWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pWindow) {
        switch (uMsg) {
            case WM_CREATE:
                pWindow->OnCreate();
                break;

            case WM_PAINT:
                pWindow->OnUpdate();
                break;

            case WM_DESTROY:
                pWindow->OnDestroy();
                break;

            case WM_DPICHANGED:
                pWindow->OnDpiChanged(LOWORD(wParam));
                break;

            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

class WindowClassRegistrar {
    public:
    static void Register(HINSTANCE hInstance);
    static void Unregister(HINSTANCE hInstance);

    private:
    static std::map<HINSTANCE, bool> s_registered;
};

std::map<HINSTANCE, bool> WindowClassRegistrar::s_registered;

void WindowClassRegistrar::Register(HINSTANCE hInstance)
{
    if (s_registered.find(hInstance) == s_registered.end()) {
        WNDCLASSEX     wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = Win32Window::WindowProc;
        wcex.hInstance = hInstance;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.lpszClassName = L"MyWindowClass";

        if (!RegisterClassEx(&wcex)) {
            throw std::runtime_error("Failed to register window class");
        }

        s_registered[hInstance] = true;
    }
}

void WindowClassRegistrar::Unregister(HINSTANCE hInstance)
{
    if (s_registered.find(hInstance) != s_registered.end()) {
        UnregisterClass(L"MyWindowClass", hInstance);
        s_registered.erase(hInstance);
    }
}

int Scale(int value)
{
    HDC hdc = GetDC(nullptr);
    int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
    ReleaseDC(nullptr, hdc);
    return MulDiv(value, dpi, 96);
}
