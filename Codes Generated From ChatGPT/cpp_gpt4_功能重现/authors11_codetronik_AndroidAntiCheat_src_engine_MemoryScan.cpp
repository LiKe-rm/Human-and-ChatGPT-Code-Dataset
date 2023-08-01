#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <algorithm>

class MemoryScanner {
public:
    MemoryScanner(uintptr_t moduleBaseAddr);
    ~MemoryScanner();

    void addPattern(const std::vector<uint8_t>& pattern, size_t len, const std::string& name, DWORD protection = PAGE_READWRITE);
    void scan();
    void displayResults();

private:
    struct PatternInfo {
        std::vector<uint8_t> pattern;
        size_t length;
        DWORD protection;
        std::string name;
    };

    uintptr_t moduleBaseAddr;
    std::vector<PatternInfo> patterns;
    std::map<std::string, std::vector<uintptr_t>> results;

    void getMemoryRegions(std::vector<MEMORY_BASIC_INFORMATION>& memRegions);
    size_t searchPatternBoyerMoore(const std::vector<uint8_t>& haystack, const std::vector<uint8_t>& needle);
    std::vector<size_t> computeBadCharacterHeuristic(const std::vector<uint8_t>& pattern);
};

MemoryScanner::MemoryScanner(uintptr_t moduleBaseAddr) : moduleBaseAddr(moduleBaseAddr) {}

MemoryScanner::~MemoryScanner() {}

void MemoryScanner::addPattern(const std::vector<uint8_t>& pattern, size_t len, const std::string& name, DWORD protection) {
    patterns.push_back({pattern, len, protection, name});
}

void MemoryScanner::scan() {
    std::vector<MEMORY_BASIC_INFORMATION> memRegions;
    getMemoryRegions(memRegions);

    for (const auto& region : memRegions) {
        for (const auto& patternInfo : patterns) {
            if (patternInfo.protection == region.Protect) {
                std::vector<uint8_t> buffer(region.RegionSize);
                ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(region.BaseAddress), buffer.data(), region.RegionSize, nullptr);

                size_t offset = searchPatternBoyerMoore(buffer, patternInfo.pattern);
                if (offset != std::string::npos) {
                    results[patternInfo.name].push_back(reinterpret_cast<uintptr_t>(region.BaseAddress) + offset);
                }
            }
        }
    }
}

void MemoryScanner::displayResults() {
    for (const auto& result : results) {
        std::cout << "Pattern: " << result.first << std::endl;
        for (const auto& address : result.second) {
            std::cout << "Address: 0x" << std::hex << address << std::endl;
        }
    }
}

void MemoryScanner::getMemoryRegions(std::vector<MEMORY_BASIC_INFORMATION>& memRegions) {
    MEMORY_BASIC_INFORMATION memInfo;
    uintptr_t address = moduleBaseAddr;

    while (VirtualQuery(reinterpret_cast<LPCVOID>(address), &memInfo, sizeof(memInfo))) {
        memRegions.push_back(memInfo);
        address += memInfo.RegionSize;
    }
}

size_t MemoryScanner::searchPatternBoyerMoore(const std::vector<uint8_t>& haystack, const std::vector<uint8_t>& needle) {
    if (needle.empty() || haystack.empty() || haystack.size() < needle.size()) {
        return std::string::npos;
    }

    std::vector<size_t> badCharShift = computeBadCharacterHeuristic(needle);
    size_t skip;

    for (size_t i = 0; i <= haystack.size() - needle.size(); i += skip) {
        skip = 0;
        for (int j = needle.size() - 1; j >= 0; --j) {
            if (needle[j] != haystack[i + j]) {
                skip = std::max(1, j - static_cast<int>(badCharShift[haystack[i + j]]));
                break;
            }
        }
        if (skip == 0) {
            return i;
        }
    }

    return std::string::npos;
}

std::vector<size_t> MemoryScanner::computeBadCharacterHeuristic(const std::vector<uint8_t>& pattern) {
    const size_t ALPHABET_SIZE = 256;
    std::vector<size_t> badCharShift(ALPHABET_SIZE, pattern.size());

    for (size_t i = 0; i < pattern.size() - 1; ++i) {
        badCharShift[pattern[i]] = pattern.size() - 1 - i;
    }

    return badCharShift;
}

int main() {
    uintptr_t moduleBaseAddr = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    MemoryScanner memoryScanner(moduleBaseAddr);

    memoryScanner.addPattern({0x48, 0x89, 0x5C, 0x24, 0x08}, 5, "Pattern1");
    memoryScanner.addPattern({0x57, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B}, 7, "Pattern2");

    memoryScanner.scan();
    memoryScanner.displayResults();

    return 0;
}

