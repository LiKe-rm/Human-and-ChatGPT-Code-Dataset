#include "Process.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

void addStudent(vector<SinhVien> &students) {
    string id, name;
    float score;

    cout << "输入学生ID: ";
    cin >> id;
    cout << "输入学生姓名: ";
    cin >> name;
    cout << "输入学生分数: ";
    cin >> score;

    students.push_back(SinhVien(id, name, score));
}

void editStudent(vector<SinhVien> &students) {
    string id;
    cout << "输入要编辑的学生ID: ";
    cin >> id;

    for (SinhVien &student : students) {
        if (student.getId() == id) {
            string newName;
            float newScore;
            cout << "输入新的学生姓名: ";
            cin >> newName;
            cout << "输入新的学生分数: ";
            cin >> newScore;

            student.setName(newName);
            student.setScore(newScore);
            cout << "学生信息已更新!" << endl;
            return;
        }
    }
    cout << "找不到该学生!" << endl;
}

void deleteStudent(vector<SinhVien> &students) {
    string id;
    cout << "输入要删除的学生ID: ";
    cin >> id;

    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getId() == id) {
            students.erase(students.begin() + i);
            cout << "学生已删除!" << endl;
            return;
        }
    }
    cout << "找不到该学生!" << endl;
}

void findStudent(vector<SinhVien> &students) {
    string id;
    cout << "输入要查找的学生ID: ";
    cin >> id;

    for (const SinhVien &student : students) {
        if (student.getId() == id) {
            cout << "学生ID: " << student.getId() << ", 姓名: " << student.getName() << ", 分数: " << student.getScore() << endl;
            return;
        }
    }
    cout << "找不到该学生!" << endl;
}

bool compareStudents(const SinhVien &a, const SinhVien &b) {
    return a.getScore() > b.getScore();
}

void sortStudents(vector<SinhVien> &students) {
    sort(students.begin(), students.end(), compareStudents);
    cout << "学生已按分数降序排列!" << endl;
}

void exportStudents(vector<SinhVien> &students) {
    for (const SinhVien &student : students) {
        cout << "学生ID: " << student.getId() << ", 姓名: " << student.getName() << ", 分数: " << student.getScore() << endl;
    }
}

void statistics(vector<SinhVien> &students) {
    // 学生统计功能，你可以添加你需要的统计功能
}

void readFile(vector<SinhVien> &students, const string &filename) {
    lock_guard<mutex> lock(mtx);

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    string id, name;
    float score;
    while (inputFile >> id >> name >> score) {
        students.push_back(SinhVien(id, name, score));
    }

    inputFile.close();
    cout << "学生数据已从文件导入!" << endl;
}

void writeFile(vector<SinhVien> &students, const string &filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    for (const SinhVien &student : students) {
        outputFile << student.getId() << " " << student.getName() << " " << student.getScore() << endl;
    }

    outputFile.close();
    cout << "学生数据已导出到文件!" << endl;
}

void multiThreadReadFiles(vector<SinhVien> &students, const vector<string> &filenames) {
    vector<thread> threads;
    for (const string &filename : filenames) {
        threads.push_back(thread(readFile, ref(students), ref(filename)));
    }

    for (thread &t : threads) {
        t.join();
    }
}

int main() {
    // 从文件读取学生数据
    vector<string> filenames = {"students1.txt", "students2.txt", "students3.txt"};
    vector<SinhVien> students;
    multiThreadReadFiles(students, filenames);

    // 显示菜单并处理操作
    menu();

    // 将学生数据写入文件
    writeFile(students, "output.txt");

    return 0;
}