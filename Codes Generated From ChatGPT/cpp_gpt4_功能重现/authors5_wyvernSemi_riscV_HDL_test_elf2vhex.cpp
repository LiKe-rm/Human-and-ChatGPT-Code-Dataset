#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef int64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;

void print_usage() {
    fprintf(stderr, "Usage: elf2verilog_hex <input_elf> [output_hex]\n");
}

uint8_t* mmap_file(const char* filename, size_t* file_size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return nullptr;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return nullptr;
    }

    *file_size = sb.st_size;
    uint8_t* data = (uint8_t*)mmap(nullptr, *file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return nullptr;
    }

    close(fd);
    return data;
}

void munmap_file(uint8_t* data, size_t file_size) {
    munmap(data, file_size);
}

bool elf2verilog_hex(const char* input_file, const char* output_file) {
    size_t file_size;
    uint8_t* file_data = mmap_file(input_file, &file_size);
    if (!file_data) {
        return false;
    }

    Elf64_Ehdr* ehdr = (Elf64_Ehdr*)file_data;
    Elf64_Phdr* phdrs = (Elf64_Phdr*)(file_data + ehdr->e_phoff);

    FILE* output = stdout;
    if (output_file) {
        output = fopen(output_file, "w");
        if (!output) {
            perror("fopen");
            munmap_file(file_data, file_size);
            return false;
        }
    }

    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            uint8_t* segment_data = file_data + phdrs[i].p_offset;
            for (size_t j = 0; j < phdrs[i].p_filesz; j++) {
                fprintf(output, "%02x\n", segment_data[j]);
            }
        }
    }

    if (output_file) {
        fclose(output);
    }
    munmap_file(file_data, file_size);
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        print_usage();
        return EXIT_FAILURE;
    }

    const char* input_file = argv[1];
    const char* output_file = (argc == 3) ? argv[2] : nullptr;

    if (elf2verilog_hex(input_file, output_file)) {
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Failed to convert ELF to Verilog hex format\n");
        return EXIT_FAILURE;
    }
}
