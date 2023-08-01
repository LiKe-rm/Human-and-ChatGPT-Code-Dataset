#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class DataList {
public:
    DataList() = default;

    // 初始化
    void initialize(const std::vector<T> &data) {
        dataList = data;
    }

    // 插入
    void insert(const T &value) {
        dataList.push_back(value);
    }

    // 删除
    bool remove(const T &value, std::function<bool(const T &, const T &)> compare) {
        auto it = std::find_if(dataList.begin(), dataList.end(), [&](const T &item) { return compare(item, value); });

        if (it != dataList.end()) {
            dataList.erase(it);
            return true;
        }

        return false;
    }

    // 读取
    void read() const {
        for (const auto &item : dataList) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 写入
    void write(const std::vector<T> &data) {
        dataList = data;
    }

    // 排序
    void sort(std::function<bool(const T &, const T &)> compare) {
        std::sort(dataList.begin(), dataList.end(), compare);
    }

    // 查找
    int find(const T &value, std::function<bool(const T &, const T &)> compare) const {
        auto it = std::find_if(dataList.begin(), dataList.end(), [&](const T &item) { return compare(item, value); });

        if (it != dataList.end()) {
            return std::distance(dataList.begin(), it);
        }

        return -1;
    }

private:
    std::vector<T> dataList;
};

// 示例比较函数
bool compareAscending(int a, int b) {
    return a < b;
}

bool compareDescending(int a, int b) {
    return a > b;
}

bool compareEqual(int a, int b) {
    return a == b;
}

int main() {
    DataList<int> dataList;
    std::vector<int> initialData = {10, 5, 8, 3, 7};

    dataList.initialize(initialData);
    dataList.read();

    dataList.insert(4);
    dataList.read();

    dataList.remove(3, compareEqual);
    dataList.read();

    dataList.write({1, 2, 3, 4, 5});
    dataList.read();

    dataList.sort(compareAscending);
    dataList.read();

    dataList.sort(compareDescending);
    dataList.read();

    std::cout << "找到5的位置: " << dataList.find(5, compareEqual) << std::endl;

    return 0;
}
