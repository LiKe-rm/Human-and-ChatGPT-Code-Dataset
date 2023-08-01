#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string>
#include <vector>

struct CKDataNode {
    // 这里定义了一个基于文件的CKDataNode数据结构，具体实现未给出
};

class AsyncFileLoader {
public:
    AsyncFileLoader(const std::string& filename) 
        : m_filename(filename), m_fileLoaded(false), m_thread(&AsyncFileLoader::loadFile, this) {}
    
    ~AsyncFileLoader() {
        m_thread.join();
    }

    bool isLoaded() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_fileLoaded;
    }

    CKDataNode& getData() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this]() { return m_fileLoaded; });
        return m_data;
    }

    static void loadFile(AsyncFileLoader* loader) {
        CKDataNode data;
        std::ifstream file(loader->m_filename, std::ios::binary);
        // 读取文件并将数据填充到data中
        // 这里假设文件是二进制格式，实际情况可能需要根据具体格式进行解析
        loader->setData(data);
    }

private:
    void setData(const CKDataNode& data) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data = data;
        m_fileLoaded = true;
        m_cv.notify_all();
    }

private:
    std::string m_filename;
    CKDataNode m_data;
    bool m_fileLoaded;
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};
