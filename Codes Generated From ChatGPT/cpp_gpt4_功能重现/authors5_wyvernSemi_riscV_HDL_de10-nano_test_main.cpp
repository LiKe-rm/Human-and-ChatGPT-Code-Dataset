#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <thread>

// Constants and static variables
constexpr uint32_t CSR_CORE_IMEM = 0x1000;
constexpr uint32_t TIMEOUT_MS = 1000;

// Simulated memory space
uint8_t memory[0x10000];

// Function to write external memory, used for loading test.exe
void write_external_memory(uint32_t addr, const uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        memory[addr + i] = data[i];
    }
}

class CCoreAuto {
public:
    // Connect to CPU Core and set some test parameters
    CCoreAuto() {
        // Simulate connection to CPU Core
        std::cout << "Connected to CPU Core." << std::endl;
        reset_core();
    }

    // Get IMEM base address
    uint32_t get_imem_base() const {
        return coreBaseAddr + CSR_CORE_IMEM;
    }

    // Load test.exe to the specified address
    void load_test_exe(const std::string &filename, uint32_t addr) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Unable to open test.exe" << std::endl;
            std::exit(1);
        }

        file.seekg(0, std::ios::end);
        size_t size = static_cast<size_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(size);
        file.read(reinterpret_cast<char *>(buffer.data()), size);
        write_external_memory(addr, buffer.data(), size);
    }

    // Run test.exe
    bool run_test_exe() {
        release_from_reset();

        auto start_time = std::chrono::steady_clock::now();
        while (!is_halted()) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
            if (elapsed.count() > TIMEOUT_MS) {
                std::cerr << "Error: Test execution timed out." << std::endl;
                output_gp_registers();
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return true;
    }

    // Check and print test result
    int check_test_result() const {
        int result = gp_registers[3]; // Assuming the return value is in register x3 (a0)
        if (result == 1) {
            std::cout << "Test succeeded." << std::endl;
        } else {
            std::cout << "Test failed." << std::endl;
        }
        return result;
    }

private:
    uint32_t coreBaseAddr = 0x2000;
    uint32_t gp_registers[32] = {0};
    bool halted = true;

    void reset_core() {
        halted = true;
    }

    void release_from_reset() {
        halted = false;
    }

    bool is_halted() const {
        return halted;
    }

    void output_gp_registers() const {
        std::cout << "GP Registers:" << std::endl;
        for (int i = 0; i < 32; ++i) {
            std::cout << "x" << i << ": " << gp_registers[i] << std::endl;
        }
    }
};

int main() {
    CCoreAuto core;
    uint32_t imem_base = core.get_imem_base();
    core.load_test_exe("test.exe", imem_base);
    if (core.run_test_exe()) {
        int result = core.check_test_result();
        std::cout << "Exit status: " << result << std::endl;
    } else {
        std::cerr << "Error: Unable to complete test execution." << std::endl;
    }

    return 0;
}
