#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <elf.h>
#include <unistd.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class RV32 {
public:
    uint32_t reg[32] = {0};
    uint32_t pc = 0;
    std::vector<uint8_t> memory;

    RV32(size_t mem_size) : memory(mem_size) {}

    uint32_t read_mem32(uint32_t addr) {
        uint32_t data;
        memcpy(&data, &memory[addr], sizeof(data));
        return data;
    }

    void write_mem32(uint32_t addr, uint32_t data) {
        memcpy(&memory[addr], &data, sizeof(data));
    }

    void execute(uint32_t instruction) {
        // 在此处实现RV32指令集的解码和执行
    }

    void run() {
        while (true) {
            uint32_t instruction = read_mem32(pc);
            execute(instruction);
            pc += 4;
        }
    }
};

void load_elf(const char *filename, RV32 &cpu) {
    // 在此处实现ELF文件的加载
}

void start_gdb_server(int port, RV32 &cpu) {
    // 在此处实现GDB服务器的启动
}

int main(int argc, char *argv[]) {
    int opt;
    bool gdb_mode = false;
    int gdb_port = 0;
    const char *elf_file = nullptr;

    while ((opt = getopt(argc, argv, "g:e:")) != -1) {
        switch (opt) {
        case 'g':
            gdb_mode = true;
            gdb_port = atoi(optarg);
            break;
        case 'e':
            elf_file = optarg;
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " -e ELF_FILE [-g GDB_PORT]" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (!elf_file) {
        std::cerr << "Error: ELF file not specified." << std::endl;
        exit(EXIT_FAILURE);
    }

    RV32 cpu(0x10000);
    load_elf(elf_file, cpu);

    if (gdb_mode) {
        start_gdb_server(gdb_port, cpu);
    } else {
        cpu.run();
    }

    return 0;
}
