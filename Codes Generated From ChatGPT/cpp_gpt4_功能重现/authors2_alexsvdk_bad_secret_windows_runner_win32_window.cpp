#include <Windows.h>
#include <string>

class Win32Window : public WNDCLASS {
public:
    Win32Window(HINSTANCE hInstance, const std::wstring& windowTitle, int x, int y, int width, int height);
    ~Win32Window();

    bool RegisterClass();
    bool Create();
    int Run();

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
    HWND hWnd;
    HINSTANCE hInstance;
    std::wstring windowTitle;
    int x, y, width, height;
};

Win32Window::Win32Window(HINSTANCE hInstance, const std::wstring& windowTitle, int x, int y, int width, int height)
    : hInstance(hInstance), windowTitle(windowTitle), x(x), y(y), width(width), height(height) {
    this->style = CS_HREDRAW | CS_VREDRAW;
    this->lpfnWndProc = WindowProc;
    this->cbClsExtra = 0;
    this->cbWndExtra = 0;
    this->hInstance = hInstance;
    this->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    this->hCursor = LoadCursor(NULL, IDC_ARROW);
    this->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    this->lpszMenuName = NULL;
    this->lpszClassName = L"Win32Window";
}

Win32Window::~Win32Window() {
    UnregisterClass(this->lpszClassName, this->hInstance);
}

bool Win32Window::RegisterClass() {
    if (!::RegisterClass(this)) {
        MessageBox(NULL, L"Failed to register window class", L"Error", MB_OK);
        return false;
    }
    return true;
}

bool Win32Window::Create() {
    hWnd = CreateWindow(
        this->lpszClassName,
        windowTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        x, y, width, height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_OK);
        return false;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    return true;
}

int Win32Window::Run() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Win32Window window(hInstance, L"My Win32 Window", CW_USEDEFAULT, CW_USEDEFAULT, 800, 600);

    if (!window.RegisterClass()) {
        return -1;
    }

    if (!window.Create()) {
        return -1;
    }

    return window.Run();
}
