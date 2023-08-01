#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class CKDataNode {};

class CKDBDataNodeLoader {
private:
    CKDataNode* m_pNode;
    bool m_bIsLoaded;
    mutex m_mtx;
    condition_variable m_cv;

    void LoadDataAsync(function<void()> callback) {
        thread t([this, callback]() {
            // Load data into m_pNode
            callback();
            // Notify that data is loaded
            unique_lock<mutex> lock(m_mtx);
            m_bIsLoaded = true;
            m_cv.notify_all();
        });
        t.detach();
    }

void LoadData() {
    // 模拟数据加载
    this->m_pNode = new CKDataNode();
    // 模拟加载需要时间
    this_thread::sleep_for(chrono::milliseconds(500));
    // Log
    cout << "Data loaded successfully." << endl;
}

void Cleanup() {
    // 模拟资源释放
    if (this->m_pNode != nullptr) {
        delete this->m_pNode;
        this->m_pNode = nullptr;
    }
    // Log
    cout << "Resources cleaned up successfully." << endl;
}


public:
    CKDBDataNodeLoader() : m_pNode(nullptr), m_bIsLoaded(false) {}

    CKDBDataNodeLoader(const CKDBDataNodeLoader& other) {
        unique_lock<mutex> lock(other.m_mtx);
        m_pNode = other.m_pNode;
        m_bIsLoaded = other.m_bIsLoaded;
    }

    CKDBDataNodeLoader& operator=(const CKDBDataNodeLoader& other) {
        if (this != &other) {
            unique_lock<mutex> lock(m_mtx, defer_lock);
            unique_lock<mutex> otherLock(other.m_mtx, defer_lock);
            lock_guard<unique_lock<mutex>> lockGuard(lock, adopt_lock);
            lock_guard<unique_lock<mutex>> otherLockGuard(otherLock, adopt_lock);
            m_pNode = other.m_pNode;
            m_bIsLoaded = other.m_bIsLoaded;
        }
        return *this;
    }

    bool operator==(const CKDBDataNodeLoader& other) const {
        unique_lock<mutex> lock(m_mtx);
        unique_lock<mutex> otherLock(other.m_mtx);
        return (m_pNode == other.m_pNode && m_bIsLoaded == other.m_bIsLoaded);
    }

    void RequestData() {
        unique_lock<mutex> lock(m_mtx);
        if (!m_bIsLoaded) {
            // Load data asynchronously
            LoadDataAsync(bind(&CKDBDataNodeLoader::LoadData, this));
            // Wait for data to be loaded
            m_cv.wait(lock, [this] { return m_bIsLoaded; });
        }
    }

    string ToString() const {
        unique_lock<mutex> lock(m_mtx);
        string result = "CKDBDataNodeLoader: ";
        if (m_pNode == nullptr) {
            result += "nullptr";
        } else {
            result += "data loaded";
        }
        return result;
    }

    ~CKDBDataNodeLoader() {
        Cleanup();
    }
};
