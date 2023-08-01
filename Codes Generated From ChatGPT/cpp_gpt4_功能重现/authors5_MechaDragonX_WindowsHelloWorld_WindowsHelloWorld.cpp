#include <windows.h>
#include <tchar.h>

// 定义常量
const TCHAR szAppName[] = _T("HelloWindowsApp");
const TCHAR szTitle[] = _T("Hello, Windows!");

// 声明窗口过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    MSG msg;

    // 注册窗口类
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szAppName;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, _T("RegisterClassEx失败!"), szAppName, MB_ICONERROR);
        return 1;
    }

    // 创建窗口
    hwnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, _T("CreateWindow失败!"), szAppName, MB_ICONERROR);
        return 1;
    }

    // 显示和更新窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    TCHAR szText[] = _T("Hello, Windows!");

    switch (message) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            // 获取文本的矩形区域
            GetClientRect(hWnd, &rect);

            // 居中文本
            DrawText(hdc, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
