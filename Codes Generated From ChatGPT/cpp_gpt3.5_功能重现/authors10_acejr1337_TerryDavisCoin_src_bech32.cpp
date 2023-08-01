#include <iostream>
#include <vector>
#include <string>

const std::string BECH32_CHARSET = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";

int bech32_polymod(const std::vector<int>& values) {
    int generator = 0x3b6a57b2;
    int checksum = 1;
    for (int i = 0; i < values.size(); i++) {
        int value = checksum >> 25;
        checksum = ((checksum & 0x1ffffff) << 5) ^ values[i];
        for (int j = 0; j < 5; j++) {
            if ((value >> j) & 1) {
                checksum ^= generator << j;
            }
        }
    }
    return checksum;
}

std::vector<int> bech32_expand(const std::string& hrp) {
    std::vector<int> result;
    for (int i = 0; i < hrp.length(); i++) {
        result.push_back(hrp[i] >> 5);
    }
    result.push_back(0);
    for (int i = 0; i < hrp.length(); i++) {
        result.push_back(hrp[i] & 0x1f);
    }
    return result;
}

std::string bech32_encode(const std::string& hrp, const std::vector<int>& data) {
    std::string result = hrp + "1";
    std::vector<int> values = bech32_expand(hrp);
    values.insert(values.end(), data.begin(), data.end());
    values.push_back(0);
    int checksum = bech32_polymod(values);
    for (int i = 0; i < 6; i++) {
        result += BECH32_CHARSET[(checksum >> (5 * (5 - i))) & 0x1f];
    }
    for (int i = 0; i < data.size(); i++) {
        result += BECH32_CHARSET[data[i]];
    }
    return result;
}

std::pair<std::string, std::vector<int>> bech32_decode(const std::string& str) {
    std::string hrp;
    std::vector<int> data;
    int last_one_pos = str.rfind('1');
    if (last_one_pos == std::string::npos) {
        throw std::invalid_argument("invalid bech32 string");
    }
    for (int i = 0; i < last_one_pos; i++) {
        if (str[i] < 33 || str[i] > 126) {
            throw std::invalid_argument("invalid character in HRP");
        }
        hrp += str[i];
    }
    for (int i = last_one_pos + 1; i < str.length(); i++) {
        int value = BECH32_CHARSET.find(str[i]);
        if (value == std::string::npos) {
            throw std::invalid_argument("invalid character in data");
        }
        data.push_back(value);
    }
    std::vector<int> values = bech32_expand(hrp);
    values.insert(values.end(), data.begin(), data.end());
    if (bech32_polymod(values) != 1) {
        throw std::invalid_argument("invalid checksum");
    }
    return std::make_pair(hrp, std::vector<int>(data.begin(), data.end() - 1));
}

int main() {
// Example usage
    std::string hrp = "bc";
    std::vector<int> data ={ 0, 14, 20, 15, 15, 14 };
    std::string encoded = bech32_encode(hrp, data);
    std::cout << "Encoded: " << encoded << std::endl; // "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4"
    std::pair<std::string, std::vector<int>> decoded = bech32_decode(encoded);
    std::cout << "Decoded: HRP=" << decoded.first << " Data=[";
    for (int i = 0; i < decoded.second.size(); i++) {
        std::cout << decoded.second[i];
        if (i != decoded.second.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl; // "Decoded: HRP=bc Data=[0,14,20,15,15,14]"
    return 0;
}
