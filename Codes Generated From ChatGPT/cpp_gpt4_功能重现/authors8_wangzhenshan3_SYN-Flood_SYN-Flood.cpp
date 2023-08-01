#include <iostream>
#include <string>
#include <pcap.h>
#include <Winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <stdint.h>

#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")

using namespace std;

// 定义各种报文的格式
struct ethernet_header {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t type;
};

struct ip_header {
    uint8_t ihl_version;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

struct tcp_header {
    uint16_t source;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack_seq;
    uint16_t res1_doff_res2;
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
};

struct pseudo_header {
    uint32_t saddr;
    uint32_t daddr;
    uint8_t zero;
    uint8_t protocol;
    uint16_t len;
};

// 函数声明
void get_local_interfaces();
void get_mac_address(const char *device, uint8_t *mac_address);
string get_ip_address(const string &domain);
void create_syn_packet(uint8_t *packet, uint32_t src_ip, uint32_t dest_ip,
                       uint16_t src_port, uint16_t dest_port, uint32_t seq_number);
uint16_t calculate_checksum(uint8_t *packet, size_t len);
void send_packet(const char *device, uint8_t *packet, size_t packet_len);

int main() {
    // 获取本地网络接口信息
    get_local_interfaces();

    // 获取某个网站的IP地址
    string domain = "www.example.com";
    string ip = get_ip_address(domain);
    cout << "IP address of " << domain << ": " << ip << endl;

    // 使用pcap库发送构造好的包
    char device[] = "\\Device\\NPF_{YOUR_DEVICE_ID}";
    uint8_t mac_address[6];
    get_mac_address(device, mac_address);
    cout << "MAC address: ";
    for (int i = 0; i < 6; i++) {
        printf("%02X", mac_address[i]);
        if (i < 5)
            cout << ":";
    }
    cout << endl;

    uint32_t src_ip = inet_addr("192.168.1.100");
    uint32_t dest_ip = inet_addr(ip.c_str());
    uint16_t src_port = 12345;
    uint16_t dest_port = 80;

    uint8_t packet[sizeof(ethernet_header) + sizeof(ip_header) + sizeof(tcp_header)];
    create_syn_packet(packet, src_ip, dest_ip, src_port, dest_port, 0);

    // 主函数中循环发送构建好的SYN包，修改了源地址、端口、序列号等部分信息，实现端口扫描的效果
    for (int i = 0; i < 10; i++) {
        create_syn_packet(packet, src_ip, dest_ip, src_port + i, dest_port, i);
        send_packet(device, packet, sizeof(packet));
        Sleep(1000);
    }
    return 0;
}

void get_local_interfaces() {
    pcap_if_t *alldevs, *d;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
        cerr << "Error in pcap_findalldevs_ex: " << errbuf << endl;
        exit(1);
    }

    cout << "List of available network interfaces:" << endl;
    for (d = alldevs; d != NULL; d = d->next) {
        cout << d->name << " - " << (d->description ? d->description : "No description available") << endl;
    }
    pcap_freealldevs(alldevs);
}

void get_mac_address(const char *device, uint8_t *mac_address) {
    ULONG buffer_size = 0;
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    PIP_ADAPTER_INFO pAdapter = NULL;
    GetAdaptersInfo(NULL, &buffer_size);
    pAdapterInfo = (IP_ADAPTER_INFO *)malloc(buffer_size);

    if (GetAdaptersInfo(pAdapterInfo, &buffer_size) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (strcmp(device, pAdapter->AdapterName) == 0) {
                memcpy(mac_address, pAdapter->Address, 6);
                break;
            }
            pAdapter = pAdapter->Next;
        }
    }

    if (pAdapterInfo)
        free(pAdapterInfo);
}

string get_ip_address(const string &domain) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    addrinfo *result = NULL;
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo(domain.c_str(), "http", &hints, &result);
    sockaddr_in *addr = (sockaddr_in *)result->ai_addr;

    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr->sin_addr), ip_str, INET_ADDRSTRLEN);

    freeaddrinfo(result);
    WSACleanup();

    return string(ip_str);
}

void create_syn_packet(uint8_t *packet, uint32_t src_ip, uint32_t dest_ip,
                       uint16_t src_port, uint16_t dest_port, uint32_t seq_number) {
    ethernet_header *eth = (ethernet_header *)packet;
    ip_header *ip = (ip_header *)(packet + sizeof(ethernet_header));
    tcp_header *tcp = (tcp_header *)(packet + sizeof(ethernet_header) + sizeof(ip_header));
    // 构造以太网包
    memset(eth->dest_mac, 0xFF, 6);
    memset(eth->src_mac, 0x11, 6);
    eth->type = htons(0x0800);

    // 构造IP包
    ip->ihl_version = 0x45;
    ip->tos = 0;
    ip->tot_len = htons(sizeof(ip_header) + sizeof(tcp_header));
    ip->id = htons(0x1234);
    ip->frag_off = 0;
    ip->ttl = 64;
    ip->protocol = IPPROTO_TCP;
    ip->saddr = src_ip;
    ip->daddr = dest_ip;

    // 构造TCP包
    tcp->source = htons(src_port);
    tcp->dest = htons(dest_port);
    tcp->seq = htonl(seq_number);
    tcp->ack_seq = 0;
    tcp->res1_doff_res2 = htons(0x5002);
    tcp->window = htons(8192);
    tcp->urg_ptr = 0;

    // 计算校验和
    ip->check = 0;
    ip->check = calculate_checksum((uint8_t *)ip, sizeof(ip_header));
    tcp->check = 0;

    pseudo_header pseudo_hdr = {};
    pseudo_hdr.saddr = src_ip;
    pseudo_hdr.daddr = dest_ip;
    pseudo_hdr.protocol = IPPROTO_TCP;
    pseudo_hdr.len = htons(sizeof(tcp_header));

    uint8_t tcp_pseudo[sizeof(pseudo_header) + sizeof(tcp_header)];
    memcpy(tcp_pseudo, &pseudo_hdr, sizeof(pseudo_header));
    memcpy(tcp_pseudo + sizeof(pseudo_header), tcp, sizeof(tcp_header));

    tcp->check = calculate_checksum(tcp_pseudo, sizeof(tcp_pseudo));
}

uint16_t calculate_checksum(uint8_t *packet, size_t len) {
    uint32_t sum = 0;
    uint16_t *p = (uint16_t *)packet;
    for (size_t i = 0; i < len / 2; i++) {
        sum += ntohs(p[i]);
    }
    if (len % 2) {
        sum += packet[len - 1] << 8;
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return htons(~sum);
}

void send_packet(const char *device, uint8_t *packet, size_t packet_len) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *fp;
    if ((fp = pcap_open_live(device, 65536, 1, 1000, errbuf)) == NULL) {
        cerr << "Error in pcap_open_live: " << errbuf << endl;
        exit(1);
    }

    if (pcap_sendpacket(fp, packet, packet_len) != 0) {
        cerr << "Error in pcap_sendpacket: " << pcap_geterr(fp) << endl;
    }

    pcap_close(fp);
}
