// Color.h - header file for enum Color
#ifndef COLOR_H
#define COLOR_H
enum Color {
    RED,
    BLUE,
    GREEN,
    YELLOW
};
#endif // COLOR_H

// edl_file.edl - EDL file containing the definitions of the function and its parameters
enclave {
    trusted {
        int ChangeColor([in, out] Color& color, [in, out] int& num);
    };
};

// enclave.cpp - the OE application that uses the EDL file to define the function
#include "enclave_t.h"
#include "Color.h"
#include <iostream>

int ChangeColor(Color& color, int& num) {
    std::cout << "Original color: " << color << std::endl;
    color = BLUE; // Change the color to blue
    std::cout << "New color: " << color << std::endl;

    num *= 2; // Double the value of num
    return color; // Return the new color
}

// test.cpp - the test function that initializes the test dataset and tests the function
void test() {
    Color color = RED;
    int num = 5;
    Color expected_color = BLUE;
    int expected_num = 10;

    // Call the OE function with the test dataset
    int result = ChangeColor(color, num);

    // Check the output parameters
    if (color != expected_color) {
        std::cout << "Error: color should be " << expected_color << ", but it is " << color << std::endl;
    }
    if (num != expected_num) {
        std::cout << "Error: num should be " << expected_num << ", but it is " << num << std::endl;
    }

    // Check the return value
    if (result != expected_color) {
        std::cout << "Error: result should be " << expected_color << ", but it is " << result << std::endl;
    }
}

// main.cpp - the main function that calls the test function
int main() {
    test();
    return 0;
}
