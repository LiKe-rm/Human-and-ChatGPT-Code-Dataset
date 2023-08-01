#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

class Stream {
public:
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
};

class StreamExtension: public Stream {
public:
    StreamExtension(Stream &stream) : _stream(stream) {}

    void setTimeout(unsigned long timeout) { _timeout = timeout; }

    int find(const std::string &target) { return find(target.c_str(), target.length()); }

    int find(const char *target, size_t length) {
        if (length == 0) return -1;

        while (int c = timedRead()) {
            if (c == target[0]) {
                if (length == 1) return 1;

                size_t index = 1;
                while (index < length) {
                    if (timedRead() != target[index]) break;
                    index++;
                }
                if (index == length) return 1;
            }
        }
        return -1;
    }

    int findUntil(const std::string &target, const std::string &terminator) {
        return findUntil(target.c_str(), target.length(), terminator.c_str(), terminator.length());
    }

    int findUntil(const char *target, size_t targetLen, const char *terminator, size_t termLen) {
        if (targetLen == 0 || termLen == 0) return -1;

        while (int c = timedRead()) {
            if (c == target[0]) {
                if (targetLen == 1) return 1;

                size_t index = 1;
                while (index < targetLen) {
                    c = timedRead();
                    if (c == terminator[0]) return 0;
                    if (c != target[index]) break;
                    index++;
                }
                if (index == targetLen) return 1;
            }
        }
        return -1;
    }

    long parseInt() {
        bool isNegative = false;
        long value = 0;
        int c;

        while (isspace(c = timedRead()));

        if (c == '-') {
            isNegative = true;
            c = timedRead();
        }

        while (isdigit(c)) {
            value = value * 10 + c - '0';
            c = timedRead();
        }

        if (isNegative) value = -value;
        return value;
    }

    float parseFloat() {
        bool isNegative = false;
        bool isFraction = false;
        long value = 0;
        int c;
        float fraction = 1.0;

        while (isspace(c = timedRead()));

        if (c == '-') {
            isNegative = true;
            c = timedRead();
        }

        while (isdigit(c) || c == '.') {
            if (c == '.') {
                isFraction = true;
            }
            else {
                value = value * 10 + c - '0';
                if (isFraction) fraction *= 0.1;
            }
            c = timedRead();
        }

        if (isNegative) value = -value;
        return value * fraction;
    }

    size_t readBytes(char *buffer, size_t length) {
        size_t index = 0;
        while (index < length) {
            int c = timedRead();
            if (c < 0) break;
            buffer[index++] = static_cast<char>(c);
        }
        return index;
    }

    size_t readBytesUntil(char terminator, char *buffer, size_t length) {
        size_t index = 0;
        while (index < length) {
            int c = timedRead();
            if (c < 0 || c == terminator) break;
            buffer[index++] = static_cast<char>(c);
        }
        return index;
    }

    std::string readString() {
        std::stringstream ss;
        while (int c = timedRead()) {
            if (c < 0) break;
            ss << static_cast<char>(c);
        }
        return ss.str();
    }

    std::string readStringUntil(char terminator) {
        std::stringstream ss;
        while (int c = timedRead()) {
            if (c < 0 || c == terminator) break;
            ss << static_cast<char>(c);
        }
        return ss.str();
    }

private:
    Stream &_stream;
    unsigned long _timeout = 1000;

    int timedRead() {
        unsigned long startMillis = std::chrono::duration_cast<std::chrono::milliseconds>(
                                         std::chrono::system_clock::now().time_since_epoch())
            .count();
        do {
            int c = _stream.read();
            if (c >= 0) return c;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } while (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
                         .count() -
                     startMillis <
                 _timeout);

        return -1;
    }
};

class TestStream: public Stream {
public:
    TestStream(const std::string &data) : _data(data), _pos(0) {}

    int available() override { return static_cast<int>(_data.size()) - _pos; }

    int read() override {
        if (_pos < _data.size()) {
            return _data[_pos++];
        }
        else {
            return -1;
        }
    }

    int peek() override {
        if (_pos < _data.size()) {
            return _data[_pos];
        }
        else {
            return -1;
        }
    }

private:
    std::string _data;
    size_t _pos;
};

int main() {
    TestStream testStream("123.45,67 -89");
    StreamExtension extStream(testStream);

    extStream.setTimeout(1000);
    std::cout << "parseFloat: " << extStream.parseFloat() << std::endl;
    std::cout << "parseInt: " << extStream.parseInt() << std::endl;
    std::cout << "parseInt: " << extStream.parseInt() << std::endl;

    return 0;
}
