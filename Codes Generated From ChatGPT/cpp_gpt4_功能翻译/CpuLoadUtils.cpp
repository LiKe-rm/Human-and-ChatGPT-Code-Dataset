#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <stdexcept>

class CpuLoadUtils {
private:
    std::string lastCpuState = "";
    std::string lastCpuStateSum = "";

    std::string executeCommand(const std::string& command) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    int getCpuIndex(std::vector<std::string>& cols) {
        int cpuIndex = -1;
        if (cols[0] == "cpu") {
            cpuIndex = -1;
        } else {
            cpuIndex = std::stoi(cols[0].substr(3));
        }
        return cpuIndex;
    }

    long cpuTotalTime(std::vector<std::string>& cols) {
        long totalTime = 0;
        for (size_t i = 1; i < cols.size(); i++) {
            totalTime += std::stol(cols[i]);
        }
        return totalTime;
    }

    long cpuIdleTime(std::vector<std::string>& cols) {
        return std::stol(cols[4]);
    }

public:
    CpuLoadUtils() {
        lastCpuState = executeCommand("cat /proc/stat | grep '^cpu'");
        lastCpuStateSum = lastCpuState;
    }

    std::map<int, double> getCpuLoad() {
        std::map<int, double> loads;
        std::string times = executeCommand("cat /proc/stat | grep '^cpu'");
        if (!times.empty() && times.substr(0, 3) == "cpu") {
            try {
                if (lastCpuState.empty()) {
                    lastCpuState = times;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    return getCpuLoad();
                } else {
                    std::vector<std::string> curTick = split(times, '\n');
                    std::vector<std::string> prevTick = split(lastCpuState, '\n');

                    for (const auto& cpuCurrentTime : curTick) {
                        std::vector<std::string> cols1 = split(cpuCurrentTime, ' ');
                        std::vector<std::string> cols0;
                        for (const auto& cpu : prevTick) {
                            if (cpu.substr(0, cols1[0].length() + 1) == (cols1[0] + " ")) {
                                cols0 = split(cpu, ' ');
                                break;
                            }
                        }
                        if (!cols0.empty()) {
                            long total1 = cpuTotalTime(cols1);
                            long idle1 = cpuIdleTime(cols1);
                            long total0 = cpuTotalTime(cols0);
                            long idle0 = cpuIdleTime(cols0);
                            long timePoor = total1 - total0;
                            if (timePoor == 0) {
                                loads[getCpuIndex(cols1)] = 0;
                            } else {
                                long idleTimePoor = idle1 - idle0;
                                if (idleTimePoor < 1) {
                                    loads[getCpuIndex(cols1)] = 100;
                                } else {
                                    double load = 100 - (idleTimePoor * 100.0 / timePoor);
                                    loads[getCpuIndex(cols1)] = load;
                                }
                            }
                        } else {
                            loads[getCpuIndex(cols1)] = 0;
                        }
                    }
                    lastCpuState = times;
                    return loads;
                }
            } catch (std::exception& ex) {
                return loads;
            }
        } else {
            return loads;
        }
    }

    double getCpuLoadSum() {
        std::string times = executeCommand("cat /proc/stat | grep '^cpu '");
        if (!times.empty() && times.substr(0, 4) == "cpu ") {
            try {
                if (lastCpuStateSum.empty()) {
                    lastCpuStateSum = times;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    return getCpuLoadSum();
                } else {
                    std::vector<std::string> curTick = split(times, '\n');
                    std::vector<std::string> prevTick = split(lastCpuStateSum, '\n');
                    for (const auto& cpuCurrentTime : curTick) {
                        std::vector<std::string> cols1 = split(cpuCurrentTime, ' ');
                        if (cols1[0] == "cpu") {
                            std::vector<std::string> cols0;
                            for (const auto& cpu : prevTick) {
                                if (cpu.substr(0, 4) == "cpu ") {
                                    lastCpuStateSum = times;
                                    cols0 = split(cpu, ' ');
                                    long total1 = cpuTotalTime(cols1);
                                    long idle1 = cpuIdleTime(cols1);
                                    long total0 = cpuTotalTime(cols0);
                                    long idle0 = cpuIdleTime(cols0);
                                    long timePoor = total1 - total0;
                                    if (timePoor == 0) {
                                        return 0;
                                    } else {
                                        long idleTimePoor = idle1 - idle0;
                                        if (idleTimePoor < 1) {
                                            return 100;
                                        } else {
                                            return 100 - (idleTimePoor * 100.0 / timePoor);
                                        }
                                    }
                                }
                            }
                            return 0;
                        }
                    }
                }
            } catch (std::exception& ex) {
                return -1;
            }
        }
        return -1;
    }
};

