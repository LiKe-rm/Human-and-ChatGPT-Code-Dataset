#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <openssl/md5.h>

class FileMD5 {
public:
    void getFile() {
        std::string path = "/path/to/file";
        std::string file = path + "/e8706cf83a2cda33dae5c40025922d75.apk";
        std::string md5 = getFileMD5(file);
        std::cout << "MD5: " << md5 << std::endl;
    }

    std::string getFileMD5(const std::string& filename) {
        std::ifstream file(filename.c_str(), std::ifstream::binary);
        if (!file) {
            return "";
        }

        MD5_CTX md5Context;
        MD5_Init(&md5Context);

        char buffer[1024];
        while (file.good()) {
            file.read(buffer, sizeof(buffer));
            MD5_Update(&md5Context, buffer, file.gcount());
        }

        unsigned char result[MD5_DIGEST_LENGTH];
        MD5_Final(result, &md5Context);

        return bytesToHexString(result, MD5_DIGEST_LENGTH);
    }

    std::string bytesToHexString(unsigned char* data, int len) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (int i = 0; i < len; ++i) {
            ss << std::setw(2) << static_cast<unsigned>(data[i]);
        }
        return ss.str();
    }
};

int main() {
    FileMD5 fileMD5;
    fileMD5.getFile();
    return 0;
}
