#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename T>
class DataList {
public:
    DataList() = default;
    ~DataList() = default;

    void read();
    void write() const;
    void insert(const T& value, size_t position);
    void remove(size_t position);
    void sort();
    int search(const T& value) const;

private:
    std::vector<T> data_;
};

template<typename T>
void DataList<T>::read() {
    size_t n;
    std::cout << "请输入数据数量: ";
    std::cin >> n;

    data_.resize(n);

    std::cout << "请输入 " << n << " 个数据: ";
    for (auto& elem : data_) {
        std::cin >> elem;
    }
}

template<typename T>
void DataList<T>::write() const {
    std::cout << "数据列表: ";
    for (const auto& elem : data_) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void DataList<T>::insert(const T& value, size_t position) {
    if (position < 0 || position > data_.size()) {
        throw std::out_of_range("插入位置超出范围");
    }
    data_.insert(data_.begin() + position, value);
}

template<typename T>
void DataList<T>::remove(size_t position) {
    if (position < 0 || position >= data_.size()) {
        throw std::out_of_range("删除位置超出范围");
    }
    data_.erase(data_.begin() + position);
}

template<typename T>
void DataList<T>::sort() {
    std::sort(data_.begin(), data_.end());
}

template<typename T>
int DataList<T>::search(const T& value) const {
    auto it = std::find(data_.begin(), data_.end(), value);
    if (it != data_.end()) {
        return std::distance(data_.begin(), it);
    }
    return -1;
}

int main() {
    DataList<int> votes;

    votes.read();
    votes.write();

    int value = 42;
    size_t position = 2;
    votes.insert(value, position);
    votes.write();

    votes.remove(position);
    votes.write();

    votes.sort();
    votes.write();

    int searchValue = 42;
    int index = votes.search(searchValue);
    if (index != -1) {
        std::cout << "找到值 " << searchValue << " 在位置 " << index << std::endl;
    } else {
        std::cout << "未找到值 " << searchValue << std::endl;
    }

    return 0;
}
