#include <iostream>
#include <string>
#include <map>
#include <set>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class ServerManager {
private:
    struct User {
        std::string username;
        SOCKET socket;
    };

    std::map<std::string, User> users;
    std::map<std::string, std::set<std::string>> chatRooms;
    SOCKET serverSocket;
    std::thread serverThread;
    std::mutex usersMutex;

    void run() {
        // Listening for user requests and processing them
    }

public:
    ServerManager() {
        // Initialize variables and start thread
        serverSocket = INVALID_SOCKET;
        serverThread = std::thread(&ServerManager::run, this);
    }

    void addUser(const std::string& username, SOCKET socket) {
        std::lock_guard<std::mutex> lock(usersMutex);
        users[username] = {username, socket};
    }

    void removeUser(const std::string& username) {
        std::lock_guard<std::mutex> lock(usersMutex);
        users.erase(username);
    }

    void openSession(const std::string& user1, const std::string& user2) {
        // Establish a connection between two users
    }

    void createChatRoom(const std::string& roomName) {
        std::lock_guard<std::mutex> lock(usersMutex);
        chatRooms[roomName] = std::set<std::string>();
    }

    void deleteChatRoom(const std::string& roomName) {
        std::lock_guard<std::mutex> lock(usersMutex);
        chatRooms.erase(roomName);
    }

    void joinChatRoom(const std::string& username, const std::string& roomName) {
        std::lock_guard<std::mutex> lock(usersMutex);
        chatRooms[roomName].insert(username);
    }

    ~ServerManager() {
        if (serverThread.joinable()) {
            serverThread.join();
        }
    }
};
