#include <iostream>
#include <cstring>
#include <cstdarg>
#include <vector>

// 检查字符是否是空格
bool is_space(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// 获取字符串的长度
size_t str_len(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

// 复制字符串
char* str_copy(char* dest, const char* src) {
    size_t i = 0;
    while ((dest[i] = src[i]) != '\0') {
        i++;
    }
    return dest;
}

// 连接字符串
char* str_concat(char* dest, const char* src) {
    size_t dest_len = str_len(dest);
    str_copy(dest + dest_len, src);
    return dest;
}

// 在字符串中查找子串
const char* str_find(const char* str, const char* substr) {
    if (*substr == '\0') {
        return str;
    }

    for (const char* p = str; *p != '\0'; p++) {
        const char* p1 = p;
        const char* p2 = substr;
        while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2) {
            p1++;
            p2++;
        }

        if (*p2 == '\0') {
            return p;
        }
    }

    return nullptr;
}

// 格式化字符串
int str_format(char* str, size_t size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = std::vsnprintf(str, size, format, args);
    va_end(args);
    return result;
}

// 比较字符串
int str_compare(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

// 比较带通配符的字符串
bool str_compare_wildcard(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return *str == '\0';
    }

    if (*pattern == '?' || *pattern == *str) {
        return str_compare_wildcard(str + 1, pattern + 1);
    }

    if (*pattern == '*') {
        while (*str != '\0') {
            if (str_compare_wildcard(str, pattern + 1)) {
                return true;
            }
            str++;
        }
    }

    return false;
}
