#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Co-simulation API and RV32I processor headers
#include "osvvm_api.h"
#include "rv32i_processor.h"

// Transaction type definition for generating TCP/IP socket script
struct WriteTransaction {
    uint32_t addr;
    uint64_t data;
    unsigned int size;
};

// Callback function for memory access
int memcosim(uint32_t addr, uint64_t *data, int size, bool is_write) {
    if (is_write) {
        // Generate a write transaction and call the co-simulation API
        WriteTransaction trans = {addr, *data, size};
        osvvm_write_to_bus(trans);
    } else {
        // Read from the bus using the co-simulation API
        *data = osvvm_read_from_bus(addr);
    }
    return 0;
}

// Function to process GDB remote serial interface commands
void process_pkts(int sockfd) {
    char buffer[1024];
    ssize_t n;

    while ((n = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        // Process GDB packets and call the co-simulation API
        gdb_process_pkt(buffer, n, memcosim);
    }
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));

    // Assign IP and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5000);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        exit(0);
    }

    // Start listening
    if (listen(sockfd, 5) != 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        exit(0);
    }

    socklen_t len = sizeof(cli);
    // Accept the connection
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        exit(0);
    }

    // Process GDB packets
    process_pkts(connfd);

    // Close the connection
    close(connfd);

    return 0;
}
