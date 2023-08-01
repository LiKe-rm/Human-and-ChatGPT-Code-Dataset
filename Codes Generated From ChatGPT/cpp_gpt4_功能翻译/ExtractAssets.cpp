#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace fs = boost::filesystem;

class ExtractAssets {
private:
    // To record the extracted resources to avoid repeated extraction
    static std::unordered_map<std::string, std::string> extractHistory;
    fs::path context;

public:
    explicit ExtractAssets(const fs::path &context) : context(context) {}

    static std::string readFileIntoString(const fs::path& path) {
        std::ifstream inputFile(path.string());
        return std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    }

    std::string extractScript(const std::string &fileName) {
        if (fileName.empty() || !fs::exists(context / fileName)) {
            return "";
        }

        if (extractHistory.count(fileName) > 0) {
            return extractHistory[fileName];
        }

        std::string fileContent = readFileIntoString(context / fileName);
        extractHistory[fileName] = fileContent;
        return fileContent;
    }

    std::string extractResource(const std::string &fileName) {
        if (fileName.empty() || !fs::exists(context / fileName)) {
            return "";
        }

        if (extractHistory.count(fileName) > 0) {
            return extractHistory[fileName];
        }

        if (fs::extension(fileName) == ".sh") {
            return extractScript(fileName);
        }

        std::string fileContent = readFileIntoString(context / fileName);
        extractHistory[fileName] = fileContent;
        return fileContent;
    }

    std::string extractResources(const std::string &dir) {
        if (dir.empty() || !fs::exists(context / dir)) {
            return "";
        }

        if (extractHistory.count(dir) > 0) {
            return extractHistory[dir];
        }

        if (fs::is_directory(context / dir)) {
            fs::directory_iterator endIter;
            for (fs::directory_iterator dirItr(context / dir); dirItr != endIter; ++dirItr) {
                if (fs::is_regular_file(dirItr->status())) {
                    std::string fileContent = readFileIntoString(dirItr->path());
                    extractHistory[dirItr->path().string()] = fileContent;
                }
            }
            return dir; // return directory path if directory
        } else {
            return extractResource(dir);
        }
    }
};

std::unordered_map<std::string, std::string> ExtractAssets::extractHistory = {};

int main() {
    ExtractAssets extractor("assets");
    std::cout << "Extracted content of file1.sh: " << extractor.extractResource("file1.sh") << std::endl;
    std::cout << "Extracted content of directory dir1: " << extractor.extractResources("dir1") << std::endl;
    return 0;
}
