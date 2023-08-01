#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <shared_mutex>

template<typename T>
class SortedList {
public:
    SortedList() = default;
    ~SortedList() { clear(); }

    void insert(const T& value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        list_.insert(std::upper_bound(list_.begin(), list_.end(), value), value);
    }

    void clear() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        list_.clear();
    }

    bool remove(const T& value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto it = std::find(list_.begin(), list_.end(), value);
        if (it != list_.end()) {
            list_.erase(it);
            return true;
        }
        return false;
    }

    T* next(T* current) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (current == nullptr) {
            return list_.empty() ? nullptr : &list_.front();
        }

        auto it = std::find(list_.begin(), list_.end(), *current);
        assert(it != list_.end());
        ++it;
        return it == list_.end()? nullptr : &(*it);
    }
    size_t size() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return list_.size();
}

void lock_write() {
    mutex_.lock();
}

void lock_read() {
    mutex_.lock_shared();
}

void unlock_write() {
    mutex_.unlock();
}

void unlock_read() {
    mutex_.unlock_shared();
}
private:
    std::list<T> list_;
    mutable std::shared_mutex mutex_;
};
int main() {
    SortedList<int> sorted_list;
    sorted_list.insert(5);
    sorted_list.insert(1);
    sorted_list.insert(9);
    sorted_list.insert(4);
    sorted_list.insert(3);

    for (int* p = sorted_list.next(nullptr); p != nullptr; p = sorted_list.next(p)) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    sorted_list.remove(1);
    sorted_list.remove(9);

    for (int* p = sorted_list.next(nullptr); p != nullptr; p = sorted_list.next(p)) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    return 0;

}
