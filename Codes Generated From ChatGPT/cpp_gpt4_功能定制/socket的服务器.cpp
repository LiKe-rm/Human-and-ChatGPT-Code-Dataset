#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <ctime>

const int PORT = 8888;
const int MAX_CLIENTS = 100;

class Server {
public:
    Server();
    ~Server();

    bool Init();
    void Run();
    void Close();

private:
    void InitFDSET(fd_set *fdset);
    void HeartBeat();
    void HandleNewConnection();
    void HandleMessage(int client_fd);

    int server_fd_;
    struct sockaddr_in server_addr_;
    std::map<int, std::string> clients_;
};

Server::Server() : server_fd_(-1) {}

Server::~Server() {
    Close();
}

bool Server::Init() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        std::cerr << "Failed to create socket. Error: " << strerror(errno) << std::endl;
        return false;
    }

    int opt = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "Failed to set socket options. Error: " << strerror(errno) << std::endl;
        return false;
    }

    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    server_addr_.sin_port = htons(PORT);

    if (bind(server_fd_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) == -1) {
        std::cerr << "Failed to bind socket. Error: " << strerror(errno) << std::endl;
        return false;
    }

    if (listen(server_fd_, MAX_CLIENTS) == -1) {
        std::cerr << "Failed to listen on socket. Error: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}

void Server::InitFDSET(fd_set *fdset) {
    FD_ZERO(fdset);
    FD_SET(server_fd_, fdset);

    for (const auto &client : clients_) {
        FD_SET(client.first, fdset);
    }
}

void Server::Run() {
    fd_set read_fds;

    while (true) {
        InitFDSET(&read_fds);
        int activity = select(FD_SETSIZE, &read_fds, nullptr, nullptr, nullptr);

        if (activity == -1) {
            std::cerr << "Failed to select. Error: " << strerror(errno) << std::endl;
            break;
        }

        if (FD_ISSET(server_fd_, &read_fds)) {
            HandleNewConnection();
        }

        for (const auto &client : clients_) {
            int client_fd = client.first;
            if (FD_ISSET(client_fd, &read_fds)) {
                HandleMessage(client_fd);
            }
        }

        HeartBeat();
    }
}

void Server::Close() {
    for (const auto &client : clients_) {
        close(client.first);
    }

    if (server_fd_ != -1) {
        close(server_fd_);
    }

    clients_.clear();
}

void Server::HeartBeat() {
    static time_t last_time = time(nullptr);

    if (time(nullptr) - last_time >= 60) {
        // Perform the tasks every 60 seconds
        // Save player count
        // Ping database, etc.

        last_time = time(nullptr);
    }
}

void Server::HandleNewConnection() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd_, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        std::cerr << "Failed to accept new connection. Error: " << strerror(errno) << std::endl;
        return;
    }

    std::string client_ip = inet_ntoa(client_addr.sin_addr);
    std::cout << "New client connected: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

    clients_[client_fd] = client_ip;
}

void Server::HandleMessage(int client_fd) {
    char buffer[1024];
    ssize_t received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (received == -1) {
        std::cerr << "Failed to receive message. Error: " << strerror(errno) << std::endl;
        return;
    }

    if (received == 0) {
        std::cout << "Client " << clients_[client_fd] << " disconnected." << std::endl;
        close(client_fd);
        clients_.erase(client_fd);
        return;
    }

    buffer[received] = '\0';
    std::string message(buffer);

    std::cout << "Message from client " << clients_[client_fd] << ": " << message << std::endl;

    for (const auto &client : clients_) {
        if (client.first == client_fd) {
            continue;
        }

        if (send(client.first, buffer, received, 0) == -1) {
            std::cerr << "Failed to send message to client. Error: " << strerror(errno) << std::endl;
        }
    }
}