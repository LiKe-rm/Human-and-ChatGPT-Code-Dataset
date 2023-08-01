#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>

const uint64_t RC[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

inline uint64_t rotl64(uint64_t x, unsigned int y)
{
    return (x << y) | (x >> (64 - y));
}

void keccak_f1600(uint64_t A[5][5])
{
    for (int round = 0; round < 24; ++round) {
        uint64_t C[5], D[5];

        for (int x = 0; x < 5; ++x)
            C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];

        for (int x = 0; x < 5; ++x)
            D[x] = C[(x + 4) % 5] ^ rotl64(C[(x + 1) % 5], 1);

        for (int x = 0; x < 5; ++x)
            for (int y = 0; y < 5; ++y)
                A[x][y] ^= D[x];

        uint64_t B[5][5];

        for (int x = 0; x < 5; ++x)
            for (int y = 0; y < 5; ++y)
                B[y][(2 * x + 3 * y) % 5] = rotl64(A[x][y], (x + 3 * y) % 64);

        for (int x = 0; x < 5; ++x)
            for (int y = 0; y < 5; ++y)
                A[x][y] = B[x][y] ^ ((~B[(x + 1) % 5][y]) & B[(x + 2) % 5][y]);

        A[0][0] ^= RC[round];
    }
}

std::vector<uint8_t> keccak(const std::vector<uint8_t>& message, int output_bits)
{
    size_t rate = 1600 - 2 * output_bits;
    size_t block_size = rate / 8;
    uint64_t A[5][5] = {0};
    size_t message_offset = 0;

    while (message_offset < message.size()) {
        size_t block_len = std::min(message.size() - message_offset, block_size);

        for (size_t i = 0; i < block_len; ++i) {
            size_t x = i % 5;
            size_t y = i / 5;
            A[x][y] ^= static_cast<uint64_t>(message[message_offset + i]) << (8 * (i % 8));
        }

        message_offset += block_len;

        if (block_len == block_size)
            keccak_f1600(A);
    }

    A[0][0] ^= 0x01;
    A[block_size % 5][block_size / 5] ^= 0x8000000000000000;

    keccak_f1600(A);

    std::vector<uint8_t> hash(output_bits / 8);
    for (size_t i = 0; i < hash.size(); ++i) {
        size_t x = i % 5;
        size_t y = i / 5;
        hash[i] = static_cast<uint8_t>(A[x][y] >> (8 * (i % 8)));
    }

    return hash;
}

std::vector<uint8_t> keccak1600(const std::vector<uint8_t>& message)
{
    return keccak(message, 1600);
}
