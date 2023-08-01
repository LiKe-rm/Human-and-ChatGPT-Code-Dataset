  #include <iostream>
#include <cstdlib>
#include <new>
#include <map>
#include <mutex>

// VLD的全局变量和内部私有堆
static std::map<void*, size_t> g_vldAllocations;
static std::mutex g_vldMutex;

// 重载C++的new操作符
void* operator new(size_t size) {
    std::lock_guard<std::mutex> lock(g_vldMutex);

    // 在VLD的私有堆中分配内存
    void* ptr = malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }

    // 将内存泄漏信息记录在VLD的内部链表中
    g_vldAllocations[ptr] = size;
    return ptr;
}

// 重载C++的delete操作符
void operator delete(void* ptr) noexcept {
    if (!ptr) {
        return;
    }

    std::lock_guard<std::mutex> lock(g_vldMutex);

    // 从VLD的内部链表中删除内存泄漏信息，并在VLD的私有堆中释放内存
    auto iter = g_vldAllocations.find(ptr);
    if (iter != g_vldAllocations.end()) {
        g_vldAllocations.erase(iter);
        free(ptr);
    }
}

// VLD的辅助函数
void* vldnew(size_t size) {
    return operator new(size);
}

void vlddelete(void* ptr) noexcept {
    operator delete(ptr);
}

// 输出内存泄漏报告
void reportLeaks() {
    std::lock_guard<std::mutex> lock(g_vldMutex);

    if (g_vldAllocations.empty()) {
        std::cout << "没有检测到内存泄漏。" << std::endl;
    } else {
        std::cout << "检测到内存泄漏：" << std::endl;
        for (const auto& allocation : g_vldAllocations) {
            std::cout << "地址：" << allocation.first << " 大小：" << allocation.second << " 字节" << std::endl;
        }
    }
}

int main() {
    int* p1 = new int;
    int* p2 = new int[10];

    delete p1;

    reportLeaks();

    delete[] p2;

    return 0;
}
