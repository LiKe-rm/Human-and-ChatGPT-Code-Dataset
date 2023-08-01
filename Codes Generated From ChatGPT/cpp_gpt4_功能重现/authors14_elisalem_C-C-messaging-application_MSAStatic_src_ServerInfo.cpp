#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

class ServerInfo {
public:
    struct User {
        std::string username;
        std::string room;
        bool active;
    };

private:
    std::map<std::string, User> registeredUsers;
    std::set<std::string> activeUsers;
    std::map<std::string, std::set<std::string>> chatRooms;

public:
    void printSessions() {
        for (const auto& user : registeredUsers) {
            std::cout << "User: " << user.second.username
                      << ", Room: " << user.second.room
                      << ", Active: " << (user.second.active ? "Yes" : "No") << std::endl;
        }
    }

    void printUsers() {
        for (const auto& user : registeredUsers) {
            std::cout << "User: " << user.second.username << std::endl;
        }
    }

    void printActiveUsers() {
        for (const auto& username : activeUsers) {
            std::cout << "Active User: " << username << std::endl;
        }
    }

    void printUsersInSpecificRoom(const std::string& room) {
        auto it = chatRooms.find(room);
        if (it != chatRooms.end()) {
            for (const auto& username : it->second) {
                std::cout << "User in room " << room << ": " << username << std::endl;
            }
        } else {
            std::cout << "Room not found." << std::endl;
        }
    }

    bool isConnected(const std::string& username) {
        return registeredUsers.find(username) != registeredUsers.end();
    }

    void printRooms() {
        for (const auto& room : chatRooms) {
            std::cout << "Room: " << room.first << std::endl;
        }
    }

    std::set<std::string> getRoomUsers(const std::string& username) {
        auto it = registeredUsers.find(username);
        if (it != registeredUsers.end()) {
            return chatRooms[it->second.room];
        }
        return std::set<std::string>();
    }

    std::map<std::string, User> getUsers() {
        return registeredUsers;
    }

    void readFromFile(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(infile, line)) {
            std::string username, room;
            bool active;
            std::istringstream iss(line);
            if (iss >> username >> room >> active) {
                User user = {username, room, active};
                registeredUsers[username] = user;
                chatRooms[room].insert(username);
                if (active) {
                    activeUsers.insert(username);
                }
            }
        }
        infile.close();
    }

    size_t fileCountUsers(const std::string& filename) {
        size_t count = 0;
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(infile, line)) {
            count++;
        }
        infile.close();
        return count;
    }
};
