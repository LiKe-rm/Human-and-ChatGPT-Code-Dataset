#include <Windows.h>
#include <stdexcept>

// 窗口类注册器，用于注册窗口类，避免重复创建
class WindowClassRegistrar
{
    public:
        // 构造函数，传入窗口类名称和窗口过程函数指针
    WindowClassRegistrar(const wchar_t* className, WNDPROC wndProc)
    {
        // 检查窗口类是否已经被注册
        WNDCLASSEXW wcex ={ sizeof(WNDCLASSEXW) };
        if (GetClassInfoExW(nullptr, className, &wcex) == FALSE)
        {
            // 如果未注册，则注册窗口类
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

    // 析构函数，注销窗口类
    ~WindowClassRegistrar()
    {
    }
};

// 窗口类
class Window
{
    public:
        // 构造函数，传入窗口标题、位置和大小
    Window(const wchar_t* title, int x, int y, int width, int height)
        : m_hWnd(nullptr), m_scaleFactor(1.0f)
    {
        // 注册窗口类
        static WindowClassRegistrar registrar(L"MyWindowClass", Window::WndProc);

        // 创建窗口
        m_hWnd = CreateWindowExW(0, L"MyWindowClass", title, WS_OVERLAPPEDWINDOW,
            x, y, width, height, nullptr, nullptr, GetModuleHandleW(nullptr), this);

        if (m_hWnd == nullptr)
            throw std::runtime_error("Failed to create window");

        // 记录当前窗口数目
        ++g_active_window_count;

        // 计算缩放比例，以支持高DPI
        HDC hdc = GetDC(m_hWnd);
        int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
        ReleaseDC(m_hWnd, hdc);

        m_scaleFactor = static_cast<float>(dpiX) / 96.0f;

        // 设置窗口属性
        SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        SetWindowTextW(m_hWnd, title);
        ShowWindow(m_hWnd, SW_SHOW);
    }

    // 析构函数，销毁窗口
    ~Window()
    {
        if (m_hWnd != nullptr)
        {
            DestroyWindow(m_hWnd);
            --g_active_window_count;
        }
    }

    // 获取窗口句柄
    HWND GetHWND() const
    {
        return m_hWnd;
    }

    // 获取缩放比例
    float GetScaleFactor() const
    {
        return m_scaleFactor;
    }

    // 处理窗口消息
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
                    // 计算新的缩放比例
                    int dpiX = HIWORD(wParam);
                    m_scaleFactor = static_cast<float>(dpiX) / 96.0f;

                    // 更新窗口位置和大小
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
    HWND m_hWnd; // 窗口句柄
    float m_scaleFactor; // 缩放比例
    // 窗口过程函数
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

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    try
    {
        // 创建窗口
        Window window(L"My Window", 100, 100, 640, 480);

        // 消息循环
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
