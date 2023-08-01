#include <iostream>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <cstring>

struct packet_info {
    u_char* data;
    int length;
};

struct tcp_info {
    uint32_t seq_num;
    uint32_t server_seq_num;
};

packet_info receive_packet(pcap_t* handle);
void parse_ethernet(u_char* &data);
void parse_ip(u_char* &data);
void parse_tcp(u_char* &data, tcp_info &info);
void send_packet(pcap_t* handle, u_char* data, int length);
u_char* make_RST_packet(u_char* data, tcp_info &info);
u_char* make_FIN_packet(u_char* data, tcp_info &info);
void swap_src_dst(u_char* data);

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live("en0", BUFSIZ, 1, 1000, errbuf);

    if (handle == nullptr) {
        std::cerr << "pcap_open_live() failed: " << errbuf << std::endl;
        return 1;
    }

    packet_info packet = receive_packet(handle);
    u_char* data = packet.data;

    parse_ethernet(data);
    parse_ip(data);
    tcp_info info;
    parse_tcp(data, info);

    u_char* rst_packet = make_RST_packet(packet.data, info);
    send_packet(handle, rst_packet, packet.length);
    delete[] rst_packet;

    u_char* fin_packet = make_FIN_packet(packet.data, info);
    send_packet(handle, fin_packet, packet.length);
    delete[] fin_packet;

    pcap_close(handle);
    delete[] packet.data;
    return 0;
}

packet_info receive_packet(pcap_t* handle) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);

    if (res < 0) {
        std::cerr << "pcap_next_ex() failed: " << pcap_geterr(handle) << std::endl;
        exit(1);
    }

    u_char* packet_copy = new u_char[header->caplen];
    std::memcpy(packet_copy, packet, header->caplen);
    return {packet_copy, header->caplen};
}

void parse_ethernet(u_char* &data) {
    struct ether_header* eth_header = (struct ether_header*)data;
    data += sizeof(struct ether_header);
}

void parse_ip(u_char* &data) {
    struct ip* ip_header = (struct ip*)data;
    data += ip_header->ip_hl * 4;
}

void parse_tcp(u_char* &data, tcp_info &info) {
    struct tcphdr* tcp_header = (struct tcphdr*)data;
    info.seq_num = ntohl(tcp_header->th_seq);
    info.server_seq_num = ntohl(tcp_header->th_ack);
    data += tcp_header->th_off * 4;
}

void send_packet(pcap_t* handle, u_char* data, int length) {
    if (pcap_sendpacket(handle, data, length) != 0) {
        std::cerr << "pcap_sendpacket() failed: " << pcap_geterr(handle) << std::endl;
    }
}

u_char* make_RST_packet(u_char* data, tcp_info &info) {
    u_char* rst_packet = new u_char[info.length];
    std::memcpy(rst_packet, data, info.length);
    struct tcphdr* tcp_header = (struct tcphdr*)(rst_packet + (sizeof(struct ether_header) + ((struct ip*)rst_packet)->ip_hl * 4));
    tcp_header->th_flags = TH_RST;
    tcp_header->th_seq = htonl(info.seq_num);
    tcp_header->th_ack = htonl(info.server_seq_num);
    tcp_header->th_sum = 0;

    // Compute the TCP checksum
    uint16_t tcp_len = ntohs(((struct ip*)rst_packet)->ip_len) - ((struct ip*)rst_packet)->ip_hl * 4;
    tcp_header->th_sum = compute_tcp_checksum((struct ip*)rst_packet, tcp_header, tcp_len);

    return rst_packet;
}

u_char* make_FIN_packet(u_char* data, tcp_info &info) {
    u_char* fin_packet = new u_char[info.length];
    std::memcpy(fin_packet, data, info.length);
    struct tcphdr* tcp_header = (struct tcphdr*)(fin_packet + (sizeof(struct ether_header) + ((struct ip*)fin_packet)->ip_hl * 4));
    tcp_header->th_flags = TH_FIN;
    tcp_header->th_seq = htonl(info.seq_num);
    tcp_header->th_ack = htonl(info.server_seq_num);
    tcp_header->th_sum = 0;

    // Compute the TCP checksum
    uint16_t tcp_len = ntohs(((struct ip*)fin_packet)->ip_len) - ((struct ip*)fin_packet)->ip_hl * 4;
    tcp_header->th_sum = compute_tcp_checksum((struct ip*)fin_packet, tcp_header, tcp_len);

    return fin_packet;
}

void swap_src_dst(u_char* data) {
    struct ether_header* eth_header = (struct ether_header*)data;
    struct ip* ip_header = (struct ip*)(data + sizeof(struct ether_header));

    // Swap MAC addresses
    uint8_t mac_tmp[ETHER_ADDR_LEN];
    std::memcpy(mac_tmp, eth_header->ether_shost, ETHER_ADDR_LEN);
    std::memcpy(eth_header->ether_shost, eth_header->ether_dhost, ETHER_ADDR_LEN);
    std::memcpy(eth_header->ether_dhost, mac_tmp, ETHER_ADDR_LEN);

    // Swap IP addresses
    uint32_t ip_tmp = ip_header->ip_src.s_addr;
    ip_header->ip_src.s_addr = ip_header->ip_dst.s_addr;
    ip_header->ip_dst.s_addr = ip_tmp;
}

uint16_t compute_tcp_checksum(struct ip* ip_header, struct tcphdr* tcp_header, uint16_t tcp_len) {
    uint32_t sum = 0;
    uint16_t* buffer = (uint16_t*)tcp_header;

    // Calculate the sum of the TCP header and payload
    for (int i = 0; i < tcp_len / 2; ++i) {
        sum += buffer[i];
    }

    // Add the carry
    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    // Add the pseudo header
    sum += (ip_header->ip_src.s_addr >> 16) + (ip_header->ip_src.s_addr & 0xffff);
    sum += (ip_header->ip_dst.s_addr >> 16) + (ip_header->ip_dst.s_addr & 0xffff);
    sum += htons(ip_header->ip_p);
    sum += htons(tcp_len);

    // Add the carry again
    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return ~sum;
}

