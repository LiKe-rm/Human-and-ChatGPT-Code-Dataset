#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUFF_LEN 1024

class TIsoTcpSocket {
private:
	int sock_fd;            // Socket file descriptor
	int recv_timeout;       // Receive timeout
	uint16_t remote_port;   // Remote port
	uint16_t dst_ref;       // Destination reference
	uint16_t src_ref;       // Source reference

	bool isoRecvFragment(uint8_t* buffer, uint32_t buffer_size);
public:
	TIsoTcpSocket();
	~TIsoTcpSocket();
	bool isoConnect(const char* ip_addr, uint16_t port);
	bool isoDisconnect();
	bool isoExchangeBuffer(uint8_t* send_buffer, uint32_t send_len, uint8_t* recv_buffer, uint32_t recv_len);
	bool isoPDUReady();
	bool isoSendBuffer(uint8_t* buffer, uint32_t len);
	bool isoRecvBuffer(uint8_t* buffer, uint32_t len);
	bool isoSendPDU(uint8_t* pdu, uint32_t pdu_len);
};

TIsoTcpSocket::TIsoTcpSocket() {
	sock_fd = -1;
	recv_timeout = 1000; // default timeout
	remote_port = 102;
	dst_ref = 0;
	src_ref = 0;
}

TIsoTcpSocket::~TIsoTcpSocket() {
	if (sock_fd != -1) {
		close(sock_fd);
		sock_fd = -1;
	}
}

bool TIsoTcpSocket::isoConnect(const char* ip_addr, uint16_t port) {
	// create socket
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error: Failed to create socket");
		return false;
	}

	// set timeout
	struct timeval timeout = { 0, recv_timeout * 1000 };
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
		perror("Error: Failed to set timeout");
		return false;
	}

	// set remote address
	struct sockaddr_in remote_addr;
	memset(&remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip_addr, &remote_addr.sin_addr) <= 0) {
		perror("Error: Failed to convert IP address");
		return false;
	}

	// connect to remote device
	if (connect(sock_fd, (struct sockaddr*)&remote_addr, sizeof(remote_addr)) < 0) {
		perror("Error: Failed to connect");
		return false;
	}

	return true;
}

bool TIsoTcpSocket::isoDisconnect() {
	if (sock_fd != -1) {
		close(sock_fd);
		sock_fd = -1;
		return true;
	}

	return false;
}

bool TIsoTcpSocket::isoExchangeBuffer(uint8_t* send_buffer, uint32_t send_len, uint8_t* recv_buffer, uint32_t recv_len) {
	// send data
	if (!isoSendbool TIsoTcpSocket::isoExchangeBuffer(uint8_t * send_buffer, uint32_t send_len, uint8_t * recv_buffer, uint32_t recv_len) {
		// send data
		if (!isoSendBuffer(send_buffer, send_len)) {
			return false;
		}
		// receive data
		if (!isoRecvBuffer(recv_buffer, recv_len)) {
			return false;
		}

		return true;
	}

	bool TIsoTcpSocket::isoPDUReady() {
		// TODO: Implement this method
		return false;
	}

	bool TIsoTcpSocket::isoSendBuffer(uint8_t * buffer, uint32_t len) {
		// TODO: Implement this method
		return false;
	}

	bool TIsoTcpSocket::isoRecvBuffer(uint8_t * buffer, uint32_t len) {
		// TODO: Implement this method
		return false;
	}

	bool TIsoTcpSocket::isoSendPDU(uint8_t * pdu, uint32_t pdu_len) {
		// TODO: Implement this method
		return false;
	}

	bool TIsoTcpSocket::isoRecvFragment(uint8_t * buffer, uint32_t buffer_size) {
		// TODO: Implement this method
		return false;
	}

	int main() {
		TIsoTcpSocket socket;
		// TODO: Use socket object to establish connection and communicate
		return 0;
	}
}