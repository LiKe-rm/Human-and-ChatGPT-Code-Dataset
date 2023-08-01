#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

// Macro definitions to enable/disable program blocks
#define PROGRAM_BLOCK_1 1
#define PROGRAM_BLOCK_2 0
#define PROGRAM_BLOCK_2_EXT 0

#if PROGRAM_BLOCK_1
void programBlock1() {
    std::vector<std::string> names;
    std::string input;
    std::cout << "Enter names separated by spaces: ";
    std::getline(std::cin, input);
    std::istringstream iss(input);

    while (iss >> input) {
        names.push_back(input);
    }

    int choice;
    std::cout << "Select a name by entering its index (0 to " << names.size() - 1 << "): ";
    std::cin >> choice;

    if (choice >= 0 && choice < names.size()) {
        std::cout << "You selected: " << names[choice] << std::endl;
    } else {
        std::cout << "Invalid index!" << std::endl;
    }
}
#endif

#if PROGRAM_BLOCK_2 || PROGRAM_BLOCK_2_EXT
bool floatValidation(const std::string &input) {
    float value;
    std::istringstream iss(input);
    return !(iss >> value).fail();
}

bool integerValidation(const std::string &input) {
    int value;
    std::istringstream iss(input);
    return !(iss >> value).fail();
}

float StringToFloat(const std::string &input) {
    return std::stof(input);
}

int StringToInteger(const std::string &input) {
    return std::stoi(input);
}

#if PROGRAM_BLOCK_2_EXT
std::string StringGenerator() {
    std::string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 10; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}
#endif

void programBlock2() {
    std::string priceStr, quantityStr;
    float price;
    int quantity;

    std::cout << "Enter the price: ";
    std::getline(std::cin, priceStr);

    while (!floatValidation(priceStr)) {
        std::cout << "Invalid input! Please enter a valid price: ";
        std::getline(std::cin, priceStr);
    }

    std::cout << "Enter the quantity: ";
    std::getline(std::cin, quantityStr);

    while (!integerValidation(quantityStr)) {
        std::cout << "Invalid input! Please enter a valid quantity: ";
        std::getline(std::cin, quantityStr);
    }

    price = StringToFloat(priceStr);
    quantity = StringToInteger(quantityStr);

#if PROGRAM_BLOCK_2_EXT
    std::ofstream logFile("log.txt", std::ios_base::app);
    srand(time(NULL));

    for (int i = 0; i < 10; ++i) {
        price = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        quantity = rand() % 100;

        if (logFile.is_open()) {
            logFile << "Random Price: " << price << ", Random Quantity: " << quantity << ", String: " << StringGenerator() << std::endl;
        }
    }
    logFile.close();
#endif

    std::cout << "Price: " << price << ", Quantity: " << quantity << std::endl;
}
#endif

int main() {
#if PROGRAM_BLOCK_1
    programBlock1();
#endif

#if PROGRAM_BLOCK_2 || PROGRAM_BLOCK_2_EXT
    programBlock2();
#endif
}
