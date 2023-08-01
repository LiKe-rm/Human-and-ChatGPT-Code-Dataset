#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <codecvt>
#include <locale>

using BYTE = unsigned char;

std::wstring ASCIITruncateTest(const BYTE* byteArray, size_t length) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(reinterpret_cast<const char*>(byteArray), reinterpret_cast<const char*>(byteArray + length));
}

std::wstring ASCIITruncateTest_3byte(const BYTE* byteArray, size_t length) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(reinterpret_cast<const char*>(byteArray), reinterpret_cast<const char*>(byteArray + length));
}

std::vector<BYTE> ReadBytes(const std::string& fileName) {
    std::ifstream inputFile(fileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return std::vector<BYTE>();
    }
    return std::vector<BYTE>((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
}

template<typename Codecvt>
std::wstring WCSConvert(const std::string& input) {
    std::wstring_convert<Codecvt, wchar_t> converter;
    return converter.from_bytes(input);
}

bool ASCII_UTF8_TEST(const std::string& asciiText, const std::string& utf8Text) {
    std::wstring asciiWstr = WCSConvert<std::codecvt_ascii<wchar_t>>(asciiText);
    std::wstring utf8Wstr = WCSConvert<std::codecvt_utf8<wchar_t>>(utf8Text);
    return asciiWstr == utf8Wstr;
}

int main() {
    // Test 1
    BYTE byteArray1[] = {'A', 0xC3, 0xA9}; // 'A' followed by 'é' (U+00E9) in UTF-8
    std::wstring result1 = ASCIITruncateTest(byteArray1, sizeof(byteArray1));
    std::wcout << L"ASCIITruncateTest: " << result1 << std::endl;

    // Test 2
    BYTE byteArray2[] = {'A', 'B', 0xE2, 0x82, 0xAC, 0xE2, 0x82, 0xAC}; // 'AB' followed by '€' (U+20AC) in UTF-8 twice
    std::wstring result2 = ASCIITruncateTest_3byte(byteArray2, sizeof(byteArray2));
    std::wcout << L"ASCIITruncateTest_3byte: " << result2 << std::endl;

    // Test 3
    std::string fileName = "testfile.txt";
    std::vector<BYTE> fileBytes = ReadBytes(fileName);
    std::cout << "ReadBytes: ";
    for (BYTE b : fileBytes) {
        std::cout << static_cast<int>(b) << " ";
    }
    std::cout << std::endl;

    // Test 4
    std::string utf8Text = u8"测试";
    std::wstring utf8Wstr = WCSConvert<std::codecvt_utf8<wchar_t>>(utf8Text);
    std::wcout << L"WCSConvert: " << utf8Wstr << std::endl;

    // Test 5
    std::string asciiText = "Hello";
    std::string utf8TextForComparison = u8"Hello";
    bool conversionTestResult = ASCII_UTF8_TEST(asciiText, utf8TextForComparison);
    std::cout << "ASCII_UTF8_TEST: " << (conversionTestResult ? "true" : "false") << std::endl;
    return 0;
}
