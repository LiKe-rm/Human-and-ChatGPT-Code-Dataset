#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <vector>

using namespace std;

const uint8_t NVRAM_ENTRY_RUNTIME = 0x01;
const uint8_t NVRAM_ENTRY_ASCII_NAME = 0x02;
const uint8_t NVRAM_ENTRY_UNICODE_NAME = 0x04;
const uint8_t NVRAM_ENTRY_HARDWARE = 0x08;
const uint8_t NVRAM_ENTRY_BOOT_OPTION = 0x10;
const uint8_t NVRAM_ENTRY_CONSOLE_IN = 0x20;
const uint8_t NVRAM_ENTRY_CONSOLE_OUT = 0x40;
const uint8_t NVRAM_ENTRY_ERROR_RECORD = 0x80;

const uint8_t VSS_TYPE_VARIABLE = 0x01;
const uint8_t VSS_TYPE_TIME = 0x02;
const uint8_t VSS_TYPE_MEMORY = 0x04;

const uint8_t EVSA_TYPE_NONE = 0x00;
const uint8_t EVSA_TYPE_SHA256 = 0x01;
const uint8_t EVSA_TYPE_RSA2048_SHA256 = 0x02;

class UString {
public:
    UString() {}
    UString(const char* str) { set(str); }
    UString(const wchar_t* str) { set(str); }

    void set(const char* str) {
        ustr.clear();
        ustr.resize(strlen(str));
        for (size_t i = 0; i < strlen(str); i++)
            ustr[i] = static_cast<wchar_t>(str[i]);
    }

    void set(const wchar_t* str) {
        ustr.clear();
        ustr.resize(wcslen(str));
        for (size_t i = 0; i < wcslen(str); i++)
            ustr[i] = str[i];
    }

    const wchar_t* c_str() const { return ustr.c_str(); }

    friend ostream& operator<<(ostream& os, const UString& str);

private:
    wstring ustr;
};

ostream& operator<<(ostream& os, const UString& str) {
    os << wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(str.ustr);
    return os;
}

UString byteToHexString(const uint8_t byte) {
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << static_cast<int>(byte);
    UString hexString(ss.str().c_str());
    return hexString;
}

UString nvramAttrToString(const uint32_t attr) {
    vector<UString> attrStrings;

    if (attr & NVRAM_ENTRY_RUNTIME) {
        attrStrings.push_back(UString("NVRAM_ENTRY_RUNTIME"));
    }

    if (attr & NVRAM_ENTRY_ASCII_NAME) {
        attrStrings.push_back(UString("NVRAM_ENTRY_ASCII_NAME"));
    }

    if (attr & NVRAM_ENTRY_UNICODE_NAME) {
        attrStrings.push_back(UString("NVRAM_ENTRY_UNICODE_NAME"));
    }

    if (attr & NVRAM_ENTRY_HARDWARE) {
        attrStrings.push_back(UString("NVRAM_ENTRY_HARDWARE"));
    }

    if (attr & NVRAM_ENTRY_BOOT_OPTION) {
        attrStrings.push_back(UString("NVRAM_ENTRY_BOOT_OPTION"));
    }

    if (attr & NVRAM_ENTRY_CONSOLE_IN) {
        attrStrings.push_back(UString("NVRAM_ENTRY_CONSOLE_IN"));
    }
    if (attr & NVRAM_ENTRY_CONSOLE_OUT) {
    attrStrings.push_back(UString("NVRAM_ENTRY_CONSOLE_OUT"));
    }

    if (attr & NVRAM_ENTRY_ERROR_RECORD) {
        attrStrings.push_back(UString("NVRAM_ENTRY_ERROR_RECORD"));
    }

    UString attrString;
    for (size_t i = 0; i < attrStrings.size(); i++) {
        attrString.set(attrString.c_str() + UString(", ").c_str() + attrStrings[i].c_str());
    }
    return attrString;
}

UString nvramExtAttrToString(const uint32_t extAttr) {
    vector<UString> extAttrStrings;
    if (extAttr & VSS_TYPE_VARIABLE) {
        extAttrStrings.push_back(UString("VSS_TYPE_VARIABLE"));
    }

    if (extAttr & VSS_TYPE_TIME) {
        extAttrStrings.push_back(UString("VSS_TYPE_TIME"));
    }

    if (extAttr & VSS_TYPE_MEMORY) {
        extAttrStrings.push_back(UString("VSS_TYPE_MEMORY"));
    }

    UString extAttrString;
    for (size_t i = 0; i < extAttrStrings.size(); i++) {
        extAttrString.set(extAttrString.c_str() + UString(", ").c_str() + extAttrStrings[i].c_str());
    }
    return extAttrString;
}

UString vssAttrToString(const uint8_t* attr, const size_t attrSize) {
    stringstream ss;
    for (size_t i = 0; i < attrSize; i++) {
        ss << byteToHexString(attr[i]) << " ";
    }

    UString attrString(ss.str().c_str());
    return attrString;
}

UString evsaAttrToString(const uint8_t* attr, const size_t attrSize) {
    stringstream ss;
    if (attr[0] == EVSA_TYPE_SHA256) {
        ss << "SHA-256: ";
        for (size_t i = 1; i < attrSize; i++) {
            ss << byteToHexString(attr[i]);
        }
    } else if (attr[0] == EVSA_TYPE_RSA2048_SHA256) {
        ss << "RSA-2048: ";
        for (size_t i = 1; i < 33; i++) {
            ss << byteToHexString(attr[i]);
        }
        ss << " SHA-256: ";
        for (size_t i = 33; i < attrSize; i++) {
            ss << byteToHexString(attr[i]);
        }
    } else {
        ss << "Unknown EVSA type";
    }

    UString attrString(ss.str().c_str());
    return attrString;
}

UString efiTimeToIso8601(const time_t efiTime) {
    struct tm* timeinfo;
    timeinfo = gmtime(&efiTime);
    stringstream ss;
    ss << setw(4) << setfill('0') << timeinfo->tm_year + 1900
       << "-" << setw(2) << setfill('0') << timeinfo->tm_mon + 1
       << "-" << setw(2) << setfill('0') << timeinfo->tm_mday
       << "T" << setw(2) << setfill('0') << timeinfo->tm_hour
       << ":" << setw(2) << setfill('0') << timeinfo->tm_min
       << ":" << setw(2) << setfill('0') << timeinfo->tm_sec
       << "Z";

    UString isoString(ss.str().c_str());
    return isoString;
}

UString guidToString(const uint8_t* guid) {
    stringstream ss;
    ss << hex << setfill('0') << setw(8) << static_cast<uint32_t>(guid[3]) << setw(8) << static_cast<uint32_t>(guid[2])
       << "-" << setw(4) << static_cast<uint32_t>(guid[1]) << "-"
       << setw(4) << static_cast<uint32_t>(guid[0]) << "-"
       << setw(2) << static_cast<uint32_t>(guid[5]) << setw(2) << static_cast<uint32_t>(guid[4]) << "-"
       << setw(2) << static_cast<uint32_t>(guid[7]) << setw(2) << static_cast<uint32_t>(guid[6])
       << setw(2) << static_cast<uint32_t>(guid[8]) << setw(2) << static_cast<uint32_t>(guid[9])
       << setw(2) << static_cast<uint32_t>(guid[10]) << setw(2) << static_cast<uint32_t>(guid[11]);

    UString guidString(ss.str().c_str());
    return guidString;
}
