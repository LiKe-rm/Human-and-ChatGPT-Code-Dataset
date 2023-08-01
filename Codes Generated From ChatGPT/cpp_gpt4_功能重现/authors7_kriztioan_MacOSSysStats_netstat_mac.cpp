#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cmath>
#include <sys/sysctl.h>
#include <NetworkStatistics.h>

struct ProcessData {
    std::string name;
    uint64_t bytesReceived;
    uint64_t bytesSent;
    std::chrono::steady_clock::time_point timestamp;
};

std::string formatBytes(uint64_t bytes) {
    const char* units[] = {"B", "kiB", "MiB", "GiB", "TiB"};
    int unitIndex = 0;
    double adjustedBytes = bytes;

    while (adjustedBytes >= 1024 && unitIndex < 4) {
        adjustedBytes /= 1024;
        unitIndex++;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << adjustedBytes << " " << units[unitIndex];
    return oss.str();
}

std::string getProcessName(pid_t pid) {
    char pathBuffer[PROC_PIDPATHINFO_MAXSIZE];
    if (proc_pidpath(pid, pathBuffer, sizeof(pathBuffer)) <= 0) {
        return "unknown";
    }

    std::string fullPath(pathBuffer);
    size_t lastSlash = fullPath.find_last_of("/");
    if (lastSlash == std::string::npos) {
        return fullPath;
    }

    return fullPath.substr(lastSlash + 1);
}

void processStats(void* context, NStatSourceRef source) {
    auto& processData = *reinterpret_cast<std::unordered_map<pid_t, ProcessData>*>(context);
    pid_t pid = NStatSourceGetPID(source);

    if (processData.count(pid) == 0) {
        processData[pid].name = getProcessName(pid);
    }

    NStatData data;
    NStatSourceQueryDescription(source, &data);

    processData[pid].bytesReceived = data.rxBytes;
    processData[pid].bytesSent = data.txBytes;
    processData[pid].timestamp = std::chrono::steady_clock::now();
}

int main() {
    std::unordered_map<pid_t, ProcessData> processData;
    NStatManagerRef manager = NStatManagerCreate();
    NStatManagerSetInterfaceTraceFD(manager, -1);
    NStatManagerSetFlags(manager, 0);

    NStatSourceRef descriptor = NStatManagerAddAllTCP(manager);
    NStatSourceSetCallback(descriptor, processStats, &processData);
    NStatManagerQueryAllSources(manager, 0);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::vector<std::pair<pid_t, double>> rates;
    NStatManagerQueryAllSources(manager, 0);
    for (const auto& [pid, data] : processData) {
        auto now = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - data.timestamp).count() / 1000.0;

        uint64_t totalBytes = data.bytesReceived + data.bytesSent;
        double rate = totalBytes / elapsedTime;
        rates.emplace_back(pid, rate);
    }

    std::sort(rates.begin(), rates.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::cout << "PID\tProcess Name\t\tRate\n";
    std::cout << "---------------------------------------------\n";
    for (const auto& [pid, rate] : rates) {
        std::cout << pid << "\t" << processData[pid].name << "\t\t" << formatBytes(rate) << "/s\n";
    }
    NStatManagerDestroy(manager);
    return 0;
}
