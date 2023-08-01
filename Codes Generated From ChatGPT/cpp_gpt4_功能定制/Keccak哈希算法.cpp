#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>

constexpr size_t KeccakRounds = 24;
constexpr uint64_t XorMasks[KeccakRounds] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 0x8000000080008000ULL,
    0x000000000000808bULL, 0x0000000080000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL,
    0x000000000000008aULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
    0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL,
    0x8000000000008002ULL, 0x8000000000000080ULL, 0x000000000000800aULL, 0x800000008000000aULL,
    0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

class Keccak {
public:
    explicit Keccak(unsigned int bits);
    void update(const uint8_t* data, size_t size);
    void finalize(uint8_t* hash);

private:
    void processBlock();
    void theta();
    void rho();
    void pi();
    void chi();
    void iota(unsigned int round);

    uint64_t state[25];
    unsigned int block_size;
    unsigned int rate;
    std::vector<uint8_t> buffer;
};

Keccak::Keccak(unsigned int bits) : block_size(200 - 2 * (bits / 8)), rate(bits) {
    std::memset(state, 0, sizeof(state));
}

void Keccak::update(const uint8_t* data, size_t size) {
    while (size > 0) {
        size_t amount = std::min(size, block_size - buffer.size());
        buffer.insert(buffer.end(), data, data + amount);
        data += amount;
        size -= amount;

        if (buffer.size() == block_size) {
            processBlock();
            buffer.clear();
        }
    }
}

void Keccak::finalize(uint8_t* hash) {
    buffer.push_back(1);
    buffer.resize(block_size, 0);
    buffer[block_size - 1] |= 0x80;
    processBlock();

    for (size_t i = 0; i < rate / 8; ++i) {
        hash[i] = state[i / 8] >> (8 * (i % 8));
    }
}

void Keccak::processBlock() {
    for (size_t i = 0; i < buffer.size() / 8; ++i) {
        state[i] ^= ((uint64_t*)buffer.data())[i];
    }

    for (unsigned int round = 0; round < KeccakRounds; ++round) {
        theta();
        rho();
        pi();
        chi();
        iota(round);
    }
}

void Keccak::theta() {
    uint64_t c[5], d[5];

    for (size_t i = 0; i < 5; ++i) {
        c[i] = state[i] ^ state[i + 5] ^ state[i + 10] ^ state[i + 15] ^ state[i + 20];
    }
    for (size_t i = 0; i < 5; ++i) {
        d[i] = c[(i + 4) % 5] ^ ((c[(i + 1) % 5] << 1) | (c[(i + 1) % 5] >> 63));
        for (size_t j = 0; j < 25; j += 5) {
            state[i + j] ^= d[i];
        }
    }
}

void Keccak::rho() {
    static const unsigned int offsets[25] = {
    0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43, 25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14
    };

    for (size_t i = 0; i < 25; ++i) {
        state[i] = (state[i] << offsets[i]) | (state[i] >> (64 - offsets[i]));
    }
}

void Keccak::pi() {
    uint64_t temp[25];
    std::memcpy(temp, state, sizeof(temp));
    for (size_t i = 0; i < 25; ++i) {
        state[(i * 7) % 25] = temp[i];
    }
}

void Keccak::chi() {
    uint64_t temp[25];
    std::memcpy(temp, state, sizeof(temp));
    for (size_t i = 0; i < 25; i += 5) {
        for (size_t j = 0; j < 5; ++j) {
            state[i + j] = temp[i + j] ^ (~temp[i + (j + 1) % 5] & temp[i + (j + 2) % 5]);
        }
    }
}

void Keccak::iota(unsigned int round) {
    state[0] ^= XorMasks[round];
}

int main() {
    const std::string input = "hello world";
    const unsigned int hash_size = 256;
    Keccak keccak(hash_size);
    keccak.update(reinterpret_cast<const uint8_t*>(input.data()), input.size());

    std::vector<uint8_t> hash(hash_size / 8);
    keccak.finalize(hash.data());

    for (const auto& byte : hash) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::endl;

    return 0;
}