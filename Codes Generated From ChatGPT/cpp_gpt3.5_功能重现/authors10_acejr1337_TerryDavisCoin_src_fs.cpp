#include <cstdio>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

class FileLock {
    public:
    explicit FileLock(const std::string& filename) {
        file_ = fopen(filename.c_str(), "w+");
    }

    ~FileLock() {
        fclose(file_);
    }

    bool TryLock() {
#ifdef _WIN32
        HANDLE handle = (HANDLE)_get_osfhandle(_fileno(file_));
        return LockFile(handle, 0, 0, 1, 0) != 0;
#else
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_start = 0;
        lock.l_whence = SEEK_SET;
        lock.l_len = 0;
        return fcntl(fileno(file_), F_SETLK, &lock) != -1;
#endif
    }

    private:
    FILE* file_;
};

std::string get_filesystem_error_message() {
#ifdef _WIN32
    DWORD error = GetLastError();
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        nullptr);
    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);
    return message;
#else
    return strerror(errno);
#endif
}

class ifstream: public std::ifstream {
    public:
    void open(const std::string& filename) {
#ifdef _WIN32
        std::ifstream::open(filename, std::ios_base::binary);
#else
        std::ifstream::open(filename);
#endif
    }

    void close() {
#ifdef _WIN32
        if (is_open()) {
            std::ifstream::close();
        }
#else
        std::ifstream::close();
#endif
    }
};

class ofstream: public std::ofstream {
    public:
    void open(const std::string& filename) {
#ifdef _WIN32
        std::ofstream::open(filename, std::ios_base::binary);
#else
        std::ofstream::open(filename);
#endif
    }

    void close() {
#ifdef _WIN32
        if (is_open()) {
            std::ofstream::close();
        }
#else
        std::ofstream::close();
#endif
    }
};

FILE* open_file(const std::string& filename, const char* mode) {
#ifdef _WIN32
    return _wfopen(std::wstring(filename.begin(), filename.end()).c_str(), std::wstring(mode, mode + strlen(mode)).c_str());
#else
    return fopen(filename.c_str(), mode);
#endif
}

int main() {
    FileLock lock("test.txt");
    if (lock.TryLock()) {
        std::cout << "File locked successfully." << std::endl;
    } else {
        std::cout << "Failed to lock file. Error message: " << get_filesystem_error_message() << std::endl;
    }

    ifstream input;
    input.open("test.txt");
    if (input.is_open()) {
        std::cout << "File opened successfully." << std::endl;
        input.close();
    } else {
        std::cout << "Failed to open file. Error message: " << get_file filesystem_error_message() << std::endl;
    }

    ofstream output;
    output.open("test.txt");
    if (output.is_open()) {
        std::cout << "File opened successfully." << std::endl;
        output.close();
    } else {
        std::cout << "Failed to open file. Error message: " << get_filesystem_error_message() << std::endl;
    }

    return 0;
}
