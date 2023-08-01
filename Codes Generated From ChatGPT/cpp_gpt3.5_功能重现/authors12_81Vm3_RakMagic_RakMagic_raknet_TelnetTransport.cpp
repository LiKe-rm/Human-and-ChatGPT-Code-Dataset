#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

class TCPInterface {
    public:
    TCPInterface();
    virtual ~TCPInterface();
    virtual bool start(int port);
    virtual void stop();
    virtual bool send(int clientIndex, const std::string& message);
    virtual bool receive(int clientIndex, std::string& message);
    virtual void process();

    private:
    void handleNewConnection(int clientSocket);
    void handleDisconnect(int clientIndex);
    void handleData(int clientIndex, const char* buffer, int size);
    void sendCommand(int clientIndex, const char* command, int size);
    bool setBlocking(int fd, bool blocking);

    std::vector<int> m_clients;
    std::mutex m_mutex;
    int m_serverSocket;
    bool m_running;
};

TCPInterface::TCPInterface()
    : m_serverSocket(0), m_running(false) {
}

TCPInterface::~TCPInterface() {
    stop();
}

bool TCPInterface::start(int port) {
    // create socket
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return false;
    }

    // set socket options
    int enable = 1;
    if (setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        std::cerr << "Error setting socket options." << std::endl;
        return false;
    }

    // bind socket
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(m_serverSocket, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        return false;
    }

    // listen for connections
    if (listen(m_serverSocket, MAX_CLIENTS) < 0) {
        std::cerr << "Error listening on socket." << std::endl;
        return false;
    }

    // start processing thread
    m_running = true;
    std::thread processingThread(&TCPInterface::process, this);
    processingThread.detach();

    return true;
}

void TCPInterface::stop() {
    m_running = false;
    close(m_serverSocket);
    for (int client : m_clients) {
        close(client);
    }
}

bool TCPInterface::send(int clientIndex, const std::string& message) {
    m_mutex.lock();
    bool success = false;
    if (clientIndex >= 0 && clientIndex < m_clients.size()) {
        int clientSocket = m_clients[clientIndex];
        success = write(clientSocket, message.c_str(), message.length()) >= 0;
    }
    m_mutex.unlock();
    return success;
}

bool TCPInterface::receive(int clientIndex, std::string& message) {
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    m_mutex.lock();
    bool success = false;
    if (clientIndex >= 0 && clientIndex < m_clients.size()) {
        int clientSocket = m_clients[clientIndex];
        int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
        if (bytesRead > 0) {
            message = std::string(buffer, bytesRead);
            success = true;
        }
    }
    m_mutex.unlock();
    return success;
}

void TCPInterface::process() {
    while (m_running) {
    // accept new connections
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(m_serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            continue;
        }
            // handle new connection
        handleNewConnection(clientSocket);
    }
}

void TCPInterface::handleNewConnection(int clientSocket) {
// add client to list
    m_mutex.lock();
    m_clients.push_back(clientSocket);
    m_mutex.unlock();
    // send initial commands
    sendCommand(m_clients.size() - 1, "\xFF\xFB\x03\xFF\xFD\x01\xFF\xFD\x22", 9);
}

void TCPInterface::handleDisconnect(int clientIndex) {
// remove client from list
    m_mutex.lock();
    m_clients.erase(m_clients.begin() + clientIndex);
    m_mutex.unlock();
}

void TCPInterface::handleData(int clientIndex, const char* buffer, int size) {
// handle telnet special characters
    for (int i = 0; i < size; i++) {
        if (buffer[i] == 0x08 || buffer[i] == 0x7F) {
            sendCommand(clientIndex, "\x08 \x08", 3);
        } else if (buffer[i] == 0x0D) {
            sendCommand(clientIndex, "\r\n", 2);
        } else if (buffer[i] == 0x1B) {
            i++;
            if (i < size && buffer[i] == 0x5B) {
                i++;
                if (i < size && buffer[i] == 0x41) {
                    sendCommand(clientIndex, "\r\n", 2);
                } else if (i < size && buffer[i] == 0x42) {
                    sendCommand(clientIndex, "\r\n", 2);
                } else if (i < size && buffer[i] == 0x43) {
                // right arrow
                } else if (i < size && buffer[i] == 0x44) {
                // left arrow
                } else if (i < size && buffer[i] == 0x48) {
                // home
                } else if (i < size && buffer[i] == 0x4F) {
                    i++;
                    if (i < size && buffer[i] == 0x46) {
                    // end
                    }
                }
            }
        } else {
        // handle regular characters
        }
    }
}

void TCPInterface::sendCommand(int clientIndex, const char* command, int size) {
    m_mutex.lock();
    if (clientIndex >= 0 && clientIndex < m_clients.size()) {
        int clientSocket = m_clients[clientIndex];
        write(clientSocket, command, size);
    }
    m_mutex.unlock();
}

bool TCPInterface::setBlocking(int fd, bool blocking) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return false;
    }
    if (blocking) {
        flags &= ~O_NONBLOCK;
    } else {
        flags |= O_NONBLOCK;
    }
    if (fcntl(fd, F_SETFL, flags) < 0) {
        return false;
    }
    return true;
}

// TelnetServer class
class TelnetServer {
    public:
    TelnetServer(int port);
    virtual ~TelnetServer();
    void start();
    void stop();
    bool send(int clientIndex, const std::string& message);
    bool receive(int clientIndex, std::string& message);

    private:
    TCPInterface m_interface;
    int m_port;
    bool m_running;
};

TelnetServer::TelnetServer(int port)
    : m_port(port), m_running(false) {
}

TelnetServer::~TelnetServer() {
    stop();
}

void TelnetServer::start() {
    if (!m_interface.start(m_port)) {
        std::cerr << "Error starting server." << std::endl;
        return;
    }
    m_running = true;
}

void TelnetServer::stop() {
    m_running = false;
    m_interface.stop();
}

bool TelnetServer::send(int clientIndex, const std::string& message) {
    return m_interface.send(clientIndex, message);
}

bool TelnetServer::receive(int clientIndex, std::string& message) {
    return m_interface.receive(clientIndex, message);
}

int main() {
    TelnetServer server(23);
    server.start();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    server.stop();
    return 0;
}