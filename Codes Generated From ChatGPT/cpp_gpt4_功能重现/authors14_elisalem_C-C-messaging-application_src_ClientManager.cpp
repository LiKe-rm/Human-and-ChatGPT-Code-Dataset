#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "ClientInfo.h" // Include the ClientInfo class from the previous example
#include "TCPSocket.h" // You need to implement the TCPSocket class
#include "UDPmessenger.h" // You need to implement the UDPmessenger class

#pragma comment(lib, "Ws2_32.lib")

class ClientManager {
private:
    ClientInfo clientInfo;
    TCPSocket tcpSocket;
    UDPmessenger* udpMessenger;
    std::thread readThread;

    void run() {
        // Read commands from the server and execute them
    }

public:
    ClientManager() : udpMessenger(nullptr) {}

    void connectToServer(const std::string& serverIP, int serverPort) {
        tcpSocket.connect(serverIP, serverPort);
        readThread = std::thread(&ClientManager::run, this);
    }

    void registerUser(const std::string& username, const std::string& password) {
        // Send registration request to the server
    }

    void loginUser(const std::string& username, const std::string& password) {
        // Send login request to the server
    }

    void openPeerSession(const std::string& username) {
        // Send a request to the server to open a session with another user
    }

    void sendMessage(const std::string& message) {
        // Send a message to the chat room or peer session
    }

    void createChatRoom(const std::string& roomName) {
        // Send a request to the server to create a chat room
    }

    void joinChatRoom(const std::string& roomName) {
        // Send a request to the server to join a chat room
    }

    void closeChatRoom(const std::string& roomName) {
        // Send a request to the server to close a chat room
    }

    void leaveRoomOrCloseSession() {
        // Send a request to the server to leave the room or close the session
    }

    void updateChatRoomInfo() {
        // Send a request to the server to update the chat room information
    }

    void clientExit() {
        // Send an exit request to the server and clean up resources
    }

    void clearOtherSideVector() {
        clientInfo.clearChatUsers();
    }

    void chatRoomAddUser(OtherSide* otherSide) {
        // Add a user to the chat room user vector
    }

    ~ClientManager() {
        if (readThread.joinable()) {
            readThread.join();
        }
        delete udpMessenger;
    }
};
