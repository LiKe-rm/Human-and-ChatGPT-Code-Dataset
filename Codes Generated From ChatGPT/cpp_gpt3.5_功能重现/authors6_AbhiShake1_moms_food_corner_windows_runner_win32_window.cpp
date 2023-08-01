#include <Windows.h>
#include <stdexcept>

// ������ע����������ע�ᴰ���࣬�����ظ�����
class WindowClassRegistrar
{
    public:
        // ���캯�������봰�������ƺʹ��ڹ��̺���ָ��
    WindowClassRegistrar(const wchar_t* className, WNDPROC wndProc)
    {
        // ��鴰�����Ƿ��Ѿ���ע��
        WNDCLASSEXW wcex ={ sizeof(WNDCLASSEXW) };
        if (GetClassInfoExW(nullptr, className, &wcex) == FALSE)
        {
            // ���δע�ᣬ��ע�ᴰ����
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = sizeof(LONG_PTR);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
            wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
            wcex.hInstance = GetModuleHandleW(nullptr);
            wcex.lpfnWndProc = wndProc;
            wcex.lpszClassName = className;
            wcex.style = CS_HREDRAW | CS_VREDRAW;

            if (RegisterClassExW(&wcex) == 0)
                throw std::runtime_error("Failed to register window class");
        }
    }

    // ����������ע��������
    ~WindowClassRegistrar()
    {
    }
};

// ������
class Window
{
    public:
        // ���캯�������봰�ڱ��⡢λ�úʹ�С
    Window(const wchar_t* title, int x, int y, int width, int height)
        : m_hWnd(nullptr), m_scaleFactor(1.0f)
    {
        // ע�ᴰ����
        static WindowClassRegistrar registrar(L"MyWindowClass", Window::WndProc);

        // ��������
        m_hWnd = CreateWindowExW(0, L"MyWindowClass", title, WS_OVERLAPPEDWINDOW,
            x, y, width, height, nullptr, nullptr, GetModuleHandleW(nullptr), this);

        if (m_hWnd == nullptr)
            throw std::runtime_error("Failed to create window");

        // ��¼��ǰ������Ŀ
        ++g_active_window_count;

        // �������ű�������֧�ָ�DPI
        HDC hdc = GetDC(m_hWnd);
        int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
        ReleaseDC(m_hWnd, hdc);

        m_scaleFactor = static_cast<float>(dpiX) / 96.0f;

        // ���ô�������
        SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        SetWindowTextW(m_hWnd, title);
        ShowWindow(m_hWnd, SW_SHOW);
    }

    // �������������ٴ���
    ~Window()
    {
        if (m_hWnd != nullptr)
        {
            DestroyWindow(m_hWnd);
            --g_active_window_count;
        }
    }

    // ��ȡ���ھ��
    HWND GetHWND() const
    {
        return m_hWnd;
    }

    // ��ȡ���ű���
    float GetScaleFactor() const
    {
        return m_scaleFactor;
    }

    // ��������Ϣ
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_CLOSE:
                DestroyWindow(m_hWnd);
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_DPICHANGED:
                {
                    // �����µ����ű���
                    int dpiX = HIWORD(wParam);
                    m_scaleFactor = static_cast<float>(dpiX) / 96.0f;

                    // ���´���λ�úʹ�С
                    RECT* const prcNewWindow = reinterpret_cast<RECT*>(lParam);
                    SetWindowPos(m_hWnd, nullptr,
                        prcNewWindow->left, prcNewWindow->top,
                        prcNewWindow->right - prcNewWindow->left,
                        prcNewWindow->bottom - prcNewWindow->top,
                        SWP_NOZORDER | SWP_NOACTIVATE);
                    return 0;
                }

            default:
                return DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
        }
    }
    private:
    HWND m_hWnd; // ���ھ��
    float m_scaleFactor; // ���ű���
    // ���ڹ��̺���
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

        if (pWindow != nullptr)
        {
            return pWindow->HandleMessage(uMsg, wParam, lParam);
        } else
        {
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }
    }
};

int g_active_window_count = 0;

// ������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    try
    {
        // ��������
        Window window(L"My Window", 100, 100, 640, 480);

        // ��Ϣѭ��
        MSG msg ={};
        while (GetMessageW(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        return static_cast<int>(msg.wParam);
    } catch (const std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }
}
