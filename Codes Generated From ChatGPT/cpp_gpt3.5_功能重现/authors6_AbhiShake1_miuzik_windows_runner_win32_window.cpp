#include <Windows.h>

// Define the window class name and window title.
constexpr auto WINDOW_CLASS_NAME = "MyWindowClass";
constexpr auto WINDOW_TITLE = "My Window Title";

// The window procedure function prototype.
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// The main entry point for the application.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    WNDCLASS wc ={};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    RegisterClass(&wc);

    // Create the window.
    HWND hWnd = CreateWindowEx(
        0,
        WINDOW_CLASS_NAME,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    if (hWnd == nullptr)
    {
        return 0;
    }

    // Enable DPI awareness.
    SetProcessDPIAware();

    // Enable non-client DPI scaling.
    EnableNonClientDpiScaling(hWnd);

    // Show the window.
    ShowWindow(hWnd, nCmdShow);

    // Run the message loop.
    MSG msg ={};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}
