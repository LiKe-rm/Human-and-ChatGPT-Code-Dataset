#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class SinhVien {
public:
    string id;
    string name;
    int age;
    string gender;
};

class Menu {
public:
    void displayMainMenu();
    void displaySubMenu1();
    void displaySubMenu2();
    void displaySubMenu3();
};

class Process {
public:
    void addStudent(SinhVien& student);
    void modifyStudent(const string& id);
    void deleteStudent(const string& id);
    void importFromFile(const string& fileName);
    void exportToFile(const string& fileName);
    void search(int option, const string& keyword);
    void sort(int option);
    void displaySummary();
private:
    vector<SinhVien> students;
};

void Menu::displayMainMenu() {
    cout << "======================================" << endl;
    cout << "学生信息管理系统" << endl;
    cout << "1. 添加、修改或删除学生信息" << endl;
    cout << "2. 查找学生信息" << endl;
    cout << "3. 排序学生信息" << endl;
    cout << "4. 导出学生信息到文件" << endl;
    cout << "5. 显示学生信息总结" << endl;
    cout << "6. 退出程序" << endl;
    cout << "======================================" << endl;
    cout << "请选择操作（1-6）：";
}

void Menu::displaySubMenu1() {
    cout << "======================================" << endl;
    cout << "1. 添加学生信息" << endl;
    cout << "2. 修改学生信息" << endl;
    cout << "3. 删除学生信息" << endl;
    cout << "4. 从文件导入学生信息" << endl;
    cout << "5. 返回上一级菜单" << endl;
    cout << "======================================" << endl;
    cout << "请选择操作（1-5）：";
}

void Menu::displaySubMenu2() {
    cout << "======================================" << endl;
    cout << "1. 按考号查找" << endl;
    cout << "2. 按姓名查找" << endl;
    cout << "3. 返回上一级菜单" << endl;
    cout << "======================================" << endl;
    cout << "请选择操作（1-3）：";
}

void Menu::displaySubMenu3() {
    cout << "======================================" << endl;
    cout << "1. 按考号排序" << endl;
    cout << "2. 按姓名排序" << endl;
    cout << "3. 返回上一级菜单" << endl;
    cout << "======================================" << endl;
    cout << "请选择操作（1-3）：";
}

void Process::addStudent(SinhVien& student) {
    students.push_back(student);
}

void Process::modifyStudent(const string& id) {
    for (SinhVien& student : students) {
        if (student.id == id) {
            cout << "请输入新的姓名：";
            cin >> student.name;
            cout << "请输入新的年龄：";
            cin >> student.age;
            cout << "请输入新的性别：";
            cin >> student.gender;
            return;
        }
    }
    cout << "未找到该考号的学生信息。" << endl;
}

void Process::deleteStudent(const string& id) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            cout << "已删除该考号的学生信息。" << endl;
            return;
        }
    }
    cout << "未找到该考号的学生信息。" << endl;
}

void Process::importFromFile(const string& fileName) {
    ifstream inputFile(fileName);

    if (!inputFile) {
        cout << "无法打开文件：" << fileName << endl;
        return;
    }

    SinhVien student;
    while (inputFile >> student.id >> student.name >> student.age >> student.gender) {
        students.push_back(student);
    }
    inputFile.close();
}

void Process::exportToFile(const string& fileName) {
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "无法打开文件：" << fileName << endl;
        return;
    }

    for (const SinhVien& student : students) {
        outputFile << student.id << " " << student.name << " " << student.age << " " << student.gender << endl;
    }
    outputFile.close();
}

void Process::search(int option, const string& keyword) {
    bool found = false;
    for (const SinhVien& student : students) {
        if ((option == 1 && student.id == keyword) || (option == 2 && student.name == keyword)) {
            cout << "考号：" << student.id << " 姓名：" << student.name << " 年龄：" << student.age << " 性别：" << student.gender << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "未找到符合条件的学生信息。" << endl;
    }

}

void Process::sort(int option) {
    if (option == 1) {
        sort(students.begin(), students.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.id < b.id;
        });
    } else if (option == 2) {
        sort(students.begin(), students.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.name < b.name;
        });
    }
}

void Process::displaySummary() {
    cout << "共有 " << students.size() << " 名学生。" << endl;
    for (const SinhVien& student : students) {
        cout << "考号：" << student.id << " 姓名：" << student.name << " 年龄：" << student.age << " 性别：" << student.gender << endl;
    }
}

int main() {
    Menu menu;
    Process process;
    SinhVien student;
    int choice, subChoice;
    string id, fileName, keyword;

    do {
        menu.displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                menu.displaySubMenu1();
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        cout << "请输入考号、姓名、年龄和性别：";
                        cin >> student.id >> student.name >> student.age >> student.gender;
                        process.addStudent(student);
                        break;
                    case 2:
                        cout << "请输入要修改的学生的考号：";
                        cin >> id;
                        process.modifyStudent(id);
                        break;
                    case 3:
                        cout << "请输入要删除的学生的考号：";
                        cin >> id;
                        process.deleteStudent(id);
                        break;
                    case 4:
                        cout << "请输入要导入的文件名：";
                        cin >> fileName;
                        process.importFromFile(fileName);
                        break;
                    case 5:
                    // 返回上一级菜单
                        break;
                    default:
                        cout << "无效的选项，请重新输入。" << endl;
                        break;
                }
                break;
            case 2:
                menu.displaySubMenu2();
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        cout << "请输入要查找的学生的考号：";
                        cin >> keyword;
                        process.search(1, keyword);
                        break;
                    case 2:
                        cout << "请输入要查找的学生的姓名：";
                        cin >> keyword;
                        process.search(2, keyword);
                        break;
                    case 3:
                    // 返回上一级菜单
                        break;
                    default:
                        cout << "无效的选项，请重新输入。" << endl;
                        break;
                }
                break;
            case 3:
                menu.displaySubMenu3();
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        process.sort(1);
                        process.displaySummary();
                        break;
                    case 2:
                        process.sort(2);
                        process.displaySummary();
                        break;
                    case 3:
                    // 返回上一级菜单
                        break;
                    default:
                        cout << "无效的选项，请重新输入。" << endl;
                        break;
                }
                break;
            case 4:
                cout << "请输入要导出的文件名：";
                cin >> fileName;
                process.exportToFile(fileName);
                break;
            case 5:
                process.displaySummary();
                break;
            case 6:
                cout << "退出程序。" << endl;
                break;
            default:
                cout << "无效的选项，请重新输入。" << endl;
                break;
        }
    } while (choice != 6);
    return 0;
}


