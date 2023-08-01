#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <vector>

class SHA1 {
public:
    SHA1() {
        reset();
    }

    void update(const std::string &message) {
        update(reinterpret_cast<const uint8_t *>(message.data()), message.size());
    }

    std::string digest() {
        uint64_t bit_length = message_size * 8;
        uint8_t final_block[64];
        size_t remaining_bytes = message_size % 64;
        memcpy(final_block, buffer, remaining_bytes);

        // 添加填充字节
        final_block[remaining_bytes++] = 0x80;
        while (remaining_bytes % 64 != 56) {
            final_block[remaining_bytes++] = 0;
        }

        // 添加长度信息
        for (int i = 7; i >= 0; --i) {
            final_block[remaining_bytes++] = (bit_length >> (i * 8)) & 0xff;
        }

        // 处理最后一个块
        update(final_block, remaining_bytes);

        // 生成哈希值字符串
        std::stringstream ss;
        for (uint32_t h : hash) {
            ss << std::hex << std::setw(8) << std::setfill('0') << h;
        }

        reset();

        return ss.str();
    }

private:
    void reset() {
        message_size = 0;
        std::memset(buffer, 0, sizeof(buffer));
        hash = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    }

    void update(const uint8_t *data, size_t size) {
        while (size--) {
            buffer[message_size++ % 64] = *data++;

            if (message_size % 64 == 0) {
                process_block(buffer);
            }
        }
    }

    void process_block(const uint8_t *block) {
        uint32_t w[80];
        for (size_t i = 0; i < 16; ++i) {
            w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
        }

        for (size_t i = 16; i < 80; ++i) {
            w[i] = left_rotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        uint32_t a = hash[0], b = hash[1], c = hash[2], d = hash[3], e = hash[4];

        for (size_t i = 0; i < 80; ++i) {
            uint32_t f, k;

            if (i < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = left_rotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = left_rotate(b, 30);
            b = a;
            a = temp;
        }

        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
    }

    uint32_t left_rotate(uint32_t value, uint32_t count) {
        return (value << count) | (value >> (32 - count));
    }

    size_t message_size;
    uint8_t buffer[64];
    std::vector<uint32_t> hash;
};

int main() {
    std::string input;
    std::cout << "请输入需要计算SHA-1哈希值的字符串: ";
    std::getline(std::cin, input);

    SHA1 sha1;
    sha1.update(input);
    std::string output = sha1.digest();

    std::cout << "SHA-1哈希值: " << output << std::endl;

    return 0;
}

