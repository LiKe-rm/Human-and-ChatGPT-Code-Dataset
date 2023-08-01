#include <iostream>
#include <unordered_map>
#include <mutex>

std::unordered_map<void *, size_t> memory_map;
std::mutex memory_map_mutex;

void *operator new(size_t size) {
    void *ptr = std::malloc(size);

    if (ptr) {
        std::unique_lock<std::mutex> lock(memory_map_mutex);
        memory_map[ptr] = size;
    } else {
        throw std::bad_alloc();
    }

    return ptr;
}

void operator delete(void *ptr) noexcept {
    if (ptr) {
        std::unique_lock<std::mutex> lock(memory_map_mutex);
        memory_map.erase(ptr);
    }

    std::free(ptr);
}

class MemoryLeakDetector {
public:
    ~MemoryLeakDetector() {
        std::unique_lock<std::mutex> lock(memory_map_mutex);

        if (!memory_map.empty()) {
            std::cerr << "Memory leak detected! " << memory_map.size() << " leaks found.\n";
            for (const auto &entry : memory_map) {
                std::cerr << "Leak: address = " << entry.first << ", size = " << entry.second << " bytes\n";
            }
        } else {
            std::cerr << "No memory leaks detected.\n";
        }
    }
};

MemoryLeakDetector memory_leak_detector;
