#include <iostream>
#include <string>
#include <thread>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SSLServer {
public:
    SSLServer(const std::string &cert_path, const std::string &key_path, int port) 
        : cert_path_(cert_path), key_path_(key_path), port_(port) {}

    bool initOpenSSL() {
        SSL_load_error_strings();
        OpenSSL_add_ssl_algorithms();

        ctx_ = SSL_CTX_new(TLS_server_method());
        if (!ctx_) {
            std::cerr << "Failed to create SSL context." << std::endl;
            return false;
        }

        return true;
    }

    bool loadCertificates() {
        if (SSL_CTX_use_certificate_file(ctx_, cert_path_.c_str(), SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            return false;
        }

        if (SSL_CTX_use_PrivateKey_file(ctx_, key_path_.c_str(), SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            return false;
        }

        return true;
    }

    bool bindSocket() {
        server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd_ == -1) {
            std::cerr << "Failed to create socket." << std::endl;
            return false;
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(server_fd_, (sockaddr *)&addr, sizeof(addr)) == -1) {
            std::cerr << "Failed to bind socket." << std::endl;
            return false;
        }

        return true;
    }

    bool startListening(int backlog) {
        if (listen(server_fd_, backlog) == -1) {
            std::cerr << "Failed to listen on socket." << std::endl;
            return false;
        }

        return true;
    }

    void acceptConnections() {
        while (true) {
            sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);

            int client_fd = accept(server_fd_, (sockaddr *)&client_addr, &addr_len);
            if (client_fd == -1) {
                std::cerr << "Failed to accept connection." << std::endl;
                continue;
            }

            std::thread(&SSLServer::handleConnection, this, client_fd).detach();
        }
    }

    void handleConnection(int client_fd) {
        SSL *ssl = SSL_new(ctx_);
        SSL_set_fd(ssl, client_fd);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            handleRequest(ssl);
        }

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_fd);
    }

    virtual void handleRequest(SSL *ssl) {
        // Implement your server logic here.
    }

    ~SSLServer() {
        close(server_fd_);
        SSL_CTX_free(ctx_);
        EVP_cleanup();
    }

private:
    std::string cert_path_;
    std::string key_path_;
    int port_;
    int server_fd_;
    SSL_CTX *ctx_;
};
