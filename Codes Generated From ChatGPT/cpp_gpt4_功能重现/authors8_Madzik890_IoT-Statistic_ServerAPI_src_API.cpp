#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

// 1. 检查指定名称的进程是否正在运行，并返回该进程的进程ID（PID）
pid_t findProcessByName(const string& processName) {
    DIR* dir;
    struct dirent* ent;
    char path[PATH_MAX];

    if ((dir = opendir("/proc")) == nullptr) {
        perror("opendir");
        return -1;
    }

    while ((ent = readdir(dir)) != nullptr) {
        long pid = strtol(ent->d_name, nullptr, 10);
        if (pid <= 0) {
            continue;
        }

        snprintf(path, sizeof(path), "/proc/%ld/comm", pid);
        ifstream in(path);
        if (in.is_open()) {
            string name;
            getline(in, name);
            if (name == processName) {
                in.close();
                closedir(dir);
                return static_cast<pid_t>(pid);
            }
        }
    }

    closedir(dir);
    return -1;
}

// 2. 返回设备信息文件夹中所有设备的GUID
vector<string> getDevicesGUIDs(const string& folderPath) {
    vector<string> guids;
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(folderPath.c_str())) == nullptr) {
        perror("opendir");
        return guids;
    }

    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_type == DT_REG) {
            guids.push_back(string(ent->d_name));
        }
    }

    closedir(dir);
    return guids;
}

// 3. 返回设备日志文件夹中所有设备的GUID
vector<string> getDevicesLogGUIDs(const string& folderPath) {
    return getDevicesGUIDs(folderPath);
}

// 4. 返回指定GUID的设备的信息
struct DeviceInfo {
    float cpuTemperature;
    long availableMemory;
    long availableDiskSpace;
};

DeviceInfo getDeviceInfoByGUID(const string& guid, const string& folderPath) {
    DeviceInfo info;
    string filePath = folderPath + "/" + guid;
    ifstream in(filePath);

    if (!in.is_open()) {
        perror("open file");
        return info;
    }

    in >> info.cpuTemperature;
    in >> info.availableMemory;
    in >> info.availableDiskSpace;

    in.close();
    return info;
}

// 5. 返回指定GUID的设备的日志文件内容
string getDeviceLogByGUID(const string& guid, const string& folderPath) {
    string filePath = folderPath + "/" + guid;
    ifstream in(filePath);

    if (!in.is_open()) {
        perror("open file");
        return "";
    }

    stringstream buffer;
    buffer << in.rdbuf();
    in.close();

    return buffer.str();
}
