#include <iostream>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

const char *dev;
const char *target_url = "http://example.com";

struct pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};

unsigned short csum(unsigned short *ptr, int nbytes) {
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char *)&oddbyte) = *(u_char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (short)~sum;

    return (answer);
}

void send_RST(u_int32_t src_ip, u_int32_t dst_ip, u_int16_t src_port, u_int16_t dst_port, u_int32_t seq_num, u_int32_t ack_num) {
    int sd;
    char buffer[4096];
    struct iphdr *iph = (struct iphdr *)buffer;
    struct tcphdr *tcph = (struct tcphdr *)(buffer + sizeof(struct ip));
    struct sockaddr_in sin;
    struct pseudo_header psh;

    memset(buffer, 0, sizeof(buffer));

    sd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sd == -1) {
        perror("socket");
        exit(-1);
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(dst_port);
    sin.sin_addr.s_addr = dst_ip;

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct ip) + sizeof(struct tcphdr);
    iph->id = htonl(12345);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0;
    iph->saddr = src_ip;
    iph->daddr = dst_ip;

    tcph->source = htons(src_port);
    tcph->dest = htons(dst_port);
    tcph->seq = seq_num;
    tcph->ack_seq = ack_num;
    tcph->doff = 5;
    tcph->rst = 1;
    tcph->window = htons(8192);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    psh.source_address = src_ip;
    psh.dest_address = dst_ip;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcphdr));

    char *pseudogram = new char[sizeof(struct pseudo_header) + sizeof(struct tcphdr)];
    memcpy(pseudogram, (char *)&psh, sizeof(struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header), tcph, sizeof(struct tcphdr));

    tcph->check = csum((unsigned short *)pseudogram, sizeof(struct pseudo_header) + sizeof(struct tcphdr));

    if (sendto(sd, buffer, iph->tot_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("sendto");
    } else {
        std::cout << "RST packet sent" << std::endl;
    }

    delete[] pseudogram;
    close(sd);
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct iphdr *iph = (struct iphdr *)(packet + 14);
    struct tcphdr *tcph = (struct tcphdr *)(packet + 14 + iph->ihl * 4);
    u_int32_t src_ip = iph->saddr;
    u_int32_t dst_ip = iph->daddr;
    u_int16_t src_port = ntohs(tcph->source);
    u_int16_t dst_port = ntohs(tcph->dest);
    u_int32_t seq_num = tcph->seq;
    u_int32_t ack_num = tcph->ack_seq;

    if (iph->protocol == IPPROTO_TCP && strstr((char *)packet, target_url)) {
        send_RST(src_ip, dst_ip, src_port, dst_port, seq_num, ack_num);
    }
}
