#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "UEFIFind.h" // UEFIFind 类的头文件

using namespace std;

int main(int argc, char* argv[]) {
    // 检查命令行参数数量是否正确
    if (argc != 4 && argc != 5) {
        cout << "Usage: " << argv[0] << " <UEFI image file> <patterns file> <result type> [pattern]" << endl;
        return 1;
    }

    // 解析命令行参数
    string uefiImageFile = argv[1];
    string patternsFile = argv[2];
    string resultType = argv[3];
    string pattern;

    if (argc == 5) {
        pattern = argv[4];
    }

    // 读取 GUID 数据库文件
    vector<string> guids;
    ifstream guidsFile("guids.csv");

    if (guidsFile.is_open()) {
        string line;
        while (getline(guidsFile, line)) {
            guids.push_back(line);
        }
        guidsFile.close();
    } else {
        cout << "Error: Could not open guids.csv" << endl;
        return 2;
    }

    // 执行搜索操作
    UEFIFind w(uefiImageFile, guids); // 初始化 UEFIFind 对象
    int count = 0;

    if (argc == 5) { // 单独模式搜索
        count = w.search(pattern, resultType);
        if (count == 0) {
            cout << "Error: Could not find pattern " << pattern << endl;
            return 3;
        }
    } else { // 多模式搜索
        ifstream patterns(patternsFile);
        if (patterns.is_open()) {
            string line;
            while (getline(patterns, line)) {
                count += w.search(line, resultType);
            }
            patterns.close();
        } else {
            cout << "Error: Could not open patterns file" << endl;
            return 4;
        }
        if (count == 0) {
            cout << "Error: Could not find any patterns" << endl;
            return 5;
        }
    }

    // 打印结果并退出
    cout << "Found " << count << " results" << endl;
    return 0;
}
