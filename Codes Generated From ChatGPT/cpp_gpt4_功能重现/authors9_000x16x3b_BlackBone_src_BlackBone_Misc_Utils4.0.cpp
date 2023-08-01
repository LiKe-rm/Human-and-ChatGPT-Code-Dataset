#include <algorithm>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <locale>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

namespace Utils {

std::wstring UTF8ToWstring(const std::string& utf8) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
  return converter.from_bytes(utf8);
}

std::string WstringToUTF8(const std::wstring& wstr) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
  return converter.to_bytes(wstr);
}

std::wstring AnsiToWstring(const std::string& ansi) {
  std::wstring result;
  int length = MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, nullptr, 0);
  if (length > 0) {
    result.resize(length - 1);
    MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), -1, &result[0], length);
  }
  return result;
}

std::string WstringToAnsi(const std::wstring& wstr) {
  std::string result;
  int length = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
  if (length > 0) {
    result.resize(length - 1);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &result[0], length, nullptr, nullptr);
  }
  return result;
}

template <typename... Args>
std::string FormatString(const std::string& format, Args... args) {
  size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
  std::vector<char> buf(size);
  snprintf(buf.data(), size, format.c_str(), args...);
  return std::string(buf.data(), buf.data() + size - 1);
}

std::string StripPath(const std::string& fullPath) {
  std::filesystem::path path(fullPath);
  return path.filename().string();
}

std::string GetParent(const std::string& path) {
  std::filesystem::path p(path);
  return p.parent_path().string();
}

std::string GetExeDirectory() {
  wchar_t buffer[MAX_PATH];
  GetModuleFileNameW(NULL, buffer, MAX_PATH);
  std::filesystem::path exePath(buffer);
  return exePath.parent_path().string();
}

std::string RandomANString(size_t length) {
  std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, chars.size() - 1);

  std::string result;
  result.reserve(length);
  for (size_t i = 0; i < length; ++i) {
    result += chars[dis(gen)];
  }
  return result;
}

std::string ToLower(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string GetErrorDescription(DWORD errorCode) {
  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

std::string message(messageBuffer, size);
LocalFree(messageBuffer);
return message;
}

bool FileExists(const std::string& path) {
std::ifstream infile(path);
return infile.good();
}

} // namespace Utils
