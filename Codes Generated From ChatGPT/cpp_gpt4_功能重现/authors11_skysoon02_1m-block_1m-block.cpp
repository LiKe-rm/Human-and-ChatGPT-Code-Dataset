#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

using namespace std;

vector<string> blacklist;

int load_blacklist(const char *filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening blacklist file: " << filename << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        blacklist.push_back(line);
    }

    sort(blacklist.begin(), blacklist.end());
    file.close();
    return 0;
}

bool is_blacklisted(const string &host) {
    return binary_search(blacklist.begin(), blacklist.end(), host);
}

static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
              struct nfq_data *nfa, void *data) {
    u_int32_t id = 0;
    struct nfqnl_msg_packet_hdr *ph;
    ph = nfq_get_msg_packet_hdr(nfa);
    if (ph) {
        id = ntohl(ph->packet_id);
    }

    unsigned char *packet_data;
    int len = nfq_get_payload(nfa, &packet_data);

    if (len > 0) {
        struct iphdr *iph = (struct iphdr *)packet_data;
        if (iph->protocol == IPPROTO_TCP) {
            struct tcphdr *tcph = (struct tcphdr *)(packet_data + iph->ihl * 4);
            unsigned char *http_data = packet_data + iph->ihl * 4 + tcph->doff * 4;
            string http_payload(reinterpret_cast<char *>(http_data));

            size_t host_pos = http_payload.find("Host:");
            if (host_pos != string::npos) {
                size_t host_end = http_payload.find("\r\n", host_pos);
                string host = http_payload.substr(host_pos + 6, host_end - (host_pos + 6));

                if (is_blacklisted(host)) {
                    return nfq_set_verdict(qh, id, NF_DROP, 0, nullptr);
                }
            }
        }
    }

    return nfq_set_verdict(qh, id, NF_ACCEPT, 0, nullptr);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <blacklist_file>" << endl;
        return -1;
    }

    if (load_blacklist(argv[1]) < 0) {
        return -1;
    }

    struct nfq_handle *h;
    struct nfq_q_handle *qh;
    int fd;
    int rv;
    char buf[4096] __attribute__((aligned));

    h = nfq_open();
    if (!h) {
        cerr << "Error during nfq_open()" << endl;
        return -1;
    }

    if (nfq_unbind_pf(h, AF_INET) < 0) {
        cerr << "Error during nfq_unbind_pf()" << endl;
        return -1;
    }

    if (nfq_bind_pf(h, AF_INET) < 0) {
        cerr << "Error during nfq_bind_pf()" << endl;
        return -1;
    }

    qh = nfq_create_queue(h, 0, &cb, nullptr);
    if (!qh) {
        cerr << "Error during nfq_create_queue()" << endl;
        return -1;
    }

    if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
        cerr << "Error during nfq_set_mode()" << endl;
        return -1;
    }

    fd = nfq_fd(h);
    while ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
        nfq_handle_packet(h, buf, rv);
    }

    nfq_destroy_queue(qh);
    nfq_close(h);

    return 0;
}
