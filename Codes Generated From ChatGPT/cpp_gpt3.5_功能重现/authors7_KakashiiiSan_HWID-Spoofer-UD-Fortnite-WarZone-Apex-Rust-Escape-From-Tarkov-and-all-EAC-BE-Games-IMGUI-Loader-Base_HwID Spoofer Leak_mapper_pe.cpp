#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <windows.h>

typedef uint8_t byte;

class PEImage {
private:
	std::vector<byte> image;
	std::vector<byte> mapped_image;
	PIMAGE_DOS_HEADER dos_header;
	PIMAGE_NT_HEADERS nt_headers;

	void mapImage();
	void processRelocations(uintptr_t actual_base);
	void resolveImports(std::function<uintptr_t(const char*, const char*)> _get_import_address);

public:
	PEImage(std::vector<byte> _image);
	const std::vector<byte>& getImage() const { return image; }
	const std::vector<byte>& getMappedImage() const { return mapped_image; }
	size_t getSize() const { return image.size(); }
	uintptr_t getImageBase() const { return nt_headers->OptionalHeader.ImageBase; }
	uintptr_t getEntryPoint() const { return nt_headers->OptionalHeader.AddressOfEntryPoint; }
	PIMAGE_DOS_HEADER getDosHeader() const { return dos_header; }
	PIMAGE_NT_HEADERS getNTHeaders() const { return nt_headers; }
	uintptr_t resolveRVA(uintptr_t rva) const;
};

PEImage::PEImage(std::vector<byte> _image) : image(_image) {
	dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(&image[0]);
	nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(&image[dos_header->e_lfanew]);
	mapImage();
}

void PEImage::mapImage() {
	size_t mapped_image_size = nt_headers->OptionalHeader.SizeOfImage;
	mapped_image.resize(mapped_image_size);

	// Copy sections
	for (size_t i = 0; i < nt_headers->FileHeader.NumberOfSections; ++i) {
		PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers) + i;
		size_t section_size = section_header->SizeOfRawData;
		memcpy(&mapped_image[section_header->VirtualAddress], &image[section_header->PointerToRawData], section_size);
	}

	// Process relocations
	processRelocations(getImageBase());

	// Resolve imports
	resolveImports([](const char* lib_name, const char* func_name) -> uintptr_t {
		HMODULE lib = LoadLibraryA(lib_name);
		return reinterpret_cast<uintptr_t>(GetProcAddress(lib, func_name));
		});
}

void PEImage::processRelocations(uintptr_t actual_base) {
	DWORD reloc_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	DWORD reloc_size = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
	PIMAGE_BASE_RELOCATION reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION>(&mapped_image[reloc_rva]);

	intptr_t delta = actual_base - getImageBase();

	while (reloc->SizeOfBlock > 0) {
		byte* reloc_block = &mapped_image[reloc->VirtualAddress];
		DWORD num_entries = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
		WORD* entries = reinterpret_cast<WORD*>(reloc + 1);

		for (DWORD i = 0; i < num_entries; ++i) {
			WORD entry = entries[i];
			WORD type = entry >> 12;
			WORD offset = entry & 0xfff;

			if (type == IMAGE_REL_BASED_HIGHLOW) {
				uintptr_t* addr = reinterpret_cast<uintptr_t*>(reloc_block + offset);
				*addr += delta;
			}
		}

		reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION>(reinterpret_cast<byte*>(reloc) + reloc->SizeOfBlock);
	}
}

void PEImage::resolveImports(std::function<uintptr_t(const char*, const char*)> _get_import_address) {
	DWORD import_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	DWORD import_size = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
	PIMAGE_IMPORT_DESCRIPTOR import_desc = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(&mapped_image[import_rva]);
	while (import_desc->Name != 0) {
		const char* lib_name = reinterpret_cast<const char*>(&mapped_image[import_desc->Name]);
		PIMAGE_THUNK_DATA import_name_table = reinterpret_cast<PIMAGE_THUNK_DATA>(&mapped_image[import_desc->OriginalFirstThunk]);
		PIMAGE_THUNK_DATA import_address_table = reinterpret_cast<PIMAGE_THUNK_DATA>(&mapped_image[import_desc->FirstThunk]);

		for (size_t i = 0; import_name_table[i].u1.AddressOfData != 0; ++i) {
			if (import_name_table[i].u1.Ordinal & IMAGE_ORDINAL_FLAG) {
				WORD ordinal = IMAGE_ORDINAL(import_name_table[i].u1.Ordinal);
				import_address_table[i].u1.Function = _get_import_address(lib_name, reinterpret_cast<const char*>(ordinal));
			}
			else {
				PIMAGE_IMPORT_BY_NAME import_by_name = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(&mapped_image[import_name_table[i].u1.AddressOfData]);
				import_address_table[i].u1.Function = _get_import_address(lib_name, import_by_name->Name);
			}
		}

		import_desc++;
	}
}

uintptr_t PEImage::resolveRVA(uintptr_t rva) const {
	for (size_t i = 0; i < nt_headers->FileHeader.NumberOfSections; ++i) {
		PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers) + i;
		if (rva >= section_header->VirtualAddress && rva < section_header->VirtualAddress + section_header->SizeOfRawData) {
			return rva - section_header->VirtualAddress + section_header->PointerToRawData;
		}
	}
	return 0;
}

int main() {
	// Load a PE image from a file
	std::vector<byte> pe_image_data;
	{
		std::ifstream file("some_pe_file.exe", std::ios::binary);
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);
		pe_image_data.resize(size);
		file.read(reinterpret_cast<char*>(&pe_image_data[0]), size);
	}

	PEImage pe_image(pe_image_data);

	// Do something with the PE image
	// ...

	return 0;
}
