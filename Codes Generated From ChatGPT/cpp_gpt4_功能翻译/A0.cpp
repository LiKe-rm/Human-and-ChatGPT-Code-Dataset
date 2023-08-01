#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <cstring>

class Base64Variant {
public:
    Base64Variant(const Base64Variant& variant, const std::string& name) : _name(name) {
        _base64Chars = variant._base64Chars;
        _decodeTable = variant._decodeTable;
        _paddingEnabled = variant._paddingEnabled;
        _paddingChar = variant._paddingChar;
    }

    Base64Variant(const std::string& name, const std::string& base64Chars, bool paddingEnabled, char paddingChar)
        : _name(name), _paddingEnabled(paddingEnabled), _paddingChar(paddingChar) {
        if (base64Chars.length() != 64) {
            throw std::invalid_argument("Base64 alphabet length must be exactly 64.");
        }

        _base64Chars = base64Chars;
        _decodeTable.fill(-1);

        for (size_t i = 0; i < base64Chars.length(); ++i) {
            _decodeTable[static_cast<unsigned char>(base64Chars[i])] = static_cast<int>(i);
        }

        if (paddingEnabled) {
            _decodeTable[static_cast<unsigned char>(paddingChar)] = -2;
        }
    }

    std::string encode(const std::vector<unsigned char>& data, bool useQuotes) const {
        size_t length = data.size();
        std::ostringstream ss;
        if (useQuotes) {
            ss << '\"';
        }

        size_t fullBlocks = length / 3;
        size_t remainder = length % 3;

        for (size_t i = 0; i < fullBlocks; ++i) {
            encodeBlock(&data[i * 3], 3, ss);
        }

        if (remainder > 0) {
            encodeBlock(&data[fullBlocks * 3], remainder, ss);
        }

        if (useQuotes) {
            ss << '\"';
        }

        return ss.str();
    }

    bool operator==(const Base64Variant& other) const {
        return _name == other._name;
    }

    bool operator!=(const Base64Variant& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Base64Variant& base64Variant) {
        os << base64Variant._name;
        return os;
    }

private:
    std::string _name;
    std::string _base64Chars;
    std::array<int, 128> _decodeTable;
    bool _paddingEnabled;
    char _paddingChar;

    void encodeBlock(const unsigned char* data, size_t size, std::ostringstream& ss) const {
        uint32_t buffer = (static_cast<uint32_t>(data[0]) << 16);
        if (size > 1) {
            buffer |= (static_cast<uint32_t>(data[1]) << 8);
            if (size > 2) {
                buffer |= data[2];
            }
        }

        ss << _base64Chars[(buffer >> 18) & 0x3F];
        ss << _base64Chars[(buffer >> 12) & 0x3F];

        if (size > 1) {
            ss << _base64Chars[(buffer >> 6) & 0x3F];
            if (size > 2) {
                ss << _base64Chars[buffer & 0x3F];
            } else if (_paddingEnabled) { 
                ss << _paddingChar;
            }
        } else if (_paddingEnabled) {
            ss << _paddingChar << _paddingChar;
        }
    }
};

// Sample usage
int main() {
    Base64Variant base64Variant("Base64", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", true, '=');
    std::vector<unsigned char> data = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    std::string encodedData = base64Variant.encode(data, true);
    std::cout << "Encoded data: " << encodedData << std::endl;

    return 0;
}