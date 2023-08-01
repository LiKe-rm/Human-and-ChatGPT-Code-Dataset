#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstring>
#include "ffs.h" // FFS相关头文件

using namespace std;
namespace fs = filesystem;

// 错误码定义
enum UEFI_STATUS {
    U_SUCCESS = 0, // 成功
    U_INVALID_PARAMETER, // 参数无效
    U_DIR_ALREADY_EXIST, // 转储目录已存在
    U_ITEM_NOT_FOUND // 没有找到匹配项
};

class FFS_Dumper {
private:
    const char* buffer;
    size_t bufferSize;
    const char* guid; // 要匹配的GUID
    string path; // 转储目录路径
    string reportPath; // 报告文件路径
    vector<string> report; // 报告内容

    // 获取GUID字符串表示形式
    string getGuidStr(const EFI_GUID& guid) {
        char buf[64];
        sprintf_s(buf, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
            guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
        return string(buf);
    }

    // 写入文件
    bool writeFile(const string& path, const char* data, size_t size) {
        ofstream ofs(path, ios::binary);
        if (!ofs) {
            return false;
        }
        ofs.write(data, size);
        ofs.close();
        return true;
    }

    // 递归遍历FFS
    UEFI_STATUS dump(const char* ptr, const char* end) {
        if (ptr >= end) {
            return U_INVALID_PARAMETER;
        }

        // 判断GUID是否匹配
        const EFI_GUID* itemGuid = reinterpret_cast<const EFI_GUID*>(ptr);
        if (guid && memcmp(guid, itemGuid, sizeof(EFI_GUID))) {
            return U_ITEM_NOT_FOUND;
        }

        // 生成文件名
        const char* itemName = ptr + sizeof(EFI_GUID);
        char fileName[64];
        sprintf_s(fileName, "%08X_%s.bin", itemName[3] << 24 | itemName[2] << 16 | itemName[1] << 8 | itemName[0],
            getGuidStr(*itemGuid).c_str());

        // 判断是否为叶子节点
        const uint32_t* itemHeader = reinterpret_cast<const uint32_t*>(itemName + 4);
        const char* itemBody = itemName + *itemHeader;
        if (itemBody > end) {
            return U_INVALID_PARAMETER;
        }

        // 写入文件
        string itemPath = path + "\\" + fileName;
        if (!writeFile(itemPath, itemName, *itemHeader) || !writeFile(itemPath, itemBody, itemHeader[1])) {
            return U_INVALID_PARAMETER;
        }

        // 添加到报告中
        report.emplace_back(itemPath);

        // 递归遍历子项
        const char* nextItem = itemBody + itemHeader[1];
        while (nextItem < end) {
            UEFI_STATUS status = dump(nextItem, end);
            if (status != U_SUCCESS && status != U_ITEM_NOT_FOUND)
            return status;
        }

        return U_SUCCESS;
    }

    // 生成报告文件
    bool generateReport() {
        ofstream ofs(reportPath);
        if (!ofs) {
            return false;
        }
        for (const auto& item : report) {
            ofs << item << endl;
        }
        ofs.close();
        return true;
    }
public:
    FFS_Dumper() : buffer(nullptr), bufferSize(0), guid(nullptr) {}
    // 初始化，返回true表示需要重新初始化
    bool init(const char* buffer, size_t bufferSize, const char* guidStr, const char* inPath) {
        if (buffer == nullptr || bufferSize == 0) {
            return false;
        }

        // 判断是否需要重新初始化
        if (this->buffer != buffer || this->bufferSize != bufferSize) {
            // 解析FFS结构并生成报告
            this->buffer = buffer;
            this->bufferSize = bufferSize;
            this->report.clear();
            const char* ptr = buffer + 4;
            const char* end = buffer + bufferSize;
            while (ptr < end) {
                UEFI_STATUS status = dump(ptr, end);
                if (status != U_SUCCESS && status != U_ITEM_NOT_FOUND) {
                    return false;
                }
                ptr += *(reinterpret_cast<const uint32_t*>(ptr));
            }
            if (report.empty()) {
                return false;
            }

            // 生成转储目录路径和报告文件路径
            path = string(inPath) + ".dump";
            reportPath = string(inPath) + ".report.txt";

            // 检查转储目录是否已存在
            if (fs::exists(path)) {
                return false;
            }

            // 创建转储目录
            if (!fs::create_directory(path)) {
                return false;
            }

            // 保存GUID字符串
            guid = nullptr;
            if (guidStr != nullptr && strlen(guidStr) == 36) {
                guid = reinterpret_cast<const EFI_GUID*>(guidStr);
            }

            // 生成报告文件
            if (!generateReport()) {
                return false;
            }

            return true;
        }

        return false;
    }

    // 转储FFS内容到指定目录
    UEFI_STATUS dump(const char* inPath) {
        if (buffer == nullptr || bufferSize == 0) {
            return U_INVALID_PARAMETER;
        }

        // 初始化
        if (init(buffer, bufferSize, nullptr, inPath)) {
            return U_SUCCESS;
        }

        // 检查转储目录是否已存在
        if (fs::exists(path)) {
            return U_DIR_ALREADY_EXIST;
        }

        // 创建转储目录
        if (!fs::create_directory(path)) {
            return U_INVALID_PARAMETER;
        }

        // 转储FFS内容
        const char* ptr = buffer + 4;
        const char* end = buffer + bufferSize;
        while (ptr < end) {
            UEFI_STATUS status = dump(ptr, end);
            if (status != U_SUCCESS && status != U_ITEM_NOT_FOUND) {
                return status;
            }
            ptr += *(reinterpret_cast<const uint32_t*>(ptr));
        }
        if (report.empty()) {
            return U_ITEM_NOT_FOUND;
        }

        // 生成报告文件
        if (!generateReport()) {
            return U_INVALID_PARAMETER;
        }

        return U_SUCCESS;
    }
}
