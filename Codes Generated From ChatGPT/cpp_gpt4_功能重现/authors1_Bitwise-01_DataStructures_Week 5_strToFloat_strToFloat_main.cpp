#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>

bool isFormed(const std::string &str) {
    bool decimal_point = false;
    int index = 0;

    if (str[0] == '-' || str[0] == '+') {
        index = 1;
    }

    for (; index < str.size(); ++index) {
        if (std::isdigit(str[index])) {
            continue;
        } else if (str[index] == '.' && !decimal_point) {
            decimal_point = true;
        } else {
            return false;
        }
    }

    return true;
}

float strToFloat(const std::string &str) {
    float result;
    std::stringstream ss(str);
    ss >> result;
    return result;
}

int main() {
    std::string inputfile;
    std::cout << "请输入文本文件路径：";
    std::cin >> inputfile;

    std::ifstream infile(inputfile);
    if (!infile.is_open()) {
        std::cerr << "无法打开输入文件！\n";
        return 1;
    }

    std::string outputfile = "output.txt";
    std::ofstream outfile(outputfile);
    if (!outfile.is_open()) {
        std::cerr << "无法打开输出文件！\n";
        return 1;
    }

    std::string str;
    while (infile >> str) {
        if (isFormed(str)) {
            float num = strToFloat(str);
            std::cout << std::setw(15) << str << " -> " << num << std::endl;
            outfile << std::setw(15) << str << " -> " << num << std::endl;
        } else {
            std::cout << std::setw(15) << str << " -> 非法字符串" << std::endl;
            outfile << std::setw(15) << str << " -> 非法字符串" << std::endl;
        }
    }

    infile.close();
    outfile.close();

    return 0;
}
