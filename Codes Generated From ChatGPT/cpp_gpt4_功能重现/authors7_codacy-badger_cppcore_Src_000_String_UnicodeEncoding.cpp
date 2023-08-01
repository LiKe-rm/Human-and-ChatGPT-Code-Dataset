#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

typedef uint32_t UTF32;
typedef uint16_t UTF16;
typedef uint8_t UTF8;
typedef uint8_t ASCII;

// 计算ASCII到Unicode字符的个数
size_t ASCII_to_UniChar_Count(const ASCII *ascii) {
    return strlen(reinterpret_cast<const char *>(ascii));
}

// 计算给定UTF-8字符所占字节数
size_t UTF8_Char_Bytes(const UTF8 *utf8) {
    if ((*utf8 & 0x80) == 0) {
        return 1;
    } else if ((*utf8 & 0xE0) == 0xC0) {
        return 2;
    } else if ((*utf8 & 0xF0) == 0xE0) {
        return 3;
    } else if ((*utf8 & 0xF8) == 0xF0) {
        return 4;
    } else {
        throw std::runtime_error("Invalid UTF-8 character");
    }
}

// 从UTF-8字符转换为UTF-32字符
UTF32 UTF8_to_UTF32_Char(const UTF8 *utf8) {
    size_t bytes = UTF8_Char_Bytes(utf8);
    UTF32 utf32 = 0;

    switch (bytes) {
        case 1:
            utf32 = *utf8;
            break;
        case 2:
            utf32 = (utf8[0] & 0x1F) << 6 | (utf8[1] & 0x3F);
            break;
        case 3:
            utf32 = (utf8[0] & 0x0F) << 12 | (utf8[1] & 0x3F) << 6 | (utf8[2] & 0x3F);
            break;
        case 4:
            utf32 = (utf8[0] & 0x07) << 18 | (utf8[1] & 0x3F) << 12 | (utf8[2] & 0x3F) << 6 | (utf8[3] & 0x3F);
            break;
    }

    return utf32;
}

// 转换ASCII到UTF-32
std::vector<UTF32> ASCII_to_UTF32(const ASCII *ascii) {
    size_t count = ASCII_to_UniChar_Count(ascii);
    std::vector<UTF32> utf32(count);

    for (size_t i = 0; i < count; ++i) {
        utf32[i] = static_cast<UTF32>(ascii[i]);
    }

    return utf32;
}

// 转换UTF-8到UTF-32
std::vector<UTF32> UTF8_to_UTF32(const UTF8 *utf8) {
    std::vector<UTF32> utf32;

    while (*utf8 != 0) {
        utf32.push_back(UTF8_to_UTF32_Char(utf8));
        utf8 += UTF8_Char_Bytes(utf8);
    }

    return utf32;
}

// 转换UTF-16到UTF-32
std::vector<UTF32> UTF16_to_UTF32(const UTF16 *utf16) {
    std::vector<UTF32> utf32;

    while (*utf16 != 0) {
        UTF32 ch = *utf16;

        if (ch >= 0xD800 && ch <= 0xDBFF) {
            utf16++;
            ch = ((ch & 0x03FF) << 10) | ((*utf16) & 0x03FF);
            ch += 0x10000;
        }
        utf32.push_back(ch);
        utf16++;
    }

    return utf32;
}

// 转换UTF-32到UTF-8
std::vector<UTF8> UTF32_to_UTF8(const std::vector<UTF32> &utf32) {
    std::vector<UTF8> utf8;

    for (const auto &ch : utf32) {
        if (ch < 0x80) {
            utf8.push_back(static_cast<UTF8>(ch));
        } else if (ch < 0x800) {
            utf8.push_back(0xC0 | (ch >> 6));
            utf8.push_back(0x80 | (ch & 0x3F));
        } else if (ch < 0x10000) {
            utf8.push_back(0xE0 | (ch >> 12));
            utf8.push_back(0x80 | ((ch >> 6) & 0x3F));
            utf8.push_back(0x80 | (ch & 0x3F));
        } else {
            utf8.push_back(0xF0 | (ch >> 18));
            utf8.push_back(0x80 | ((ch >> 12) & 0x3F));
            utf8.push_back(0x80 | ((ch >> 6) & 0x3F));
            utf8.push_back(0x80 | (ch & 0x3F));
        }
    }

    utf8.push_back(0);  // 添加字符串结束符
    return utf8;
}

// 转换UTF-32到UTF-16
std::vector<UTF16> UTF32_to_UTF16(const std::vector<UTF32> &utf32) {
    std::vector<UTF16> utf16;

    for (const auto &ch : utf32) {
        if (ch < 0x10000) {
            utf16.push_back(static_cast<UTF16>(ch));
        } else {
            UTF32 tmp = ch - 0x10000;
            utf16.push_back(0xD800 | (tmp >> 10));
            utf16.push_back(0xDC00 | (tmp & 0x03FF));
        }
    }

    utf16.push_back(0);  // 添加字符串结束符
    return utf16;
}
