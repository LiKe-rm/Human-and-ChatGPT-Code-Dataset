#include <Windows.h>

// ���崰�������ʹ��ڱ���
const wchar_t* g_szClassName = L"MyWinClass";
const wchar_t* g_szWindowTitle = L"My Window";

// ���崰�ھ���� DPI ���ű���
HWND g_hWnd = NULL;
float g_dpiScaleX = 1.0f;
float g_dpiScaleY = 1.0f;

// ���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        // �����ڴ�����Ϣ
        case WM_CREATE:
            {
                // ����һ����ť�ؼ�
                HWND hButton = CreateWindowExW(0, L"BUTTON", L"Click Me", WS_VISIBLE | WS_CHILD, 10, 10, 100, 30, hWnd, (HMENU)1, NULL, NULL);
                if (hButton == NULL)
                {
                    MessageBoxW(hWnd, L"Failed to create button control!", g_szWindowTitle, MB_OK | MB_ICONERROR);
                    return -1;
                }

                break;
            }

            // ����ť�����Ϣ
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

            // ���� DPI ������Ϣ
        case WM_DPICHANGED:
            {
                // ��ȡ�µ� DPI ���ű���
                int dpiX = LOWORD(wParam);
                int dpiY = HIWORD(wParam);
                g_dpiScaleX = (float)dpiX / USER_DEFAULT_SCREEN_DPI;
                g_dpiScaleY = (float)dpiY / USER_DEFAULT_SCREEN_DPI;

                // ���´���λ�úʹ�С
                RECT* pRect = (RECT*)lParam;
                SetWindowPos(hWnd, NULL, pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top, SWP_NOZORDER | SWP_NOACTIVATE);

                break;
            }

            // ����رմ�����Ϣ
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        // �������ٴ�����Ϣ
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
    // ע�ᴰ����
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

    // ��ȡϵͳ DPI ���ű���
    HDC hDC = GetDC(NULL);
    g_dpiScaleX = (float)GetDeviceCaps(hDC, LOGPIXELSX) / USER_DEFAULT_SCREEN_DPI;
    g_dpiScaleY = (float)GetDeviceCaps(hDC, LOGPIXELSY) / USER_DEFAULT_SCREEN_DPI;
    ReleaseDC(NULL, hDC);

    // ��������
    g_hWnd = CreateWindowExW(0, g_szClassName, g_szWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (g_hWnd == NULL)
    {
        MessageBoxW(NULL, L"Failed to create window!", g_szWindowTitle, MB_OK | MB_ICONERROR);
        return -1;
    }

    // ��ʾ����
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    // ��Ϣѭ��
    MSG msg ={ 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
