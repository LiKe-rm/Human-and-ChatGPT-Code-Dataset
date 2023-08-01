#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <codecvt>
#include <locale>
#include <windows.h>

namespace Utils {
    // 将UTF-8格式的字符串转换为宽字符格式的字符串
    std::wstring UTF8ToWstring(const std::string& utf8str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(utf8str);
    }

    // 将宽字符格式的字符串转换为UTF-8格式的字符串
    std::string WstringToUTF8(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    // 将ANSI格式的字符串转换为宽字符格式的字符串
    std::wstring AnsiToWstring(const std::string& ansiStr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(ansiStr);
    }

    // 将宽字符格式的字符串转换为ANSI格式的字符串
    std::string WstringToAnsi(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    // 格式化字符串，支持可变参数
    std::string FormatString(const char* format, ...) {
        char buffer[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, 1024, format, args);
        va_end(args);
        return std::string(buffer);
    }

    // 从完全限定路径中获取文件名
    std::string StripPath(const std::string& path) {
        size_t pos = path.find_last_of("\\/");
        if (pos != std::string::npos) {
            return path.substr(pos + 1);
        }
        return path;
    }

    // 获取文件的父目录
    std::string GetParent(const std::string& path) {
        size_t pos = path.find_last_of("\\/");
        if (pos != std::string::npos) {
            return path.substr(0, pos);
        }
        return "";
    }

    // 获取当前进程的可执行文件所在目录
    std::string GetExeDirectory() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string path(buffer);
        return GetParent(path);
    }

    // 生成指定长度或随机长度的随机字母数字组合字符串
    std::string RandomANString(size_t length = 16) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        srand((unsigned)time(NULL));
        std::string str;
        for (size_t i = 0; i < length; ++i) {
            str += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        return str;
    }

    // 将字符串中的字符转换为小写
    std::string ToLower(const std::string& str) {
        std::string lowerStr;
        std::locale loc;
        for (auto& c : str) {
            lowerStr += std::tolower(c, loc);
        }
        return lowerStr;
    }

    // 获取系统错误描述
    std::string GetErrorDescription(DWORD error) {
        char* buffer = NULL;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&buffer,
            0, NULL);
        std::string description(buffer);
        LocalFree(buffer);
        return description;
    }

    // 检查指定路径的文件是否存在
    bool FileExists(const std::string& path) {
        DWORD attrib = GetFileAttributesA(path.c_str());
        return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
    }
}
