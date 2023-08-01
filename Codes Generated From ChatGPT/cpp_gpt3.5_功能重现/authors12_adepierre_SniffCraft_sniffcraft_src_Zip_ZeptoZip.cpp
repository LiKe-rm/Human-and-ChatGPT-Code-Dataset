#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <zlib.h>
#include "crc32.h"

#pragma pack(push, 1)
struct LocalFileHeader {
    uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t compression;
    uint16_t modTime;
    uint16_t modDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t fileNameLength;
    uint16_t extraFieldLength;
};

struct CentralDirectoryFileHeader {
    uint32_t signature;
    uint16_t versionMadeBy;
    uint16_t versionNeeded;
    uint16_t flags;
    uint16_t compression;
    uint16_t modTime;
    uint16_t modDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t fileNameLength;
    uint16_t extraFieldLength;
    uint16_t commentLength;
    uint16_t diskNumberStart;
    uint16_t internalFileAttributes;
    uint32_t externalFileAttributes;
    uint32_t relativeOffset;
};

struct EndOfCentralDirectoryRecord {
    uint32_t signature;
    uint16_t diskNumber;
    uint16_t centralDirectoryDisk;
    uint16_t diskEntries;
    uint16_t totalEntries;
    uint32_t centralDirectorySize;
    uint32_t centralDirectoryOffset;
    uint16_t commentLength;
};
#pragma pack(pop)

std::vector<char> readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);
    return buffer;
}

void writeFile(const std::string& filePath, const std::vector<char>& data) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not create file: " + filePath);
    }
    file.write(data.data(), data.size());
}

std::vector<char> compressData(const std::vector<char>& inputData) {
    uLong sourceSize = inputData.size();
    uLong destSize = compressBound(sourceSize);
    std::vector<char> compressedData(destSize);

    if (compress(reinterpret_cast<Bytef*>(compressedData.data()), &destSize,
                 reinterpret_cast<const Bytef*>(inputData.data()), sourceSize) != Z_OK) {
        throw std::runtime_error("Compression failed.");
    }

    compressedData.resize(destSize);
    return compressedData;
}

uint16_t dosDateTime() {
    time_t t = time(nullptr);
    tm* timeStruct = localtime(&t);
    uint16_t date = (timeStruct->tm_year - 80) << 9 | (timeStruct->tm_mon + 1) << 5 | timeStruct->tm_mday;
    uint16_t time = timeStruct->tm_hour << 11 | timeStruct->tm_min << 5 | timeStruct->tm_sec / 2;
    return (date << 16) | time;
}

void createCompressedFile(const std::string& outputPath, const std::vector<std::string>& inputFiles, bool compress) {
    std::ofstream output(outputPath, std::ios::binary);
    if (!output) {
        throw std::runtime_error("Could not create output file: " + outputPath);
    }

    std::vector<CentralDirectoryFileHeader> centralDirectory;
    uint32_t centralDirectorySize = 0;

    for (const auto& inputFile : inputFiles) {
        std::vector<char> fileData = readFile(inputFile);
        uint32_t uncompressedSize = fileData.size();
        uint32_t compressedSize = 0;
        uint32_t crc = crc32(0, reinterpret_cast<const Bytef*>(fileData.data()), uncompressedSize);

        if (compress) {
            fileData = compressData(fileData);
            compressedSize = fileData.size();
        } else {
            compressedSize = uncompressedSize;
        }

        LocalFileHeader localHeader;
        memset(&localHeader, 0, sizeof(LocalFileHeader));
        localHeader.signature = 0x04034B50;
        localHeader.version = 20;
        localHeader.compression = compress ? 8 : 0;
        localHeader.modTime = dosDateTime() & 0xFFFF;
        localHeader.modDate = dosDateTime() >> 16;
        localHeader.crc32 = crc;
        localHeader.compressedSize = compressedSize;
        localHeader.uncompressedSize = uncompressedSize;
        localHeader.fileNameLength = inputFile.size();

        output.write(reinterpret_cast<const char*>(&localHeader), sizeof(LocalFileHeader));
        output.write(inputFile.c_str(), inputFile.size());
        output.write(fileData.data(), fileData.size());

        CentralDirectoryFileHeader centralHeader;
        memset(&centralHeader, 0, sizeof(CentralDirectoryFileHeader));
        centralHeader.signature = 0x02014B50;
        centralHeader.versionMadeBy = 20;
        centralHeader.versionNeeded = 20;
        centralHeader.flags = 0;
        centralHeader.compression = localHeader.compression;
        centralHeader.modTime = localHeader.modTime;
        centralHeader.modDate = localHeader.modDate;
        centralHeader.crc32 = localHeader.crc32;
        centralHeader.compressedSize = localHeader.compressedSize;
        centralHeader.uncompressedSize = localHeader.uncompressedSize;
        centralHeader.fileNameLength = localHeader.fileNameLength;
        centralHeader.relativeOffset = output.tellp() - (sizeof(LocalFileHeader) + inputFile.size() + fileData.size());

        centralDirectory.push_back(centralHeader);
        centralDirectorySize += sizeof(CentralDirectoryFileHeader) + inputFile.size();
    }

    uint32_t centralDirectoryOffset = output.tellp();

    for (const auto& centralHeader : centralDirectory) {
        output.write(reinterpret_cast<const char*>(&centralHeader), sizeof(CentralDirectoryFileHeader));
        output.write(inputFiles[centralHeader.relativeOffset / sizeof(LocalFileHeader)].c_str(), centralHeader.fileNameLength);
    }

    EndOfCentralDirectoryRecord endRecord;
    memset(&endRecord, 0, sizeof(EndOfCentralDirectoryRecord));
    endRecord.signature = 0x06054B50;
    endRecord.totalEntries = centralDirectory.size();
    endRecord.diskEntries = endRecord.totalEntries;
    endRecord.centralDirectorySize = centralDirectorySize;
    endRecord.centralDirectoryOffset = centralDirectoryOffset;

    output.write(reinterpret_cast<const char*>(&endRecord), sizeof(EndOfCentralDirectoryRecord));
    output.close();
}

