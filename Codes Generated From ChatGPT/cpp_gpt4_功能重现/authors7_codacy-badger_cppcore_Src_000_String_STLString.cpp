#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <cstring>

namespace core {
    // 1. Format string output function
    template<typename... Args>
    std::string format(const std::string &format_str, Args... args) {
        constexpr size_t buf_size = 1024;
        char buf[buf_size];
        snprintf(buf, buf_size, format_str.c_str(), args...);
        return std::string(buf);
    }

    // 2. Replace all occurrences of the target string with the given string
    std::string replace_all(const std::string &str, const std::string &from, const std::string &to) {
        std::string result = str;
        size_t start_pos = 0;
        while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
            result.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return result;
    }

    // 3. Convert all characters in the string to lowercase
    std::string to_lowercase(const std::string &str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    // 4. Convert all characters in the string to uppercase
    std::string to_uppercase(const std::string &str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    // 5. Convert all characters in the given string to lowercase in-place
    void to_lowercase_inplace(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    // 6. Convert all characters in the given string to uppercase in-place
    void to_uppercase_inplace(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    // 7. Remove leading and trailing whitespace characters from the string
    std::string trim(const std::string &str) {
        std::string result = str;
        result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), result.end());
        return result;
    }

    // 8. Remove leading whitespace characters from the string
    std::string ltrim(const std::string &str) {
        std::string result = str;
        result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        return result;
    }

    // 9. Remove trailing whitespace characters from the string
    std::string rtrim(const std::string &str) {
        std::string result = str;
        result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), result.end());
        return result;
    }

    // 10. Split the string by the given delimiter and return the substring at the specified offset
    std::string split_offset(const std::string &str, const std::string &delimiter, size_t offset) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);
        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        tokens.push_back(str.substr(start, end));

        if (offset < tokens.size()) {
            return tokens[offset];
        } else {
            return "";
        }
    }

    // 11. Split the string by the given delimiter and store the substrings in the specified structure
    template <typename Container>
    void split(const std::string &str, const std::string &delimiter, Container &container) {
        size_t start = 0;
        size_t end = str.find(delimiter);
        while (end != std::string::npos) {
            container.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        container.push_back(str.substr(start, end));
    }

    // 12. Swap the values of two strings
    void swap_strings(std::string &str1, std::string &str2) {
        std::swap(str1, str2);
    }

    // 13. Find the first occurrence of the delimiter and assign the substrings on both sides of the delimiter to the specified string structure
    bool split_first(const std::string &str, const std::string &delimiter, std::string &left, std::string &right) {
        size_t pos = str.find(delimiter);
        if (pos != std::string::npos) {
            left = str.substr(0, pos);
            right = str.substr(pos + delimiter.length());
            return true;
        }
        return false;
    }

    // 14. Return the substring composed of the specified number of characters at the end of the string
    std::string last_n_chars(const std::string &str, size_t n) {
        if (n >= str.size()) {
            return str;
        }
        return str.substr(str.size() - n);
    }

    // 15. Compare the given string with a match pattern (using wildcard matching) for consistency
    bool wildcard_match(const char *str, const char *pattern) {
        if (*pattern == '\0') {
            return *str == '\0';
        }

        if (*pattern == '*') {
            while (*(pattern + 1) == '*') {
                ++pattern;
            }

            if (*(pattern + 1) == '\0') {
                return true;
            }

            while (*str != '\0') {
                if (wildcard_match(str, pattern + 1)) {
                    return true;
                }
                ++str;
            }

            return false;
        }

        return (*str == *pattern || (*pattern == '?' && *str != '\0')) && wildcard_match(str + 1, pattern + 1);
    }

    bool wildcard_match(const std::string &str, const std::string &pattern) {
        return wildcard_match(str.c_str(), pattern.c_str());
    }
}// namespace core
