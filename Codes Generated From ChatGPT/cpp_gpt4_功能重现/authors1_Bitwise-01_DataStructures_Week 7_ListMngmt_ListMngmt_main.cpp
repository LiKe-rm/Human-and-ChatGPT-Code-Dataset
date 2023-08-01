#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 5;

struct IntArray {
    int data[MAX_SIZE];
    int size;
};

void menu();
void addElement(IntArray &arr, int element);
void removeElement(IntArray &arr, int element);
int searchElement(const IntArray &arr, int element);
void displayArray(const IntArray &arr);
bool isArrayEmpty(const IntArray &arr);
bool isArrayFull(const IntArray &arr);
int getMinElement(const IntArray &arr);
int getMaxElement(const IntArray &arr);

int main() {
    IntArray arr;
    arr.size = 0;

    int choice, element;

    do {
        menu();
        cout << "选择操作: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "输入要添加的元素: ";
                cin >> element;
                addElement(arr, element);
                break;
            case 2:
                cout << "输入要删除的元素: ";
                cin >> element;
                removeElement(arr, element);
                break;
            case 3:
                cout << "输入要查找的元素: ";
                cin >> element;
                int index;
                index = searchElement(arr, element);
                if (index != -1) {
                    cout << "找到元素 " << element << " 位于索引 " << index << endl;
                } else {
                    cout << "未找到元素 " << element << endl;
                }
                break;
            case 4:
                displayArray(arr);
                break;
            case 5:
                cout << "数组大小: " << arr.size << endl;
                break;
            case 6:
                if (isArrayEmpty(arr)) {
                    cout << "数组为空" << endl;
                } else {
                    cout << "数组非空" << endl;
                }
                break;
            case 7:
                if (isArrayFull(arr)) {
                    cout << "数组已满" << endl;
                } else {
                    cout << "数组未满" << endl;
                }
                break;
            case 8:
                cout << "最小元素: " << getMinElement(arr) << endl;
                break;
            case 9:
                cout << "最大元素: " << getMaxElement(arr) << endl;
                break;
            case 10:
                cout << "退出程序" << endl;
                break;
            default:
                cout << "无效选项，请重新选择" << endl;
        }

    } while (choice != 10);

    return 0;
}

void menu() {
    cout << "1. 添加元素" << endl;
    cout << "2. 删除元素" << endl;
    cout << "3. 搜索元素" << endl;
    cout << "4. 显示数组" << endl;
    cout << "5. 检查数组大小" << endl;
    cout << "6. 检查数组是否为空" << endl;
    cout << "7. 检查数组是否已满" << endl;
    cout << "8. 获取最小元素" << endl;
    cout << "9. 获取最大元素" << endl;
    cout << "10. 退出" << endl;
}

void addElement(IntArray &arr, int element) {
    if (arr.size < MAX_SIZE) {
        arr.data[arr.size++] = element;
        cout << "元素 " << element << " 已添加" << endl;
    } else {
        cout << "数组已满，无法添加元素" << endl;
    }
}

void removeElement(IntArray &arr, int element) {
    int index = searchElement(arr, element);
    if (index != -1) {
        for (int i = index; i < arr.size - 1; ++i) {
            arr.data[i] = arr.data[i + 1];
        }
        arr.size--;
        cout << "元素 " << element << " 已删除" << endl;
    } else {
        cout << "未找到元素 " << element << endl;
    }
}

int searchElement(const IntArray &arr, int element) {
    for (int i = 0; i < arr.size; ++i) {
        if (arr.data[i] == element) {
            return i;
        }
    }
    return -1;
}

void displayArray(const IntArray &arr) {
    cout << "数组元素: ";
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

bool isArrayEmpty(const IntArray &arr) {
    return arr.size == 0;
}

bool isArrayFull(const IntArray &arr) {
    return arr.size == MAX_SIZE;
}

int getMinElement(const IntArray &arr) {
    if (isArrayEmpty(arr)) {
        cout << "数组为空，无法获取最小元素" << endl;
        return -1;
    }

    int minElement = arr.data[0];
    for (int i = 1; i < arr.size; ++i) {
        if (arr.data[i] < minElement) {
            minElement = arr.data[i];
        }
    }
    return minElement;
}

int getMaxElement(const IntArray &arr) {
    if (isArrayEmpty(arr)) {
        cout << "数组为空，无法获取最大元素" << endl;
        return -1;
    }

    int maxElement = arr.data[0];
    for (int i = 1; i < arr.size; ++i) {
        if (arr.data[i] > maxElement) {
            maxElement = arr.data[i];
        }
    }
    return maxElement;
}
