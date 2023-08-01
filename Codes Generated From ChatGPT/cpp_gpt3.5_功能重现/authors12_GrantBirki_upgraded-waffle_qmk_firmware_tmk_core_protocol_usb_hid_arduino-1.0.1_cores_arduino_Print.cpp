#ifndef _PRINT_H_
#define _PRINT_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <Arduino.h>

class Print {
public:
    Print() {}
    virtual ~Print() {}

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
        if (str == NULL) return 0;
        return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);

    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);

    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
    size_t println(void);

private:
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);

};

#endif // _PRINT_H_

#include "Print.h"

size_t Print::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        n += write(*buffer++);
    }
    return n;
}

size_t Print::print(const char str[]) {
    return write(str);
}

size_t Print::print(char c) {
    return write((uint8_t)c);
}

size_t Print::print(unsigned char b, int base) {
    return print((unsigned long)b, base);
}

size_t Print::print(int n, int base) {
    if (base == 0) {
        return write((uint8_t)n);
    } else if (base == 10) {
        if (n < 0) {
            int t = print('-');
            n = -n;
            return printNumber(n, 10) + t;
        }
        return printNumber(n, 10);
    } else {
        return printNumber(n, base);
    }
}

size_t Print::print(unsigned int n, int base) {
    return print((unsigned long)n, base);
}

size_t Print::print(long n, int base) {
    if (base == 0) {
        return write((uint8_t)n);
    } else if (base == 10) {
        if (n < 0) {
            int t = print('-');
            n = -n;
            return printNumber(n, 10) + t;
        }
        return printNumber(n, 10);
    } else {
        return printNumber(n, base);
    }
}

size_t Print::print(unsigned long n, int base) {
    if (base == 0) {
        return write((uint8_t)n);
    } else {
        return printNumber(n, base);
    }
}

size_t Print::print(double n, int digits) {
    return printFloat(n, digits);
}

size_t Print::println(const char str[]) {
    size_t n = print(str);
    n += println();
    return n;
}

size_t Print::println(char c) {
    size_t n = print(c);
    n += println();
    return n;
}

size_t Print::println(unsigned char b, int base) {
    size_t n = print(b, base);
    n += println();
    return n;
}

size_t Print::println(int num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(unsigned int num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(long num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(unsigned long num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(double num, int digits) {
    size_t n = print(num, digits);
    n += println();
    return n;
}

size_t Print::println(void) {
    return write('\r') + write('\n');
}

size_t Print::printNumber(unsigned long n, uint8_t base) {
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // Prevent crash if called with base == 1
    if (base < 2) base = 10;

    do {
        char c = n % base;
        n /= base;

        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while (n);

    return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) {
    size_t n = 0;

    if (isnan(number)) return print("nan");
    if (isinf(number)) return print("inf");
    if (number > 4294967040.0) return print("ovf");
    if (number < -4294967040.0) return print("ovf");

    if (number < 0.0) {
        n += print('-');
        number = -number;
    }

    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i) {
        rounding /= 10.0;
    }

    number += rounding;

    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;
    n += print(int_part);

    if (digits > 0) {
        n += print(".");
    }

    while (digits-- > 0) {
        remainder *= 10.0;
        unsigned int toPrint = (unsigned int)(remainder);
        n += print(toPrint);
        remainder -= toPrint;
    }

    return n;
}
