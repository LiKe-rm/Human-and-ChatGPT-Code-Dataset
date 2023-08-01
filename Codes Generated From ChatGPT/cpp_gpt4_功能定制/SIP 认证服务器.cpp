#include <iostream>
#include <string>
#include <map>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int BUF_SIZE = 1024;
const int PORT = 5060;
const std::string OK_MSG = "200 OK";
const std::string NOT_FOUND_MSG = "404 IMSI Not Found";

std::string parse_imsi(const std::string& sip_msg) {
  const std::string IMSI_PREFIX = "IMSI=";
  size_t pos = sip_msg.find(IMSI_PREFIX);
  if (pos == std::string::npos) {
    return "";  // 没有找到 IMSI
  }

  pos += IMSI_PREFIX.size();
  size_t end_pos = sip_msg.find_first_not_of("0123456789", pos);
  return sip_msg.substr(pos, end_pos - pos);
}

void handle_sip_msg(const std::string& sip_msg, int sockfd, const sockaddr_in& client_addr,
                    std::map<std::string, std::string>& imsi_ip_table) {
  std::string imsi = parse_imsi(sip_msg);
  if (imsi.empty()) {
    std::cout << "Invalid SIP message: " << sip_msg << std::endl;
    return;
  }

  auto it = imsi_ip_table.find(imsi);
  if (it == imsi_ip_table.end()) {
    sendto(sockfd, NOT_FOUND_MSG.c_str(), NOT_FOUND_MSG.size(), 0,
           reinterpret_cast<const sockaddr*>(&client_addr), sizeof(client_addr));
    std::cout << "IMS not found: " << imsi << std::endl;
  } else {
    sendto(sockfd, OK_MSG.c_str(), OK_MSG.size(), 0,
           reinterpret_cast<const sockaddr*>(&client_addr), sizeof(client_addr));
    std::cout << "IMS registered: " << imsi << " => " << it->second << std::endl;
  }
}

int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "Failed to create socket" << std::endl;
    return 1;
  }

  sockaddr_in server_addr, client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  if (bind(sockfd, reinterpret_cast<const sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
    std::cerr << "Failed to bind socket" << std::endl;
    close(sockfd);
    return 1;
  }

  std::map<std::string, std::string> imsi_ip_table;
  char buf[BUF_SIZE];

  while (true) {
    socklen_t addr_len = sizeof(client_addr);
    int n = recvfrom(sockfd, buf, BUF_SIZE, 0,
    reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
    if (n < 0) {
      std::cerr << "Failed to receive data" << std::endl;
      continue;
    }
    std::string sip_msg(buf, n);
    handle_sip_msg(sip_msg, sockfd, client_addr, imsi_ip_table);
  }

  close(sockfd);
  return 0;
}

