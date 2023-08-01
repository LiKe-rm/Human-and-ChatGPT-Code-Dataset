#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <string>

class SinhVien {
public:
    SinhVien();
    SinhVien(std::string id, std::string name, float score);

    void setId(std::string id);
    void setName(std::string name);
    void setScore(float score);

    std::string getId() const;
    std::string getName() const;
    float getScore() const;

private:
    std::string id;
    std::string name;
    float score;
};

#endif // SINHVIEN_H

#ifndef MENU_H
#define MENU_H

void showMenu();
void menu();

#endif // MENU_H

#ifndef PROCESS_H
#define PROCESS_H

#include "SinhVien.h"
#include <vector>

void addStudent(std::vector<SinhVien> &students);
void editStudent(std::vector<SinhVien> &students);
void deleteStudent(std::vector<SinhVien> &students);
void findStudent(std::vector<SinhVien> &students);
void sortStudents(std::vector<SinhVien> &students);
void exportStudents(std::vector<SinhVien> &students);
void statistics(std::vector<SinhVien> &students);
void readFile(std::vector<SinhVien> &students, const std::string &filename);
void writeFile(std::vector<SinhVien> &students, const std::string &filename);

#endif // PROCESS_H

#include "SinhVien.h"

SinhVien::SinhVien() {}

SinhVien::SinhVien(std::string id, std::string name, float score)
    : id(id), name(name), score(score) {}

void SinhVien::setId(std::string id) {
    this->id = id;
}

void SinhVien::setName(std::string name) {
    this->name = name;
}

void SinhVien::setScore(float score) {
    this->score = score;
}

std::string SinhVien::getId() const {
    return id;
}

std::string SinhVien::getName() const {
    return name;
}

float SinhVien::getScore() const {
    return score;
}

#include "Menu.h"
#include "Process.h"
#include <iostream>
#include <vector>
#include "SinhVien.h"

using namespace std;

void showMenu() {
    cout << "1. 添加学生" << endl;
    cout << "2. 编辑学生" << endl;
    cout << "3. 删除学生" << endl;
    cout << "4. 查找学生" << endl;
    cout << "5. 排序学生" << endl;
    cout << "6. 输出学生信息" << endl;
    cout << "7. 统计学生信息" << endl;
    cout << "8. 退出程序" << endl;
}

void menu() {
    vector<SinhVien> students;
    int choice;

    while (true) {
        showMenu();
        cout << "请选择操作: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                editStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                findStudent(students);
                break;
            case 5:
                sortStudents(students);
                break;
            case 6:
                exportStudents(students);
                break;
            case 7:
                statistics(students);
                break;
            case 8:
                cout << "谢谢使用！" << endl;
                return;
            default:
                cout << "无效的选择，请重试！" << endl;
                break;
        }
    }
}
