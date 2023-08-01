#include <iostream>
#include <vector>
#include <Windows.h>

struct RelocInfo {
    DWORD VirtualAddress;
    DWORD Size;
};

struct ImportInfo {
    std::string Name;
    std::vector<std::string> Functions;
};

class PEParser {
public:
    PEParser(const std::string& filename);
    ~PEParser();

    PIMAGE_NT_HEADERS GetNtHeaders();
    std::vector<RelocInfo> GetRelocs();
    std::vector<ImportInfo> GetImports();

private:
    LPVOID fileData;
    PIMAGE_DOS_HEADER dosHeader;
    PIMAGE_NT_HEADERS ntHeaders;
};

PEParser::PEParser(const std::string& filename) {
    // Load file into memory
    HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD fileSize = GetFileSize(hFile, nullptr);
    HANDLE hFileMapping = CreateFileMapping(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
    fileData = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);

    // Get DOS header
    dosHeader = (PIMAGE_DOS_HEADER)fileData;

    // Get NT headers
    ntHeaders = (PIMAGE_NT_HEADERS)((BYTE*)fileData + dosHeader->e_lfanew);
}

PEParser::~PEParser() {
    UnmapViewOfFile(fileData);
}

PIMAGE_NT_HEADERS PEParser::GetNtHeaders() {
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE || ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return nullptr;
    }
    return ntHeaders;
}

std::vector<RelocInfo> PEParser::GetRelocs() {
    std::vector<RelocInfo> relocs;

    if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size == 0) {
        return relocs;
    }

    PIMAGE_BASE_RELOCATION baseReloc = (PIMAGE_BASE_RELOCATION)((BYTE*)fileData + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

    while (baseReloc->SizeOfBlock) {
        RelocInfo relocInfo;
        relocInfo.VirtualAddress = baseReloc->VirtualAddress;
        relocInfo.Size = baseReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION);
        relocs.push_back(relocInfo);

        baseReloc = (PIMAGE_BASE_RELOCATION)((BYTE*)baseReloc + baseReloc->SizeOfBlock);
    }

    return relocs;
}

std::vector<ImportInfo> PEParser::GetImports() {
    std::vector<ImportInfo> imports;

    if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size == 0) {
        return imports;
    }

    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)fileData + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    while (importDescriptor->Name) {
        ImportInfo importInfo;
        importInfo.Name = (char*)((BYTE*)fileData + importDescriptor->Name);

        PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)((BYTE*)fileData + importDescriptor->OriginalFirstThunk);
        while (thunk->u1.AddressOfData) {
            PIMAGE_IMPORT_BY_NAME importByName = (PIMAGE_IMPORT_BY_NAME)((BYTE*)fileData + thunk->u1.AddressOfData);
            importInfo.Functions.push_back(std::string(importByName->Name));
            thunk++;
        }
        imports.push_back(importInfo);
        importDescriptor++;
    }

    return imports;
}

