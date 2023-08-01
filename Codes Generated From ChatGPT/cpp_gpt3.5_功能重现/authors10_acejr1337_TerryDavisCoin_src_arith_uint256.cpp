#include <cstring>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstdint>
#include <sstream>

template <size_t BITS>
class base_uint {
public:
    static constexpr size_t WIDTH = BITS / 8;
    uint8_t data[WIDTH];

    base_uint() {
        std::memset(data, 0, WIDTH);
    }

    template <typename T>
    base_uint(T v) {
        std::memset(data, 0, WIDTH);
        *this = v;
    }

    template <typename T>
    base_uint& operator=(T v) {
        std::memset(data, 0, WIDTH);
        std::stringstream ss;
        ss << std::hex << v;
        std::string hexStr = ss.str();
        int len = hexStr.length();
        int k = 0;
        for (int i = len - 1; i >= 0 && k < WIDTH; i -= 2) {
            uint8_t b;
            std::stringstream h;
            h << hexStr[i-1] << hexStr[i];
            h >> std::hex >> b;
            data[k++] = b;
        }
        return *this;
    }

    bool operator==(const base_uint& other) const {
        return std::memcmp(data, other.data, WIDTH) == 0;
    }

    bool operator!=(const base_uint& other) const {
        return !(*this == other);
    }

    bool operator<(const base_uint& other) const {
        for (int i = WIDTH - 1; i >= 0; i--) {
            if (data[i] < other.data[i]) {
                return true;
            }
            else if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator<=(const base_uint& other) const {
        return (*this == other) || (*this < other);
    }

    bool operator>(const base_uint& other) const {
        return !(*this <= other);
    }

    bool operator>=(const base_uint& other) const {
        return (*this == other) || (*this > other);
    }

    base_uint operator<<(int shift) const {
        base_uint ret;
        int k = shift / 8;
        int rem = shift % 8;
        for (int i = 0; i < WIDTH - k; i++) {
            ret.data[i+k] |= data[i] << rem;
            if (rem > 0 && i + k + 1 < WIDTH) {
                ret.data[i+k+1] |= data[i] >> (8 - rem);
            }
        }
        return ret;
    }

    base_uint operator>>(int shift) const {
        base_uint ret;
        int k = shift / 8;
        int rem = shift % 8;
        for (int i = k; i < WIDTH; i++) {
            ret.data[i-k] |= data[i] >> rem;
            if (rem > 0 && i > k) {
                ret.data[i-k-1] |= data[i] << (8 - rem);
            }
        }
        return ret;
    }

    base_uint operator*(const base_uint& other) const {
        base_uint ret;
        for (int i = 0; i < WIDTH; i++) {
            uint16_t carry = 0;
            for (int j = 0; j < WIDTH - i; j++) {
                uint32_t res = (uint32_t)data[j] * (uint32_t)other.data[i] + (uint32_t)ret.data[i+j] + carry;
            carry = res >> 8;
            ret.data[i+j] = res & 0xff;
        }
    }
    return ret;
}

base_uint operator/(const base_uint& other) const {
    base_uint ret;
    base_uint dividend = *this;
    for (int i = WIDTH * 8 - 1; i >= 0; i--) {
        if (dividend >= other << i) {
            dividend = dividend - (other << i);
            ret |= base_uint<WIDTH>(1) << i;
        }
    }
    return ret;
}

base_uint operator%(const base_uint& other) const {
    base_uint dividend = *this;
    for (int i = WIDTH * 8 - 1; i >= 0; i--) {
        if (dividend >= other << i) {
            dividend = dividend - (other << i);
        }
    }
    return dividend;
}

uint64_t Get64(int n = 0) const {
    uint64_t ret = 0;
    for (int i = 0; i < 8 && n * 8 + i < WIDTH; i++) {
        ret |= (uint64_t)data[n * 8 + i] << (i * 8);
    }
    return ret;
}

uint32_t Get32(int n = 0) const {
    uint32_t ret = 0;
    for (int i = 0; i < 4 && n * 4 + i < WIDTH; i++) {
        ret |= (uint32_t)data[n * 4 + i] << (i * 8);
    }
    return ret;
}

uint8_t GetCompact() const {
    int nSize = (BITS + 7) / 8;
    if (nSize <= 3) {
        uint32_t nCompact = Get32(0);
        nCompact |= (nSize << 24);
        return nCompact;
    }
    else {
        uint32_t nCompact = Get32(nSize - 3);
        nCompact = nCompact / 0x1000000;
        nCompact |= ((nSize & 0xff) << 24);
        return nCompact;
    }
}

void SetCompact(uint32_t nCompact) {
    int nSize = nCompact >> 24;
    uint32_t nWord = nCompact & 0x007fffff;
    if (nSize > 3) {
        data[0] = (uint8_t)(nWord);
        data[1] = (uint8_t)(nWord >> 8);
        data[2] = (uint8_t)(nWord >> 16);
        data[3] = (uint8_t)(nWord >> 24);
        std::memset(data + 4, 0, nSize - 3);
    }
    else {
        nWord >>= 8 * (3 - nSize);
        std::memset(data, 0, 4);
        data[0] = (uint8_t)(nWord);
        data[1] = (uint8_t)(nWord >> 8);
        data[2] = (uint8_t)(nWord >> 16);
        data[3] = (uint8_t)(nWord >> 24);
    }
}

std::string ToString() const {
    std::stringstream ss;
    ss << std::hex;
    for (int i = WIDTH - 1; i >= 0; i--) {
        ss << static_cast<int (data[i]);
}
return ss.str();
}
};

// 辅助函数，将uint256转换为arith_uint256
inline arith_uint256 ArithToUint256(const uint256& u) {
arith_uint256 ret;
std::memcpy(&ret, &u, sizeof(u));
return ret;
}

// 辅助函数，将arith_uint256转换为uint256
inline uint256 UintToArith256(const arith_uint256& a) {
uint256 ret;
std::memcpy(&ret, &a, sizeof(ret));
return ret;
}

int main() {
base_uint<256> a("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
base_uint<256> b(1234567890);
base_uint<256> c = a * b;
std::cout << c.ToString() << std::endl;
uint256 u("0x123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
arith_uint256 arith = ArithToUint256(u);
uint256 u2 = UintToArith256(arith);
std::cout << u.ToString() << std::endl;
std::cout << u2.ToString() << std::endl;
return 0;
}
