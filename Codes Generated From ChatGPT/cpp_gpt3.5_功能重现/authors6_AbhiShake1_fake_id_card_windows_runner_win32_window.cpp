#include <Windows.h>

// 定义窗口类名和窗口标题
const wchar_t* g_szClassName = L"MyWinClass";
const wchar_t* g_szWindowTitle = L"My Window";

// 定义窗口句柄和 DPI 缩放比例
HWND g_hWnd = NULL;
float g_dpiScaleX = 1.0f;
float g_dpiScaleY = 1.0f;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        // 处理窗口创建消息
        case WM_CREATE:
            {
                // 创建一个按钮控件
                HWND hButton = CreateWindowExW(0, L"BUTTON", L"Click Me", WS_VISIBLE | WS_CHILD, 10, 10, 100, 30, hWnd, (HMENU)1, NULL, NULL);
                if (hButton == NULL)
                {
                    MessageBoxW(hWnd, L"Failed to create button control!", g_szWindowTitle, MB_OK | MB_ICONERROR);
                    return -1;
                }

                break;
            }

            // 处理按钮点击消息
        case WM_COMMAND:
            {
                switch (LOWORD(wParam))
                {
                    case 1:
                        MessageBoxW(hWnd, L"Button clicked!", g_szWindowTitle, MB_OK);
                        break;
                }

                break;
            }

            // 处理 DPI 缩放消息
        case WM_DPICHANGED:
            {
                // 获取新的 DPI 缩放比例
                int dpiX = LOWORD(wParam);
                int dpiY = HIWORD(wParam);
                g_dpiScaleX = (float)dpiX / USER_DEFAULT_SCREEN_DPI;
                g_dpiScaleY = (float)dpiY / USER_DEFAULT_SCREEN_DPI;

                // 更新窗口位置和大小
                RECT* pRect = (RECT*)lParam;
                SetWindowPos(hWnd, NULL, pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top, SWP_NOZORDER | SWP_NOACTIVATE);

                break;
            }

            // 处理关闭窗口消息
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        // 处理销毁窗口消息
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 注册窗口类
    WNDCLASSW wc ={ 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = g_szClassName;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    if (!RegisterClassW(&wc))
    {
        MessageBoxW(NULL, L"Failed to register window class!", g_szWindowTitle, MB_OK | MB_ICONERROR);
        return -1;
    }

    // 获取系统 DPI 缩放比例
    HDC hDC = GetDC(NULL);
    g_dpiScaleX = (float)GetDeviceCaps(hDC, LOGPIXELSX) / USER_DEFAULT_SCREEN_DPI;
    g_dpiScaleY = (float)GetDeviceCaps(hDC, LOGPIXELSY) / USER_DEFAULT_SCREEN_DPI;
    ReleaseDC(NULL, hDC);

    // 创建窗口
    g_hWnd = CreateWindowExW(0, g_szClassName, g_szWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (g_hWnd == NULL)
    {
        MessageBoxW(NULL, L"Failed to create window!", g_szWindowTitle, MB_OK | MB_ICONERROR);
        return -1;
    }

    // 显示窗口
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    // 消息循环
    MSG msg ={ 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
