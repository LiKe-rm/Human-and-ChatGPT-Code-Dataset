#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

class Date {
public:
    int year, month, day, hour, minute, second;

    Date(int year, int month, int day, int hour, int minute, int second)
        : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}
};

class UtilDateConverter {
public:
    static std::string convertTo(Date source) {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << source.year << "-"
           << std::setw(2) << std::setfill('0') << source.month << "-"
           << std::setw(2) << std::setfill('0') << source.day << " "
           << std::setw(2) << std::setfill('0') << source.hour << ":"
           << std::setw(2) << std::setfill('0') << source.minute << ":"
           << std::setw(2) << std::setfill('0') << source.second;
        return ss.str();
    }

    static Date convertFrom(std::string source) {
        // This method assumes the source string is in "yyyy-mm-dd hh:mm:ss" format
        Date date(std::stoi(source.substr(0, 4)), std::stoi(source.substr(5, 2)), std::stoi(source.substr(8, 2)),
                  std::stoi(source.substr(11, 2)), std::stoi(source.substr(14, 2)), std::stoi(source.substr(17, 2)));
        return date;
    }
};

class BigDecimal {
public:
    std::string value;

    explicit BigDecimal(const std::string& value) : value(value) {}
};

class BigDecimalConverter {
public:
    static std::string convertTo(BigDecimal source) {
        return source.value;
    }

    static BigDecimal convertFrom(std::string source) {
        return BigDecimal(source);
    }
};

template <class T, class R>
T map(T target, R source) {
    // Simplified version of map function
    target = static_cast<T>(source);
    return target;
}

int main() {
    Date date = UtilDateConverter::convertFrom("2023-04-27 12:30:45");
    std::cout << "Converted date: " << date.year << "-" << date.month << "-" << date.day << " "
              << date.hour << ":" << date.minute << ":" << date.second << std::endl;

    std::string dateStr = UtilDateConverter::convertTo(Date(2023, 04, 27, 12, 30, 45));
    std::cout << "Converted string: " << dateStr << std::endl;

    BigDecimal bigDecimal = BigDecimalConverter::convertFrom("123456.789");
    std::cout << "Converted BigDecimal: " << bigDecimal.value << std::endl;

    std::string bigDecimalStr = BigDecimalConverter::convertTo(BigDecimal("123456.789"));
    std::cout << "Converted string: " << bigDecimalStr << std::endl;

    int target = 0;
    double source = 5.5;
    target = map(target, source);
    std::cout << "Mapped value: " << target << std::endl;

    return 0;
}

