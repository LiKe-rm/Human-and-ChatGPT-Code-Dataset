#include <iostream>
#include <functional>
#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class InstallServiceHelpers {
public:
    static std::optional<int> foldDownloadSize(const std::optional<int>& first, const std::optional<int>& second) {
        if (first.has_value() && second.has_value()) {
            return first.value() + second.value();
        }
        return std::nullopt;
    }
};

class File {
public:
    std::string name;
    std::optional<int> downloadSize;

    File(const std::string& name, const std::optional<int>& downloadSize) : name(name), downloadSize(downloadSize) {}
};

std::vector<File> readFiles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<File> files;
    std::string line;
    while (std::getline(file, line)) {
        std::string name = line.substr(0, line.find(','));
        std::string sizeStr = line.substr(line.find(',') + 1);
        std::optional<int> size;
        if (sizeStr != "null") {
            size = std::stoi(sizeStr);
        }
        files.emplace_back(name, size);
    }
    file.close();
    return files;
}

int main() {
    try {
        auto files = readFiles("files.txt");

        std::optional<int> totalSize;
        for (const auto& file : files) {
            totalSize = InstallServiceHelpers::foldDownloadSize(totalSize, file.downloadSize);
        }

        if (totalSize.has_value()) {
            std::cout << "Total download size: " << totalSize.value() << " bytes" << std::endl;
        } else {
            std::cout << "Total download size is unknown" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
