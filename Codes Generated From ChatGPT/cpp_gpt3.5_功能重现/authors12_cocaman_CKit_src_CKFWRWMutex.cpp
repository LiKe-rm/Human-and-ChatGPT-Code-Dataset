#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class CKFWRWMutex {
public:
    CKFWRWMutex() : read_count_(0), write_count_(0) {}

    ~CKFWRWMutex() {}

    void readLock() {
        unique_lock<mutex> lock(mutex_);
        while (write_count_ > 0) {
            cv_.wait(lock);
        }
        read_count_++;
    }

    bool tryReadLock() {
        lock_guard<mutex> lock(mutex_);
        if (write_count_ > 0) {
            return false;
        }
        read_count_++;
        return true;
    }

    void writeLock() {
        unique_lock<mutex> lock(mutex_);
        while (read_count_ > 0 || write_count_ > 0) {
            cv_.wait(lock);
        }
        write_count_++;
    }

    bool tryWriteLock() {
        lock_guard<mutex> lock(mutex_);
        if (read_count_ > 0 || write_count_ > 0) {
            return false;
        }
        write_count_++;
        return true;
    }

    void unlock() {
        lock_guard<mutex> lock(mutex_);
        if (write_count_ > 0) {
            write_count_--;
        }
        else if (read_count_ > 0) {
            read_count_--;
        }
        cv_.notify_all();
    }

private:
    mutex mutex_;
    condition_variable cv_;
    int read_count_;
    int write_count_;
};
