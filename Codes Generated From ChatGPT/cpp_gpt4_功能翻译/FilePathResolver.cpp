#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

class FilePathResolver {
public:
    std::string getPath(const std::string& filePath) {
        // Check if file exists
        if (std::filesystem::exists(filePath)) {
            return filePath;
        } else {
            return "File does not exist.";
        }
    }

    void createFile(const std::string& filePath) {
        std::ofstream file(filePath);
        file.close();
    }

    void writeToFile(const std::string& filePath, const std::string& content) {
        std::ofstream file(filePath, std::ios::app); // open in append mode
        if (file.is_open()) {
            file << content << "\n";
            file.close();
        } else {
            std::cout << "Unable to open file for writing.\n";
        }
    }

    std::string readFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::stringstream buffer;
        if (file.is_open()) {
            buffer << file.rdbuf();
            file.close();
        } else {
            std::cout << "Unable to open file for reading.\n";
        }
        return buffer.str();
    }

    void deleteFile(const std::string& filePath) {
        if (std::filesystem::remove(filePath)) {
            std::cout << "File deleted successfully.\n";
        } else {
            std::cout << "Failed to delete the file.\n";
        }
    }

    uintmax_t getFileSize(const std::string& filePath) {
        try {
            return std::filesystem::file_size(filePath);
        } catch (std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }
        return 0;
    }

    // And so on with other file operations...
};

int main() {
    FilePathResolver fileResolver;
    std::string filePath = "/path/to/file.txt";
    std::cout << fileResolver.getPath(filePath) << "\n";
    fileResolver.createFile(filePath);
    fileResolver.writeToFile(filePath, "Hello, World!");
    std::cout << fileResolver.readFromFile(filePath) << "\n";
    std::cout << "File size: " << fileResolver.getFileSize(filePath) << " bytes\n";
    fileResolver.deleteFile(filePath);
    return 0;
}
