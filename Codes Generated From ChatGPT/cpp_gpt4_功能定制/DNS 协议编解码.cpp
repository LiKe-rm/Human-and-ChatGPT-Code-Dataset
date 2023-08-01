#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>

struct DNSHeader {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

struct DNSQuestion {
    std::string qname;
    uint16_t qtype;
    uint16_t qclass;
};

struct DNSOption {
    uint16_t code;
    uint16_t length;
    std::vector<uint8_t> data;
};

void decode_hdr(const uint8_t* data, DNSHeader& hdr) {
    memcpy(&hdr, data, sizeof(DNSHeader));
    hdr.id = ntohs(hdr.id);
    hdr.flags = ntohs(hdr.flags);
    hdr.qdcount = ntohs(hdr.qdcount);
    hdr.ancount = ntohs(hdr.ancount);
    hdr.nscount = ntohs(hdr.nscount);
    hdr.arcount = ntohs(hdr.arcount);
}

const uint8_t* decode_qname(const uint8_t* data, std::string& qname) {
    qname.clear();
    const uint8_t* ptr = data;
    while (*ptr) {
        uint8_t label_len = *ptr++;
        qname.append(ptr, ptr + label_len);
        ptr += label_len;
        if (*ptr) qname.push_back('.');
    }
    return ptr + 1;
}

const uint8_t* decode_option(const uint8_t* data, DNSOption& option) {
    memcpy(&option.code, data, sizeof(uint16_t));
    memcpy(&option.length, data + sizeof(uint16_t), sizeof(uint16_t));
    option.code = ntohs(option.code);
    option.length = ntohs(option.length);
    option.data.assign(data + 4, data + 4 + option.length);
    return data + 4 + option.length;
}

const uint8_t* decode_additional(const uint8_t* data, std::vector<DNSOption>& additional) {
    const uint8_t* ptr = data;
    while (ptr < data + 2 && *ptr == 0) {
        DNSOption option;
        ptr = decode_option(ptr + 2, option);
        additional.push_back(option);
    }
    return ptr;
}

void decode(const std::vector<uint8_t>& data, DNSHeader& hdr, DNSQuestion& question, std::vector<DNSOption>& additional) {
    const uint8_t* ptr = data.data();
    decode_hdr(ptr, hdr);
    ptr += sizeof(DNSHeader);
    ptr = decode_qname(ptr, question.qname);
    memcpy(&question.qtype, ptr, sizeof(uint16_t));
    memcpy(&question.qclass, ptr + sizeof(uint16_t), sizeof(uint16_t));
    question.qtype = ntohs(question.qtype);
    question.qclass = ntohs(question.qclass);
    ptr += 4;
    decode_additional(ptr, additional);
}

std::vector<uint8_t> code_hdr(const DNSHeader& hdr) {
    std::vector<uint8_t> data(sizeof(DNSHeader));
    DNSHeader n_hdr = hdr;
    n_hdr.id = htons(n_hdr.id);
    n_hdr.flags = htons(n_hdr.flags);
    n_hdr.qdcount = htons(n_hdr.qdcount);
    n_hdr.ancount = htons(n_hdr.ancount);
    n_hdr.nscount = htons(n_hdr.nscount);
    n_hdr.arcount = htons(n_hdr.arcount);
    memcpy(data.data(), &n_hdr, sizeof(DNSHeader));
    return data;
}

std::vector<uint8_t> code_domain(const std::string(const std::string& domain) {
    std::vector<uint8_t> data;
    std::istringstream iss(domain);
    std::string label;
    while (std::getline(iss, label, '.')) {
        data.push_back(static_cast<uint8_t>(label.size()));
        for (char ch : label) {
            data.push_back(ch);
        }
    }
    data.push_back(0);
    return data;
}

std::vector<uint8_t> code_option(const DNSOption& option) {
    std::vector<uint8_t> data(4 + option.length);
    uint16_t code = htons(option.code);
    uint16_t length = htons(option.length);
    memcpy(data.data(), &code, sizeof(uint16_t));
    memcpy(data.data() + sizeof(uint16_t), &length, sizeof(uint16_t));
    memcpy(data.data() + 4, option.data.data(), option.length);
    return data;
}

std::vector<uint8_t> code_additional(const std::vector<DNSOption>& additional) {
    std::vector<uint8_t> data;
    for (const auto& option : additional) {
        data.push_back(0);
        data.push_back(0);
        auto option_data = code_option(option);
        data.insert(data.end(), option_data.begin(), option_data.end());
    }
    return data;
}

std::vector<uint8_t> code(const DNSHeader& hdr, const DNSQuestion& question, const std::vector<DNSOption>& additional) {
    std::vector<uint8_t> data = code_hdr(hdr);
    auto qname_data = code_domain(question.qname);
    data.insert(data.end(), qname_data.begin(), qname_data.end());
    uint16_t qtype = htons(question.qtype);
    uint16_t qclass = htons(question.qclass);
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&qtype), reinterpret_cast<uint8_t*>(&qtype) + sizeof(uint16_t));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&qclass), reinterpret_cast<uint8_t*>(&qclass) + sizeof(uint16_t));
    auto additional_data = code_additional(additional);
    data.insert(data.end(), additional_data.begin(), additional_data.end());
    return data;
}

int main() {
    std::vector<uint8_t> raw_data = { /* raw DNS data */};
    DNSHeader hdr;
    DNSQuestion question;
    std::vector<DNSOption> additional;
    decode(raw_data, hdr, question, additional);
    std::vector<uint8_t> encoded_data = code(hdr, question, additional);

    return 0;
}
