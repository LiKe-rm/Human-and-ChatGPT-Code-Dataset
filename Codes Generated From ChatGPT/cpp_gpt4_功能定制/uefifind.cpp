#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include <winioctl.h>
#include <winerror.h>
#include <ntdddisk.h>
#include <ntddscsi.h>
#include <ntddstor.h>
#include <ntddndis.h>
#include <ntddser.h>
#include <ntddmodm.h>
#include <winioctl.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "UEFIFind.h"

using namespace std;

// 用于从字符串中提取 GUID
GUID stringToGuid(string s) {
    GUID guid;
    wstringstream ss;
    ss << s;
    ss >> hex >> guid.Data1;
    ss.ignore(1);
    ss >> hex >> guid.Data2;
    ss.ignore(1);
    ss >> hex >> guid.Data3;
    ss.ignore(1);
    for (int i = 0; i < 8; i++) {
        int byte;
        ss >> hex >> byte;
        guid.Data4[i] = (unsigned char)byte;
        if (i < 7) {
            ss.ignore(1);
        }
    }
    return guid;
}

// 用于将 GUID 转换为字符串
string guidToString(GUID guid) {
    ostringstream ss;
    ss << uppercase << hex << setw(8) << setfill('0') << guid.Data1 << "-"
        << setw(4) << setfill('0') << guid.Data2 << "-"
        << setw(4) << setfill('0') << guid.Data3 << "-"
        << setw(2) << setfill('0') << (int)guid.Data4[0]
        << setw(2) << setfill('0') << (int)guid.Data4[1] << "-"
        << setw(2) << setfill('0') << (int)guid.Data4[2]
        << setw(2) << setfill('0') << (int)guid.Data4[3]
        << setw(2) << setfill('0') << (int)guid.Data4[4]
        << setw(2) << setfill('0') << (int)guid.Data4[5]
        << setw(2) << setfill('0') << (int)guid.Data4[6]
        << setw(2) << setfill('0') << (int)guid.Data4[7];
    return ss.str();
}

// UEFI 文件系统信息结构体
struct UEFIFileSystemInfo {
    uint64_t rootDirOffset; // 根目录偏移量
    uint64_t sizeOfEntries; // 目录项大小
    uint64_t entryCount;    // 目录项数量
};

// UEFI 文件系统目录项结构体
struct UEFIFileSystemEntry {
    uint8_t  status;
    uint8_t  reserved[7];
    uint64_t startLBA;
    uint64_t size;
};

// UEFI 文件系统目录项状态
#define UEFI_FS_ENTRY_STATUS_FREE       0x00 // 空闲目录项
#define UEFI_FS_ENTRY_STATUS_ALLOCATED  0x01 // 已分配目录项
#define UEFI_FS_ENTRY_STATUS_DELETED    0xE5 // 已删除目录项
 
// UEFI 文件系统常量
#define UEFI_FS_SIG 0x5452415020494645 // "EFI PART"
#define UEFI_FS_ENTRY_SIZE 0x20 // 目录项大小

// UEFI 文件系统头结构体
#pragma pack(push, 1)
struct UEFIFileSystemHeader {
    uint64_t signature;
    uint32_t revision;
    uint32_t headerSize;
    uint32_t headerCRC32;
    uint32_t reserved1;
    uint64_t myLBA;
    uint64_t alternateLBA;
    uint64_t firstUsableLBA;
    uint64_t lastUsableLBA;
    GUID diskGUID;
    uint64_t partitionStart;
    uint64_t partitionSize;
    uint32_t flags;
    uint8_t reserved2[0x5C];
};
#pragma pack(pop)

// UEFI 文件系统 GUID
const GUID UEFI_FS_GUID = stringToGuid("C12A7328-F81F-11D2-BA4B-00A0C93EC93B");

// UEFIFind 类的实现
UEFIFind::UEFIFind(string imageFile, vector<string> guids) {
    // 打开镜像文件
    this->imageFile = imageFile;
    this->imageStream.open(imageFile, ios::binary);
    if (!this->imageStream.is_open()) {
        cout << "Error: Could not open image file " << imageFile << endl;
        exit(1);
    }

    // 初始化 GUIDs
    for (string guid : guids) {
        this->guids.push_back(stringToGuid(guid));
    }
}

UEFIFind::~UEFIFind() {
    this->imageStream.close();
}

// 查找 GUID 或文本模式
int UEFIFind::search(string pattern, string resultType) {
    if (resultType != "offset" && resultType != "guid") {
        cout << "Error: Invalid result type " << resultType << endl;
        exit(1);
    }
    if (pattern.size() == 36) {
        // 输入为 GUID，直接解析
        GUID guid = stringToGuid(pattern);
        return searchGuid(guid, resultType);
    } else {
        // 输入为文本模式，转换为 UTF-16LE 编码后搜索
        wstring widePattern(pattern.length(), L' ');
        copy(pattern.begin(), pattern.end(), widePattern.begin());
        return searchText(widePattern, resultType);
    }
}

// 查找 GUID
int UEFIFind::searchGuid(GUID guid, string resultType) {
    int count = 0;
    for (int i = 0; i < this->imageStreams.size(); i++) {
        // 定位 GPT 分区的 UEFI 文件系统
        this->imageStreams[i].seekg(0);
        UEFIFileSystemHeader fsHeader;
        this->imageStreams[i].read((char*)&fsHeader, sizeof(fsHeader));

        if (fsHeader.signature != UEFI_FS_SIG) {
            continue; // 不是 UEFI 文件系统，跳过
        }

        if (fsHeader.diskGUID != this->guids[i]) {
            continue; // GUID 不匹配，跳过
        }

        // 读取文件系统信息
        UEFIFileSystemInfo fsInfo;
        fsInfo.rootDirOffset = UEFI_FS_ENTRY_SIZE * 2; // 根目录在第 3 个目录项后面
        fsInfo.sizeOfEntries = UEFI_FS_ENTRY_SIZE;
        fsInfo.entryCount = (fsHeader.lastUsableLBA - fsHeader.firstUsableLBA + 1) * 512 / fsInfo.sizeOfEntries;
        // 定位根目录
        this->imageStreams[i].seekg(fsInfo.rootDirOffset);

        for (int j = 0; j < fsInfo.entryCount; j++) {
            UEFIFileSystemEntry entry;
            this->imageStreams[i].read((char*)&entry, sizeof(entry));

            if (entry.status != UEFI_FS_ENTRY_STATUS_ALLOCATED) {
                continue; // 目录项未分配，跳过
            }

            // 检查文件名是否为 GUID
            string fileName;
            char nameBuffer[512];
            uint64_t offset = (entry.startLBA * 512) + sizeof(UEFIFileSystemHeader);
            this->imageStreams[i].seekg(offset);
            this->imageStreams[i].read(nameBuffer, 512);
            fileName = string(nameBuffer, 36);

            if (fileName == guidToString(guid)) {
                // 找到匹配的文件名，输出结果
                if (resultType == "offset") {
                    cout << "0x" << hex << offset << endl;
                } else {
                    cout << guidToString(this->guids[i]) << endl;
                }
                count++;
            }
        }
    }

    return count;
}

// 查找文本
int UEFIFind::searchText(wstring pattern, string resultType) {
    int count = 0;
    for (int i = 0; i < this->imageStreams.size(); i++) {
        // 定位 GPT 分区的 UEFI 文件系统
        this->imageStreams[i].seekg(0);
        UEFIFileSystemHeader fsHeader;
        this->imageStreams[i].read((char*)&fsHeader, sizeof(fsHeader));

        if (fsHeader.signature != UEFI_FS_SIG) {
            continue; // 不是 UEFI 文件系统，跳过
        }

        if (fsHeader.diskGUID != this->guids[i]) {
            continue; // GUID 不匹配，跳过
        }

        // 读取文件系统信息
        UEFIFileSystemInfo fsInfo;
        fsInfo.rootDirOffset = UEFI_FS_ENTRY_SIZE * 2; // 根目录在第 3 个目录项后面
        fsInfo.sizeOfEntries = UEFI_FS_ENTRY_SIZE;
        fsInfo.entryCount = (fsHeader.lastUsableLBA - fsHeader.firstUsableLBA + 1) * 512 / fsInfo.sizeOfEntries;

        // 定位根目录
        this->imageStreams[i].seekg(fsInfo.rootDirOffset);

        for (int j = 0; j < fsInfo.entryCount; j++) {
            UEFIFileSystemEntry entry;
            this->imageStreams[i].read((char*)&entry, sizeof(entry));

            if (entry.status != UEFI_FS_ENTRY_STATUS_ALLOCATED) {
                continue; // 目录项未分配，跳过
            }

            // 读取文件名
            wstring fileName;
            char nameBuffer[512];
            uint64_t offset = (entry.startLBA * 512) + sizeof(UEFIFileSystemHeader);
            // 读取文件名
            wstring fileName;
            char nameBuffer[512];
            uint64_t offset = (entry.startLBA * 512) + sizeof(UEFIFileSystemHeader);
            this->imageStreams[i].seekg(offset);
            this->imageStreams[i].read(nameBuffer, 512);
            fileName = wstring((wchar_t*)nameBuffer, 36);
            // 搜索文件内容
            bool found = false;
            uint64_t fileSize = entry.size;
            uint64_t fileOffset = offset + 512;
            uint64_t readSize = min((uint64_t)512, fileSize);
            char fileBuffer[512];

            while (fileSize > 0) {
                this->imageStreams[i].seekg(fileOffset);
                this->imageStreams[i].read(fileBuffer, readSize);
                wstring fileContents = wstring((wchar_t*)fileBuffer, readSize / 2);

                size_t pos = fileContents.find(pattern);
                if (pos != string::npos) {
                    found = true;
                    break;
                }

                fileSize -= readSize;
                fileOffset += readSize;
                readSize = min((uint64_t)512, fileSize);
            }

            if (found) {
                // 找到匹配的文件内容，输出结果
                if (resultType == "offset") {
                    cout << "0x" << hex << offset << endl;
                } else {
                    cout << guidToString(this->guids[i]) << endl;
                }
                count++;
            }
        }
    }

    return count;
}
