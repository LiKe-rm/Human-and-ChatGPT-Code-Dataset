#include <iostream>
#include <vector>
#include <Windows.h>

struct RelocInfo {
    DWORD rva;    // 重定位虚拟地址
    WORD type;    // 重定位类型
};

struct ImportInfo {
    std::string name;    // 导入函数名称
    DWORD rva;           // 导入函数虚拟地址
};

class PEParser {
public:
    PEParser(const std::string& filename) {
        // 打开文件
        hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Cannot open file " << filename << std::endl;
            return;
        }

        // 创建文件映射
        hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        if (hMapping == NULL) {
            std::cerr << "Cannot create file mapping" << std::endl;
            return;
        }

        // 映射文件到内存
        baseAddr = (BYTE*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
        if (baseAddr == NULL) {
            std::cerr << "Cannot map file to memory" << std::endl;
            return;
        }

        // 获取NT头指针
        pNTHeader = (IMAGE_NT_HEADERS*)(baseAddr + ((IMAGE_DOS_HEADER*)baseAddr)->e_lfanew);
    }

    ~PEParser() {
        // 释放资源
        if (baseAddr != NULL) {
            UnmapViewOfFile(baseAddr);
        }
        if (hMapping != NULL) {
            CloseHandle(hMapping);
        }
        if (hFile != INVALID_HANDLE_VALUE) {
            CloseHandle(hFile);
        }
    }

    IMAGE_NT_HEADERS* GetNtHeaders() const {
        if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) {
            return NULL;    // 不是PE文件
        }
        return pNTHeader;
    }

    std::vector<RelocInfo> GetRelocs() const {
        std::vector<RelocInfo> relocs;
        IMAGE_DATA_DIRECTORY* pRelocDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
        if (pRelocDir->VirtualAddress == 0 || pRelocDir->Size == 0) {
            return relocs;    // 没有重定位信息
        }
        IMAGE_BASE_RELOCATION* pRelocBlock = (IMAGE_BASE_RELOCATION*)(baseAddr + pRelocDir->VirtualAddress);
        DWORD blockSize = 0;
        while (blockSize < pRelocDir->Size) {
            DWORD pageRva = pRelocBlock->VirtualAddress;
            DWORD numEntries = (pRelocBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
            WORD* pEntries = (WORD*)((BYTE*)pRelocBlock + sizeof(IMAGE_BASE_RELOCATION));
            for (DWORD i = 0; i < numEntries; i++) {
                DWORD offset = pEntries[i] & 0xfff;
                WORD type = (pEntries[i] >> 12) & 0xf;
                DWORD rva = pageRva + offset;
                relocs.push_back({ rva, type });
            }
            blockSize += pRelocBlock->SizeOfBlock;
            pRelocBlock = (IMAGE_BASE_RELOCATION*)((BYTE*)pRelocBlock + pRelocBlock->SizeOfBlock);
        }
        return relocs;
    }

    std::vector<ImportInfo> GetImports() const {
        std::vector<ImportInfo> imports;
        IMAGE_DATA_DIRECTORY* pImportDir = &pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
        if (pImportDir->VirtualAddress == 0 || pImportDir->Size == 0) {
            return imports;    // 没有导入信息
        }
        IMAGE_IMPORT_DESCRIPTOR* pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(baseAddr + pImportDir->VirtualAddress);
        while (pImportDesc->Name != 0) {
            std::string dllName = (char*)(baseAddr + pImportDesc->Name);
            IMAGE_THUNK_DATA* pThunk = (IMAGE_THUNK_DATA*)(baseAddr + pImportDesc->OriginalFirstThunk);
            if (pImportDesc->OriginalFirstThunk == 0) {
                pThunk = (IMAGE_THUNK_DATA*)(baseAddr + pImportDesc->FirstThunk);
            }
            while (pThunk->u1.AddressOfData != 0) {
                DWORD rva = pThunk->u1.AddressOfData & 0xffff;
                ImportInfo info;
                info.name = (char*)(baseAddr + rva + 2);
                info.rva = pThunk->u1.Function;
                imports.push_back(info);
                pThunk++;
            }
            pImportDesc++;
        }
        return imports;
    }

private:
    HANDLE hFile;
    HANDLE hMapping;
    BYTE* baseAddr;
    IMAGE_NT_HEADERS* pNTHeader;
};
