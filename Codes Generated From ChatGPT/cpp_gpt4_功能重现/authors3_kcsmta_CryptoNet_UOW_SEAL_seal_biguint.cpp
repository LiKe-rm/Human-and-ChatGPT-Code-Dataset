#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BigInteger {
public:
    BigInteger() : sign(true), number("0") {}

    BigInteger(const std::string &str) {
        if (str[0] == '-') {
            sign = false;
            number = str.substr(1);
        } else {
            sign = true;
            number = str;
        }
    }

    BigInteger(const BigInteger &other) : sign(other.sign), number(other.number) {}

    BigInteger &operator=(const BigInteger &other) {
        if (this == &other) {
            return *this;
        }

        sign = other.sign;
        number = other.number;

        return *this;
    }

    BigInteger operator+(const BigInteger &other) const {
        if (sign == other.sign) {
            return BigInteger(sign, add(number, other.number));
        }

        if (isGreater(number, other.number)) {
            return BigInteger(sign, subtract(number, other.number));
        } else {
            return BigInteger(!sign, subtract(other.number, number));
        }
    }

    BigInteger operator-(const BigInteger &other) const {
        if (sign != other.sign) {
            return BigInteger(sign, add(number, other.number));
        }

        if (isGreater(number, other.number)) {
            return BigInteger(sign, subtract(number, other.number));
        } else {
            return BigInteger(!sign, subtract(other.number, number));
        }
    }

    BigInteger operator*(const BigInteger &other) const {
        return BigInteger(sign == other.sign, multiply(number, other.number));
    }

    BigInteger operator/(const BigInteger &other) const {
        return BigInteger(sign == other.sign, divide(number, other.number));
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInteger &bigInt) {
        if (!bigInt.sign) {
            out << "-";
        }
        out << bigInt.number;
        return out;
    }

private:
    BigInteger(bool sign, const std::string &number) : sign(sign), number(number) {}

    static std::string add(const std::string &num1, const std::string &num2) {
        std::string result;
        int carry = 0;
        int maxLength = std::max(num1.length(), num2.length());

        for (int i = 0; i < maxLength; i++) {
            int digit1 = i < num1.length() ? num1[num1.length() - i - 1] - '0' : 0;
            int digit2 = i < num2.length() ? num2[num2.length() - i - 1] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        if (carry) {
            result.push_back(carry + '0');
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    static std::string subtract(const std::string &num1, const std::string &num2) {
        std::string result;
        int borrow = 0;

        for (int i = 0; i < num1.length(); i++) {
            int digit1 = num1[num1.length() - i - 1] - '0';
            int digit2 = i < num2.length() ? num2[num2.length() - i - 1] - '0' : 0;
            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(diff + '0');
        }

        while (result.length() > 1 && result.back() == '0') {
            result.pop_back();
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    static std::string multiply(const std::string &num1, const std::string &num2) {
        std::string result(num1.length() + num2.length(), '0');

        for (int i = 0; i < num1.length(); i++) {
            int carry = 0;
            for (int j = 0; j < num2.length(); j++) {
                int prod = (num1[num1.length() - i - 1] - '0') * (num2[num2.length() - j - 1] - '0') + (result[result.length() - i - j - 1] - '0') + carry;
                carry = prod / 10;
                result[result.length() - i - j - 1] = (prod % 10) + '0';
            }

            if (carry) {
                result[result.length() - i - num2.length() - 1] = carry + '0';
            }
        }

        while (result.length() > 1 && result[0] == '0') {
            result.erase(result.begin());
        }

        return result;
    }

    static std::string divide(const std::string &num1, const std::string &num2) {
        if (isGreater(num2, num1)) {
            return "0";
        }

        if (num2 == "1") {
            return num1;
        }

        std::string result;
        std::string current;
        int idx = 0;

        while (idx < num1.length()) {
            current += num1[idx++];

            int quotient = 0;
            while (!isGreater(num2, current)) {
                current = subtract(current, num2);
                quotient++;
            }

            result.push_back(quotient + '0');
        }

        while (result.length() > 1 && result[0] == '0') {
            result.erase(result.begin());
        }

        return result;
    }

    static bool isGreater(const std::string &num1, const std::string &num2) {
        if (num1.length() != num2.length()) {
            return num1.length() > num2.length();
        }

        for (int i = 0; i < num1.length(); i++) {
            if (num1[i] != num2[i]) {
                return num1[i] > num2[i];
            }
        }

        return false;
    }

    bool sign;
    std::string number;

};
