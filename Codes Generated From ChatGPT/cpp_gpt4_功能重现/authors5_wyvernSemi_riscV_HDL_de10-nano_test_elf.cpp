#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <elf.h>

constexpr int USER_ERROR = -1;

bool is_elf_file(const Elf64_Ehdr& elf_header) {
    return elf_header.e_ident[EI_MAG0] == ELFMAG0 &&
           elf_header.e_ident[EI_MAG1] == ELFMAG1 &&
           elf_header.e_ident[EI_MAG2] == ELFMAG2 &&
           elf_header.e_ident[EI_MAG3] == ELFMAG3;
}

int load_elf_to_memory(const std::string& elf_filename) {
    std::ifstream elf_file(elf_filename, std::ios::in | std::ios::binary);
    if (!elf_file) {
        std::cerr << "Error: Unable to open the ELF file." << std::endl;
        return USER_ERROR;
    }

    Elf64_Ehdr elf_header;
    elf_file.read(reinterpret_cast<char*>(&elf_header), sizeof(elf_header));

    if (!is_elf_file(elf_header)) {
        std::cerr << "Error: The file is not a valid ELF file." << std::endl;
        return USER_ERROR;
    }

    std::vector<Elf64_Phdr> program_headers(elf_header.e_phnum);
    elf_file.seekg(elf_header.e_phoff, std::ios::beg);
    elf_file.read(reinterpret_cast<char*>(program_headers.data()), sizeof(Elf64_Phdr) * elf_header.e_phnum);

    for (const auto& program_header : program_headers) {
        if (program_header.p_type == PT_LOAD) {
            std::vector<char> segment_data(program_header.p_filesz);
            elf_file.seekg(program_header.p_offset, std::ios::beg);
            elf_file.read(segment_data.data(), program_header.p_filesz);

            void* memory_address = reinterpret_cast<void*>(program_header.p_vaddr);
            std::memcpy(memory_address, segment_data.data(), program_header.p_filesz);

            std::memset(reinterpret_cast<void*>(program_header.p_vaddr + program_header.p_filesz), 0, program_header.p_memsz - program_header.p_filesz);
        }
    }

    elf_file.close();
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <ELF_FILE>" << std::endl;
        return USER_ERROR;
    }

    int result = load_elf_to_memory(argv[1]);
    if (result == USER_ERROR) {
        std::cerr << "Error: Unable to load the ELF file to memory." << std::endl;
    } else {
        std::cout << "ELF file has been successfully loaded into memory." << std::endl;
    }

    return result;
}
