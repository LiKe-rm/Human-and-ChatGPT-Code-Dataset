#include <windows.h>
#include <string>

class WindowClassRegistrar {
    public:
    WindowClassRegistrar(HINSTANCE hInstance, const std::wstring& className)
        : m_hInstance(hInstance), m_className(className), m_refCount(0) {}

    bool Register() {
        if (m_refCount++ == 0) {
            WNDCLASSEX wc ={};
            wc.cbSize = sizeof(wc);
            wc.hInstance = m_hInstance;
            wc.lpszClassName = m_className.c_str();
            wc.lpfnWndProc = &WndProc;
            return RegisterClassEx(&wc) != 0;
        }
        return true;
    }

    bool Unregister() {
        if (--m_refCount == 0) {
            return UnregisterClass(m_className.c_str(), m_hInstance) != 0;
        }
        return true;
    }

    const std::wstring& GetName() const { return m_className; }

    private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    HINSTANCE m_hInstance;
    std::wstring m_className;
    int m_refCount;
};

class Win32Window {
    public:
    Win32Window(HINSTANCE hInstance, const std::wstring& title, int width, int height)
        : m_hInstance(hInstance), m_title(title), m_width(width), m_height(height),
        m_hWnd(nullptr), m_scalingFactor(1.0f) {}

    bool Create() {
        m_classReg = std::make_unique<WindowClassRegistrar>(m_hInstance, L"Win32Window");
        if (!m_classReg->Register()) {
            return false;
        }

        RECT rc ={ 0, 0, Scale(m_width), Scale(m_height) };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        m_hWnd = CreateWindowEx(0, m_classReg->GetName().c_str(), m_title.c_str(),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, this);
        return m_hWnd != nullptr;
    }

    void Show(int nCmdShow) { ShowWindow(m_hWnd, nCmdShow); }

    void Update() {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    bool IsOpen() const {
        MSG msg;
        return PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE) == TRUE || IsWindow(m_hWnd);
    }

    void Close() { DestroyWindow(m_hWnd); }

    int GetWidth() const { return m_width; }

    int GetHeight() const { return m_height; }

    float GetScalingFactor() const { return m_scalingFactor; }

    void SetScalingFactor(float factor) { m_scalingFactor = factor; }

    HWND GetHandle() const { return m_hWnd; }

    private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Win32Window* window = nullptr;
        if (msg == WM_NCCREATE) {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = static_cast<Win32Window*>(cs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        } else {
            window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (window) {
            switch (msg) {
                case WM_SIZE:
                    window->OnSize(LOWORD(lParam), HIWORD(lParam));
                    return 0;
            }
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    void OnSize(int width, int height) {
        m_width = width;
        m_height = height;
    }

    int Scale(int value) const {
        return static_cast<int>(value * m_scalingFactor);
    }

    HINSTANCE m_hInstance;
    std::wstring m_title;
    int m_width;
    int m_height;
    HWND m_hWnd;
    float m_scalingFactor;
    std::unique_ptr<WindowClassRegistrar> m_classReg;
};

void EnableFullDpiSupportIfAvailable() {
    HMODULE user32 = LoadLibrary(L"user32.dll");
    if (user32 != nullptr) {
        typedef BOOL(WINAPI *LPFN_ENABLENONCLIENTDPISCALING)(HWND);
        LPFN_ENABLENONCLIENTDPISCALING pfnEnableNonClientDpiScaling = reinterpret_cast<LPFN_ENABLENONCLIENTDPISCALING>(
            GetProcAddress(user32, "EnableNonClientDpiScaling"));
        if (pfnEnableNonClientDpiScaling != nullptr) {
            HWND hwnd = CreateWindow(L"STATIC", L"Dummy", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr,
                nullptr, nullptr);
            if (hwnd != nullptr) {
                pfnEnableNonClientDpiScaling(hwnd);
                DestroyWindow(hwnd);
            }
        }
        FreeLibrary(user32);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    EnableFullDpiSupportIfAvailable();
    Win32Window window(hInstance, L"Hello, Win32!", 640, 480);
    if (!window.Create()) {
        return -1;
    }

    window.Show(nCmdShow);

    while (window.IsOpen()) {
        window.Update();
    }

    return 0;
}
