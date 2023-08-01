#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <cstring>

// 假设VPROC API为虚拟处理器API
#include "VPROC_API.h"

// 定义HALT_ADDR停机地址
const uint32_t HALT_ADDR = 0xFFFF;

class VirtualProcessor {
public:
    VirtualProcessor(size_t memorySize) : memory(memorySize, 0) {}

    void writeMemory(uint32_t addr, uint8_t value) {
        if (addr < memory.size()) {
            memory[addr] = value;
        } else {
            throw std::out_of_range("Memory address out of range.");
        }
    }

    uint8_t readMemory(uint32_t addr) {
        if (addr < memory.size()) {
            return memory[addr];
        } else {
            throw std::out_of_range("Memory address out of range.");
        }
    }

    bool validateData(uint32_t addr, uint8_t expectedValue) {
        uint8_t value = readMemory(addr);
        return value == expectedValue;
    }

    bool validateHalfWord(uint32_t addr, uint16_t expectedValue) {
        uint16_t value = readMemory(addr) | (readMemory(addr + 1) << 8);
        return value == expectedValue;
    }

    bool validateWord(uint32_t addr, uint32_t expectedValue) {
        uint32_t value = readMemory(addr) | (readMemory(addr + 1) << 8) |
                         (readMemory(addr + 2) << 16) | (readMemory(addr + 3) << 24);
        return value == expectedValue;
    }

    void runTest() {
        if (validateData(0x00, 0x12) &&
            validateHalfWord(0x02, 0x3456) &&
            validateWord(0x04, 0x789ABCDE)) {
            std::cout << "Test passed!" << std::endl;
            exit(EXIT_SUCCESS);
        } else {
            std::cout << "Test failed!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

private:
    std::vector<uint8_t> memory;
};

int main() {
    VirtualProcessor vp(256);

    // 填充内存
    vp.writeMemory(0x00, 0x12);
    vp.writeMemory(0x01, 0xFF);
    vp.writeMemory(0x02, 0x34);
    vp.writeMemory(0x03, 0x56);
    vp.writeMemory(0x04, 0x78);
    vp.writeMemory(0x05, 0x9A);
    vp.writeMemory(0x06, 0xBC);
    vp.writeMemory(0x07, 0xDE);

    vp.runTest();

    return 0;
}
