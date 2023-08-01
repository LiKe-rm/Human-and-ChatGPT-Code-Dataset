#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class FileHandler {
private:
    std::string currentDir;
    std::vector<std::string> fileList;
    std::string extension;

    bool hasParentDir() {
        return currentDir != "/";
    }

    void filterFiles() {
        DIR* dir;
        struct dirent* ent;
        if ((dir = opendir(currentDir.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                std::string filename = ent->d_name;
                if (filename != "." && filename != "..") {
                    if (extension.empty() || filename.substr(filename.find_last_of(".") + 1) == extension) {
                        fileList.push_back(filename);
                    }
                }
            }
            closedir(dir);
        } else {
            perror("");
        }
    }

public:
    FileHandler(const std::string& dir, const std::string& ext) : currentDir(dir), extension(ext) {
        filterFiles();
    }

    void printFiles() {
        for (const auto& file : fileList) {
            std::cout << file << std::endl;
        }
    }

    void changeDir(const std::string& dir) {
        currentDir = dir;
        fileList.clear();
        filterFiles();
    }

    void goToParent() {
        if (hasParentDir()) {
            size_t found = currentDir.find_last_of("/\\");
            changeDir(currentDir.substr(0,found));
        }
    }

    std::vector<std::string> getFileList() {
        return fileList;
    }
};

int main() {
    FileHandler fileHandler("/home/user", "txt");
    fileHandler.printFiles();
    fileHandler.goToParent();
    fileHandler.printFiles();
    return 0;
}
