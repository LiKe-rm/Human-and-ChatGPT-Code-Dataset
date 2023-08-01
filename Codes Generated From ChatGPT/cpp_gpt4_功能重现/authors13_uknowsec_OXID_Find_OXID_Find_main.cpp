#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

std::mutex mtx;
CRITICAL_SECTION criticalSection;

struct DeviceInfo {
    std::string deviceName;
    std::string ipAddress;
};

bool oxid1(const std::string& ip, DeviceInfo& deviceInfo) {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        return false;
    }

    // Create a socket
    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // Connect to the server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPtonA(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(135);

    result = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (result == SOCKET_ERROR) {
        std::cerr << "Unable to connect to " << ip << " Error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }

    // Send the MAC address request messages
    char buffer_v1[] = {/* ... */};
    char buffer_v2[] = {/* ... */};

    result = send(ConnectSocket, buffer_v1, sizeof(buffer_v1), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }

    result = send(ConnectSocket, buffer_v2, sizeof(buffer_v2), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }

    // Receive the response
    char recvbuf[512];
    int recvbuflen = 512;
    result = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (result > 0) {
        // Process the response to get the device name and IP address
        deviceInfo.deviceName = /* ... */;
        deviceInfo.ipAddress = ip;
    }
    else if (result == 0) {
        std::cerr << "Connection closed" << std::endl;
    }
    else {
        std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
    }

    // Clean up
    closesocket(ConnectSocket);
    WSACleanup();
    return result > 0;
}

void search_devices(const std::vectorstd::string& ips) {
    for (const auto& ip : ips) {
        DeviceInfo deviceInfo;
        if (oxid1(ip, deviceInfo)) {
            EnterCriticalSection(&criticalSection);
            std::cout << "Device Name: " << deviceInfo.deviceName << ", IP Address: " << deviceInfo.ipAddress << std::endl;
            LeaveCriticalSection(&criticalSection);
        }
    }
}

int main() {
    InitializeCriticalSection(&criticalSection);
    // Replace the below vector with the actual list of CIDR or IP addresses
    std::vector<std::string> ips = {
        "192.168.1.1",
        "192.168.1.2",
        // ...
    };

    // Set up multithreading
    const size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    for (size_t i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(search_devices, std::ref(ips));
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    DeleteCriticalSection(&criticalSection);

    return 0;
}

