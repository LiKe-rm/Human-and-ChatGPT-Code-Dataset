#include <iostream>
#include <vector>

class MersenneTwister {
public:
    MersenneTwister() : index(624) {
        // 初始化种子
        std::vector<unsigned int> defaultSeed = { 5489, 40692, 636413, 39847, 25674, 965 };
        seed(defaultSeed);
    }

    // 用指定的种子初始化
    void seed(std::vector<unsigned int> seed) {
        index = 624;
        state[0] = seed[0];
        for (int i = 1; i < 624; ++i) {
            state[i] = (1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i);
        }
    }

    // 生成下一个32位的伪随机数
    unsigned int generate() {
        if (index >= 624) {
            twist();
        }
        unsigned int y = state[index];
        y ^= (y >> 11);
        y ^= ((y << 7) & 0x9d2c5680);
        y ^= ((y << 15) & 0xefc60000);
        y ^= (y >> 18);

        ++index;
        return y;
    }

private:
    void twist() {
        for (int i = 0; i < 624; ++i) {
            unsigned int x = (state[i] & 0x80000000UL) + (state[(i + 1) % 624] & 0x7fffffffUL);
            unsigned int xA = x >> 1;
            if (x % 2 != 0) {
                xA ^= 0x9908b0dfUL;
            }
            state[i] = state[(i + 397) % 624] ^ xA;
        }
        index = 0;
    }

    unsigned int state[624];
    int index;
};

int main() {
    MersenneTwister mt;
    std::vector<unsigned int> seed = { 123, 456, 789 };
    mt.seed(seed);

    for (int i = 0; i < 10; ++i) {
        std::cout << mt.generate() << std::endl;
    }

    return 0;
}
