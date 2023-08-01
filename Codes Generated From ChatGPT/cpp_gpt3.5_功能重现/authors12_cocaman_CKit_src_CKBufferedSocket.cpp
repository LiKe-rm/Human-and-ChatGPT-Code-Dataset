#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class CKBufferedSocket {
public:
	CKBufferedSocket::CKBufferedSocket() :
		m_sock(-1),
		m_timeout(-1)
	{}

	CKBufferedSocket::CKBufferedSocket(const char* addr, int port) :
		m_sock(-1),
		m_timeout(-1)
	{
		memset(&m_sockaddr, 0, sizeof(m_sockaddr));
		m_sockaddr.sin_family = AF_INET;
		m_sockaddr.sin_port = htons(port);
		inet_pton(AF_INET, addr, &m_sockaddr.sin_addr);
		Connect();
	}

	CKBufferedSocket::CKBufferedSocket(const CKBufferedSocket& other) :
		m_sock(other.m_sock),
		m_sockaddr(other.m_sockaddr),
		m_timeout(other.m_timeout),
		m_buffer(other.m_buffer)
	{}

	CKBufferedSocket::~CKBufferedSocket()
	{
		Disconnect();
	}

	void CKBufferedSocket::SetReadTimeout(int seconds)
	{
		m_timeout = seconds;
	}

	int CKBufferedSocket::GetReadTimeout() const
	{
		return m_timeout;
	}

	std::string CKBufferedSocket::GetPendingData() const
	{
		return m_buffer;
	}

	std::string CKBufferedSocket::ReadAll()
	{
		const int BUF_SIZE = 1024;
		char buf[BUF_SIZE];
		std::string result;
		int len;
		while ((len = ReadSocket(buf, BUF_SIZE)) > 0) {
			result.append(buf, len);
		}
		return result;
	}

	std::string CKBufferedSocket::Read(int n)
	{
		char buf[n];
		int len = ReadSocket(buf, n);
		if (len > 0) {
			return std::string(buf, len);
		}
		else {
			return std::string();
		}
	}

	std::string CKBufferedSocket::ReadUntil(const char* stop)
	{
		std::string result;
		char c;
		while (ReadSocket(&c, 1) > 0) {
			result.push_back(c);
			if (result.size() >= strlen(stop) &&
				result.substr(result.size() - strlen(stop)) == stop) {
				break;
			}
		}
		return result;
	}

	std::string CKBufferedSocket::ReadLine()
	{
		return ReadUntil("\r\n");
	}

	bool CKBufferedSocket::HasStopData(const char* stop) const
	{
		return m_buffer.find(stop) != std::string::npos;
	}

	bool CKBufferedSocket::HasLine() const
	{
		return HasStopData("\r\n") || HasStopData("\n");
	}

	bool CKBufferedSocket::operator==(const CKBufferedSocket& other) const
	{
		return m_sock == other.m_sock &&
			m_sockaddr.sin_addr.s_addr == other.m_sockaddr.sin_addr.s_addr &&
			m_sockaddr.sin_port == other.m_sockaddr.sin_port;
	}

	bool CKBufferedSocket::operator!=(const CKBufferedSocket& other) const
	{
		return !(*this == other);
	}

	std::string CKBufferedSocket::ToString() const
	{
		return m_buffer;
	}

	void CKBufferedSocket::Append(const char* data, int len)
	{
		m_buffer.append(data, len);
	}

	void CKBufferedSocket::Clear()
	{
		m_buffer.clear();
	}

	void CKBufferedSocket::ClearUntil(const char* stop)
	{
		while (m_buffer.find(stop) == std::string::npos) {
			char buf[1024];
			int len = ReadSocket(buf, sizeof(buf));
			if (len > 0) {
				m_buffer.append(buf, len);
			}
			else {
				break;
			}
		}
		int pos = m_buffer.find(stop);
		if (pos != std::string::npos) {
			m_buffer.erase(0, pos + strlen(stop));
		}
	}



private:
	int m_sock;
	struct sockaddr_in m_sockaddr;
	int m_timeout;
	std::string m_buffer;

	void CKBufferedSocket::Connect()
	{
		m_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (m_sock < 0) {
			std::cerr << "Error creating socket" << std::endl;
			return;
		}
		int result = connect(m_sock, (struct sockaddr*)&m_sockaddr, sizeof(m_sockaddr));
		if (result < 0) {
			std::cerr << "Error connecting to server" << std::endl;
			Disconnect();
			return;
		}
		SetNonBlocking();
	}

	void CKBufferedSocket::Disconnect()
	{
		if (m_sock >= 0) {
			close(m_sock);
			m_sock = -1;
		}
	}

	void CKBufferedSocket::SetNonBlocking()
	{
		int flags = fcntl(m_sock, F_GETFL, 0);
		if (flags < 0) {
			std::cerr << "Error getting socket flags" << std::endl;
			return;
		}
		flags |= O_NONBLOCK;
		int result = fcntl(m_sock, F_SETFL, flags);
		if (result < 0) {
			std::cerr << "Error setting socket flags" << std::endl;
			return;
		}
	}

	int CKBufferedSocket::ReadSocket(char* buf, int len)
	{
		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(m_sock, &read_fds);
		struct timeval timeout;
		timeout.tv_sec = m_timeout;
		timeout.tv_usec = 0;
		int result = select(m_sock + 1, &read_fds, NULL, NULL, &timeout);
		if (result < 0) {
			std::cerr << "Error reading from socket" << std::endl;
			Disconnect();
			return -1;
		}
		else if (result == 0) {
			std::cerr << "Timeout reading from socket" << std::endl;
			return -1;
		}
		else {
			int n = recv(m_sock, buf, len, 0);
			if (n < 0) {
				std::cerr << "Error reading from socket" << std::endl;
				Disconnect();
				return -1;
			}
			else {
				return n;
			}
		}
	}
};

CKBufferedSocket::CKBufferedSocket() :
	m_sock(-1),
	m_timeout(-1)
{}

CKBufferedSocket::CKBufferedSocket(const char* addr, int port) :
	m_sock(-1),
	m_timeout(-1)
{
	memset(&m_sockaddr, 0, sizeof(m_sockaddr));
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(port);
	inet_pton(AF_INET, addr, &m_sockaddr.sin_addr);
	Connect();
}

CKBufferedSocket::CKBufferedSocket(const CKBufferedSocket& other) :
	m_sock(other.m_sock),
	m_sockaddr(other.m_sockaddr),
	m_timeout(other.m_timeout),
	m_buffer(other.m_buffer)
{}

CKBufferedSocket::~CKBufferedSocket()
{
	Disconnect();
}

void CKBufferedSocket::SetReadTimeout(int seconds)
{
	m_timeout = seconds;
}

int CKBufferedSocket::GetReadTimeout() const
{
	return m_timeout;
}

std::string CKBufferedSocket::GetPendingData()
{
	return m_buffer;
}

std::string CKBufferedSocket::ReadAll()
{
	const int BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	std::string result;
	int len;
	while ((len = ReadSocket(buf, BUF_SIZE)) > 0) {
		result.append(buf, len);
	}
	return result;
}
std::string CKBufferedSocket::Read(int n)
{
	char buf[n];
	int len = ReadSocket(buf, n);
	if (len > 0) {
		return std::string(buf, len);
	}
	else {
		return std::string();
	}
}

std::string CKBufferedSocket::ReadUntil(const char* stop)
{
	std::string result;
	char c;
	while (ReadSocket(&c, 1) > 0) {
		result.push_back(c);
		if (result.size() >= strlen(stop) &&
			result.substr(result.size() - strlen(stop)) == stop) {
			break;
		}
	}
	return result;
}

std::string CKBufferedSocket::ReadLine()
{
	return ReadUntil("\r\n");
}

bool CKBufferedSocket::HasStopData(const char* stop)
{
	return m_buffer.find(stop) != std::string::npos;
}

bool CKBufferedSocket::HasLine()
{
	return HasStopData("\r\n") || HasStopData("\n");
}

bool CKBufferedSocket::operator==(const CKBufferedSocket& other) const
{
	return m_sock == other.m_sock &&
		m_sockaddr.sin_addr.s_addr == other.m_sockaddr.sin_addr.s_addr &&
		m_sockaddr.sin_port == other.m_sockaddr.sin_port;
}

bool CKBufferedSocket::operator!=(const CKBufferedSocket& other) const
{
	return !(*this == other);
}

std::string CKBufferedSocket::ToString() const
{
	return m_buffer;
}

void CKBufferedSocket::Append(const char* data, int len)
{
	m_buffer.append(data, len);
}

void CKBufferedSocket::Clear()
{
	m_buffer.clear();
}

void CKBufferedSocket::ClearUntil(const char* stop)
{
	while (m_buffer.find(stop) == std::string::npos) {
		char buf[1024];
		int len = ReadSocket(buf, sizeof(buf));
		if (len > 0) {
			m_buffer.append(buf, len);
		}
		else {
			break;
		}
	}
	int pos = m_buffer.find(stop);
	if (pos != std::string::npos) {
		m_buffer.erase(0, pos + strlen(stop));
	}
}

void CKBufferedSocket::Connect()
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return;
	}
	int result = connect(m_sock, (struct sockaddr*)&m_sockaddr, sizeof(m_sockaddr));
	if (result < 0) {
		std::cerr << "Error connecting to server" << std::endl;
		Disconnect();
		return;
	}
	SetNonBlocking();
}

void CKBufferedSocket::Disconnect()
{
	if (m_sock >= 0) {
		close(m_sock);
		m_sock = -1;
	}
}

void CKBufferedSocket::SetNonBlocking()
{
	int flags = fcntl(m_sock, F_GETFL, 0);
	if (flags < 0) {
		std::cerr << "Error getting socket flags" << std::endl;
		return;
	}
	flags |= O_NONBLOCK;
	int result = fcntl(m_sock, F_SETFL, flags);
	if (result < 0) {
		std::cerr << "Error setting socket flags" << std::endl;
		return;
	}
}
int CKBufferedSocket::ReadSocket(char* buf, int len)
{
	fd_set read_fds;
	FD_ZERO(&read_fds);
	FD_SET(m_sock, &read_fds);
	struct timeval timeout;
	timeout.tv_sec = m_timeout;
	timeout.tv_usec = 0;
	int result = select(m_sock + 1, &read_fds, NULL, NULL, &timeout);
	if (result < 0) {
		std::cerr << "Error reading from socket" << std::endl;
		Disconnect();
		return -1;
	}
	else if (result == 0) {
		std::cerr << "Timeout reading from socket" << std::endl;
		return -1;
	}
	else {
		int n = recv(m_sock, buf, len, 0);
		if (n < 0) {
			std::cerr << "Error reading from socket" << std::endl;
			Disconnect();
			return -1;
		}
		else {
			return n;
		}
	}
}

// Example usage
int main()
{
	CKBufferedSocket socket("localhost", 8080);
	socket.SetReadTimeout(5); // set read timeout to 5 seconds
	socket.Append("Hello, world!\r\n", 14); // append data to socket buffer
	std::string data = socket.ReadLine(); // read a line from socket buffer
	std::cout << data << std::endl;
	socket.Clear(); // clear socket buffer
	socket.Disconnect(); // disconnect from server
	return 0;
}
