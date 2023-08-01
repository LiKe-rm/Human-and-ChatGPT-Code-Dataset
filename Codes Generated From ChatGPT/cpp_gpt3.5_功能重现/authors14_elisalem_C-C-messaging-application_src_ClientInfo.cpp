#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

class OtherSide {
    // The implementation of the OtherSide class depends on your requirements.
};

class ClientInfo {
private:
    std::vector<OtherSide*> chatUsers;
    bool inChatRoom;
    bool connectedToServer;
    OtherSide* UDPmsgr;
    std::map<std::string, std::string> connectedUsers;
    std::set<std::string> registeredUsers;
    std::set<std::string> activeChatRooms;
    
public:
    ClientInfo() : inChatRoom(false), connectedToServer(false), UDPmsgr(nullptr) {}

    void clearChatUsers() {
        chatUsers.clear();
    }

    bool isInChatRoomOrSession() {
        return inChatRoom;
    }

    bool isConnectedToServer() {
        return connectedToServer;
    }

    void removeFromChatRoomAndDeleteUDPmsgr() {
        inChatRoom = false;
        delete UDPmsgr;
        UDPmsgr = nullptr;
    }

    void printConnectedUsers() {
        for (const auto& user : connectedUsers) {
            std::cout << "User: " << user.first << ", IP: " << user.second << std::endl;
        }
    }

    void printUserStatus() {
        std::cout << "Connected to server: " << (connectedToServer ? "Yes" : "No") << std::endl;
        std::cout << "In chat room or session: " << (inChatRoom ? "Yes" : "No") << std::endl;
    }

    void printActiveChatRooms() {
        for (const auto& room : activeChatRooms) {
            std::cout << "Active Chat Room: " << room << std::endl;
        }
    }

    void printRegisteredUsers() {
        for (const auto& user : registeredUsers) {
            std::cout << "Registered User: " << user << std::endl;
        }
    }

    void getAndPrintConnectedUsers() {
        // This function should query the server for the connected users and then call printConnectedUsers.
    }

    void getAndPrintRegisteredUsers() {
        // This function should query the server for the registered users and then call printRegisteredUsers.
    }

    void getAndPrintActiveChatRooms() {
        // This function should query the server for the active chat rooms and then call printActiveChatRooms.
    }

    void getAndPrintUsersInSpecificRoom(const std::string& room) {
        // This function should query the server for the users in the specific room and then print them.
    }
};
