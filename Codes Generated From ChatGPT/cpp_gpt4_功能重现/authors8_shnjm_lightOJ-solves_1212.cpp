#include <iostream>
#include <deque>
#include <string>
#include <limits>

void display_menu() {
    std::cout << "\n双端队列操作菜单: \n";
    std::cout << "1. 添加元素到队首\n";
    std::cout << "2. 添加元素到队尾\n";
    std::cout << "3. 移除队首元素\n";
    std::cout << "4. 移除队尾元素\n";
    std::cout << "5. 查看队首元素\n";
    std::cout << "6. 查看队尾元素\n";
    std::cout << "7. 查看队列长度\n";
    std::cout << "8. 检查队列是否为空\n";
    std::cout << "0. 退出程序\n";
}

void add_front(std::deque<int>& deque) {
    int value;
    std::cout << "请输入要添加到队首的元素: ";
    std::cin >> value;
    deque.push_front(value);
}

void add_back(std::deque<int>& deque) {
    int value;
    std::cout << "请输入要添加到队尾的元素: ";
    std::cin >> value;
    deque.push_back(value);
}

void remove_front(std::deque<int>& deque) {
    if (!deque.empty()) {
        deque.pop_front();
    } else {
        std::cout << "队列为空，无法移除元素。\n";
    }
}

void remove_back(std::deque<int>& deque) {
    if (!deque.empty()) {
        deque.pop_back();
    } else {
        std::cout << "队列为空，无法移除元素。\n";
    }
}

void display_front(const std::deque<int>& deque) {
    if (!deque.empty()) {
        std::cout << "队首元素: " << deque.front() << std::endl;
    } else {
        std::cout << "队列为空。\n";
    }
}

void display_back(const std::deque<int>& deque) {
    if (!deque.empty()) {
        std::cout << "队尾元素: " << deque.back() << std::endl;
    } else {
        std::cout << "队列为空。\n";
    }
}

void display_length(const std::deque<int>& deque) {
    std::cout << "队列长度: " << deque.size() << std::endl;
}

void check_empty(const std::deque<int>& deque) {
    std::cout << (deque.empty() ? "队列为空。" : "队列非空。") << std::endl;
}

int main() {
    std::deque<int> deque;
    int choice;
    bool exit = false;

    while (!exit) {
        display_menu();
        std::cout << "请输入操作序号: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                add_front(deque);
                break;
            case 2:
                add_back(deque);
                break;
            case 3:
                remove_front(deque);
                break;
            case 4:
                remove_back(deque);
                break;
            case 5:
                display_front(deque);
                break;
            case 6:
                display_back(deque);
                break;
            case 7:
                display_length(deque);
                           break;
            case 8:
                check_empty(deque);
                break;
            case 0:
                exit = true;
                break;
            default:
                std::cout << "无效的选项，请重新输入。\n";
                break;
        }
        // 清空输入缓冲区，防止错误输入导致死循环
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "感谢使用双端队列操作程序，再见!\n";
    return 0;
}

