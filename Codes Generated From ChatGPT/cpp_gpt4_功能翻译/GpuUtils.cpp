#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class GpuUtils {
private:
    static std::string GPU_LOAD_PATH;
    static std::string GPU_FREQ_PATH;

public:
    static std::string getGpuFreq() {
        if (GPU_FREQ_PATH.empty()) {
            std::string path1 = "/sys/kernel/gpu/gpu_clock";
            std::string path2 = "/sys/class/kgsl/kgsl-3d0/devfreq/cur_freq";
            if (std::filesystem::exists(path1)) {
                GPU_FREQ_PATH = path1;
            } else if (std::filesystem::exists(path2)) {
                GPU_FREQ_PATH = path2;
            } else {
                GPU_FREQ_PATH = "";
            }
        }

        if (GPU_FREQ_PATH.empty()) {
            return "";
        } else {
            std::string freq = readProp(GPU_FREQ_PATH);
            if (freq.length() > 6) {
                return freq.substr(0, freq.length() - 6);
            }
            return freq;
        }
    }

    static int getGpuLoad() {
        if (GPU_LOAD_PATH.empty()) {
            std::string path1 = "/sys/kernel/gpu/gpu_busy";
            std::string path2 = "/sys/class/kgsl/kgsl-3d0/devfreq/gpu_load";
            std::string path3 = "/sys/class/kgsl/kgsl-3d0/gpu_busy_percentage";
            if (std::filesystem::exists(path1)) {
                GPU_LOAD_PATH = path1;
            } else if (std::filesystem::exists(path2)) {
                GPU_LOAD_PATH = path2;
            } else if (std::filesystem::exists(path3)) {
                GPU_LOAD_PATH = path3;
            } else {
                GPU_LOAD_PATH = "";
            }
        }

        if (GPU_LOAD_PATH == "") {
            return -1;
        } else {
            std::string load = readProp(GPU_LOAD_PATH);
            try {
                return std::stoi(load);
            } catch (const std::invalid_argument&) {
                return -1;
            }
        }
    }

private:
    static std::string readProp(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

std::string GpuUtils::GPU_LOAD_PATH = "";
std::string GpuUtils::GPU_FREQ_PATH = "";

int main() {
    std::cout << "GPU Frequency: " << GpuUtils::getGpuFreq() << std::endl;
    std::cout << "GPU Load: " << GpuUtils::getGpuLoad() << std::endl;
    return 0;
}
