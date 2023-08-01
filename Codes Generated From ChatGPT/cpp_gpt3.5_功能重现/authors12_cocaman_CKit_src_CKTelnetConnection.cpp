#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

class CKString {
public:
    CKString(const char* str) {
        if (str != nullptr) {
            length_ = strlen(str);
            str_ = new char[length_ + 1];
            strcpy(str_, str);
        }
    }
    
    CKString(const CKString& other) : length_(other.length_) {
        str_ = new char[length_ + 1];
        strcpy(str_, other.str_);
    }
    
    ~CKString() {
        delete[] str_;
    }
    
    const char* c_str() const {
        return str_;
    }
    
private:
    char* str_ = nullptr;
    size_t length_ = 0;
};

class CKTelnetConnection {
public:
    CKTelnetConnection() {}
    
    CKTelnetConnection(const char* hostname) {
        connect(hostname, 23);
    }
    
    CKTelnetConnection(const char* hostname, int port) {
        connect(hostname, port);
    }
    
    ~CKTelnetConnection() {
        close(socket_);
    }
    
    bool operator==(const CKTelnetConnection& other) const {
        return socket_ == other.socket_;
    }
    
    bool operator!=(const CKTelnetConnection& other) const {
        return !(*this == other);
    }
    
    CKString toString() const {
        char buf[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr_.sin_addr, buf, INET_ADDRSTRLEN);
        return CKString(buf);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const CKTelnetConnection& conn) {
        os << conn.toString().c_str();
        return os;
    }
    
private:
    int socket_ = -1;
    sockaddr_in addr_;
    
    void connect(const char* hostname, int port) {
        addrinfo hints, *servinfo;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        
        if (getaddrinfo(hostname, nullptr, &hints, &servinfo) != 0) {
            throw std::runtime_error("Failed to get address info");
        }
        
        memcpy(&addr_, servinfo->ai_addr, servinfo->ai_addrlen);
        addr_.sin_port = htons(port);
        
        freeaddrinfo(servinfo);
        
        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        
        if (socket_ == -1) {
            throw std::runtime_error("Failed to create socket");
        }
        
        if (connect(socket_, (sockaddr*)&addr_, sizeof(addr_)) == -1) {
            throw std::runtime_error("Failed to connect");
        }
    }
};
