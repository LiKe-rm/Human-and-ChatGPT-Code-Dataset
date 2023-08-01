#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <keystone/keystone.h>
#include <pe_bliss.h>

std::string read_asm_code(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    return content;
}

std::vector<uint8_t> compile_asm_code(const std::string& asm_code) {
    ks_engine *ks;
    size_t count;
    unsigned char *encode;
    size_t size;

    if (ks_open(KS_ARCH_X86, KS_MODE_32, &ks) != KS_ERR_OK) {
        throw std::runtime_error("Failed to initialize Keystone engine");
    }

    if (ks_asm(ks, asm_code.c_str(), 0, &encode, &size, &count) != KS_ERR_OK) {
        throw std::runtime_error("Failed to compile asm code: " + std::string(ks_strerror(ks_errno(ks))));
    }

    std::vector<uint8_t> shellcode(encode, encode + size);
    ks_free(encode);
    ks_close(ks);

    return shellcode;
}

void generate_pe_executable(const std::vector<uint8_t>& shellcode, const std::string& output_filename) {
    pe_bliss::pe_base image(pe_bliss::pe_properties_32(), pe_bliss::section_list(), true);
    pe_bliss::section new_section(".text", pe_bliss::readable_code | pe_bliss::executable);

    new_section.get_raw_data().insert(new_section.get_raw_data().end(), shellcode.begin(), shellcode.end());
    image.get_image_sections().push_back(new_section);
    image.set_entry_point(new_section.get_virtual_address());

    std::ofstream output_file(output_filename.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if (!output_file) {
        throw std::runtime_error("Unable to create output file: " + output_filename);
    }

    pe_bliss::rebuild_pe(image, output_file, true);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <asm_file> <output_pe_file>" << std::endl;
        return 1;
    }

    try {
        std::string asm_code = read_asm_code(argv[1]);
        std::vector<uint8_t> shellcode = compile_asm_code(asm_code);
        generate_pe_executable(shellcode, argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "PE executable file successfully generated!" << std::endl;
    return 0;
}
