#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class Daemon
{
public:
    Daemon(int port);
    ~Daemon();

    void AddTrayIcon();
    void CheckTrayIcon();
    void RemoveTrayIcon();
    void SendTrayMsg(const std::wstring& msg, DWORD type);

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static DWORD WINAPI ListenThread(LPVOID lpParam);

    int m_port;
    HWND m_hwnd;
    SOCKET m_sock;
    NOTIFYICONDATA m_nid;
};

Daemon::Daemon(int port) : m_port(port)
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        exit(1);
    }

    // Create a dummy window
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"DaemonWindowClass";
    RegisterClass(&wc);

    m_hwnd = CreateWindow(wc.lpszClassName, L"DaemonWindow", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // Create a listening socket
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == INVALID_SOCKET)
    {
        std::cerr << "Failed to create a socket." << std::endl;
        WSACleanup();
        exit(1);
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(m_port);

    if (bind(m_sock, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to bind socket to port " << m_port << std::endl;
        closesocket(m_sock);
        WSACleanup();
        exit(1);
    }

    if (listen(m_sock, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Failed to listen on socket." << std::endl;
        closesocket(m_sock);
        WSACleanup();
        exit(1);
    }

    // Start a new thread for listening to incoming connections
    CreateThread(NULL, 0, ListenThread, this, 0, NULL);

    // Add tray icon
    AddTrayIcon();
}

Daemon::~Daemon()
{
    // Remove tray icon
    RemoveTrayIcon();

    // Close the listening socket
    closesocket(m_sock);

    // Unregister window class and destroy window
    UnregisterClass(L"DaemonWindowClass", GetModuleHandle(NULL));
    DestroyWindow(m_hwnd);

    // Clean up Winsock
    WSACleanup();
}

void Daemon::AddTrayIcon()
{
    m_nid.cbSize = sizeof(NOTIFYICONDATA);
    m_nid.hWnd = m_hwnd;
    m_nid.uID = 1;
    m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_nid.uCallbackMessage = WM_APP;
    m_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcscpy_s(m_nid.szTip, L"Daemon");
    Shell_NotifyIcon(NIM_ADD, &m_nid);
}

void Daemon::CheckTrayIcon()
{
    Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

void Daemon::RemoveTrayIcon()
{
    Shell_NotifyIcon(NIM_DELETE, &m_nid);
}

void Daemon::SendTrayMsg(const std::wstring &msg, DWORD type)
{
    m_nid.uFlags = NIF_INFO;
    m_nid.dwInfoFlags = type;
    wcscpy_s(m_nid.szInfo, msg.c_str());
    wcscpy_s(m_nid.szInfoTitle, L"Daemon");
    Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

LRESULT CALLBACK Daemon::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Daemon *daemon = reinterpret_cast<Daemon *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg)
    {
        case WM_APP:
            if (lParam == WM_LBUTTONUP)
            {
                daemon->CheckTrayIcon();
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

DWORD WINAPI Daemon::ListenThread(LPVOID lpParam)
{
    Daemon *daemon = static_cast<Daemon *>(lpParam);
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    while ((clientSocket = accept(daemon->m_sock, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        // Handle incoming connection
        // ...
        closesocket(clientSocket);
    }

    return 0;
}

int main()
{
    Daemon daemon(8080);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
