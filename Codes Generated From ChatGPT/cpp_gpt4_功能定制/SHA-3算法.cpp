#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdint>

class SHA3 {
public:
    SHA3(int bitLength);
    void reset();
    std::string operator()(const std::string &input);

private:
    void processBlock(const uint8_t *block);
    void padAndProcess();
    std::string digestToHex();

    static constexpr size_t stateSize = 25;
    static constexpr size_t blockSize = 200;
    std::array<uint64_t, stateSize> m_hash;
    std::vector<uint8_t> m_block;
    size_t m_blockPos;
    size_t m_bitsInGroup;
    uint64_t m_bitLength;
};

const uint64_t roundConstants[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
    0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

inline uint64_t rot(uint64_t x, uint8_t y) {
    return (x << y) | (x >> (64 - y));
}

inline void theta(std::array<uint64_t, 25> &state) {
    std::array<uint64_t, 5> columnParity;
    for (size_t i = 0; i < 5; ++i) {
        columnParity[i] = state[i] ^ state[i + 5] ^ state[i + 10] ^ state[i + 15] ^ state[i + 20];
    }
    for (size_t i = 0; i < 5; ++i) {
        uint64_t t = columnParity[(i + 4) % 5] ^ rot(columnParity[(i + 1) % 5], 1);
        for (size_t j = 0; j < 25; j += 5) {
            state[i + j] ^= t;
        }
    }
}

inline void rho(std::array<uint64_t, 25> &state) {
    static const uint8_t rotations[25] = {
        0,  1, 62, 28, 27,
        36, 44,  6, 55, 20,
        3, 10, 43, 25, 39,
        41, 45, 15, 21,  8,
        18,  2, 61, 56, 14
    };
    for (size_t i = 0; i < 25; ++i) {
        state[i] = rot(state[i], rotations[i]);
    }
}

inline void pi(std::array<uint64_t, 25> &state) {
    std::array<uint64_t, 25> temp = state;
    for (size_t i = 0; i < 25; ++i) {
        state[i] = temp[((i % 5) * 5) + (i / 5)];
    }
}

inline void chi(std::array<uint64_t, 25> &state) {
    for (size_t i = 0; i < 25; i += 5) {
        for (size_t j = 0; j < 5; ++j) {
            state[i + j] ^= (~state[i + (j + 1) % 5]) & state[i + (j + 2) % 5];
        }
    }
}

inline void iota(std::array<uint64_t, 25> &state, size_t round) {
    state[0] ^= roundConstants[round];
}

void keccakf(std::array<uint64_t, 25> &state) {
    for (size_t round = 0; round < 24; ++round) {
        theta(state);
        rho(state);
        pi(state);
        chi(state);
        iota(state, round);
    }
}

SHA3::SHA3(int bitLength) : m_bitsInGroup(1600 - 2 * bitLength), m_bitLength(bitLength) {
    reset();
}

void SHA3::reset() {
    std::fill(m_hash.begin(), m_hash.end(), 0);
    m_block.resize(blockSize);
    m_blockPos = 0;
}

void SHA3::processBlock(const uint8_t *block) {
    for (size_t i = 0; i < blockSize; i += 8) {
        m_hash[i / 8] ^= *reinterpret_cast<const uint64_t *>(block + i);
    }
    keccakf(m_hash);
}

void SHA3::padAndProcess() {
    m_block[m_blockPos] = 1;
    std::fill(m_block.begin() + m_blockPos + 1, m_block.end(), 0);
    m_block[blockSize - 1] |= 0x80;
    processBlock(m_block.data());
}

std::string SHA3::operator()(const std::string &input) {
    const uint8_t *data = reinterpret_cast<const uint8_t *>(input.data());
    size_t dataSize = input.size();
    while (dataSize > 0) {
        size_t bytesToCopy = std::min(dataSize, blockSize - m_blockPos);
        std::memcpy(m_block.data() + m_blockPos, data, bytesToCopy);
        m_blockPos += bytesToCopy;
        dataSize -= bytesToCopy;
        data += bytesToCopy;

        if (m_blockPos == blockSize) {
            processBlock(m_block.data());
            m_blockPos = 0;
        }
    }

    padAndProcess();
    return digestToHex();
}

std::string SHA3::digestToHex() {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    size_t digestLength = m_bitLength / 8;

    for (size_t i = 0; i < digestLength; ++i) {
        ss << std::setw(2) << static_cast<unsigned>(reinterpret_cast<uint8_t *>(m_hash.data())[i]);
    }

    reset();
    return ss.str();
}