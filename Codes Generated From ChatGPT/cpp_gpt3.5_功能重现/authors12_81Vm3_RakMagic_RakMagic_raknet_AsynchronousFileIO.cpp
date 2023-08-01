#include <windows.h>
#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>

// 定义IOCP对象
HANDLE g_iocp = INVALID_HANDLE_VALUE;

// 定义每个IO请求的结构体
struct IORequest {
    OVERLAPPED overlapped; // 重叠结构体
    HANDLE file_handle; // 文件句柄
    DWORD bytes_to_transfer; // 要传输的字节数
    DWORD bytes_transferred; // 已经传输的字节数
    std::vector<char> buffer; // 数据缓冲区
};

// 定义IO处理线程池类
class IOThreadPool {
    public:
    IOThreadPool(): m_thread_count(0), m_stop(false) {}

    // 初始化线程池
    bool Initialize(int thread_count) {
        // 创建IOCP对象
        g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (g_iocp == NULL) {
            std::cerr << "Error creating IOCP: " << GetLastError() << std::endl;
            return false;
        }

        // 启动IO处理线程
        for (int i = 0; i < thread_count; i++) {
            m_threads.emplace_back(&IOThreadPool::WorkerThread, this);
        }
        m_thread_count = thread_count;

        return true;
    }

    // 向IOCP中添加IO请求
    void AddRequest(IORequest* request) {
        // 将请求加入IOCP队列
        if (CreateIoCompletionPort(request->file_handle, g_iocp, reinterpret_cast<ULONG_PTR>(request), 0) == NULL) {
            std::cerr << "Error adding request to IOCP: " << GetLastError() << std::endl;
            return;
        }

        // 发起异步IO请求
        DWORD bytes_transferred = 0;
        if (!ReadFileEx(request->file_handle, &request->buffer[0], request->bytes_to_transfer, &request->overlapped, IoCompletionRoutine)) {
            DWORD last_error = GetLastError();
            if (last_error != ERROR_IO_PENDING) {
                std::cerr << "Error starting IO request: " << last_error << std::endl;
                return;
            }
        }
    }

    // 停止线程池
    void Stop() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
        }
        m_cond.notify_all();

        // 等待所有线程退出
        for (auto& thread : m_threads) {
            thread.join();
        }

        // 关闭IOCP对象
        CloseHandle(g_iocp);
        g_iocp = INVALID_HANDLE_VALUE;
    }

    private:
        // IO处理线程函数
    void WorkerThread() {
        while (true) {
            DWORD bytes_transferred = 0;
            IORequest* request = nullptr;
            ULONG_PTR completion_key = 0;
            DWORD error = 0;

            // 等待IOCP通知
            if (GetQueuedCompletionStatus(g_iocp, &bytes_transferred, &completion_key
                , reinterpret_cast<LPOVERLAPPED*>(&request), INFINITE) == FALSE) {
                error = GetLastError();
            }
                    // 如果线程池已停止，则退出线程
            if (m_stop && request == nullptr) {
                break;
            }

            // 处理IO请求
            if (request != nullptr) {
                if (error == 0) {
                    request->bytes_transferred = bytes_transferred;
                    HandleRequest(request);
                } else {
                    std::cerr << "Error handling IO request: " << error << std::endl;
                }
            }
        }
    }

    // 处理完成的IO请求
    void HandleRequest(IORequest* request) {
        // TODO: 处理请求，比如将数据发送到网络等操作
    }
    private:
    std::vectorstd::thread m_threads; // IO处理线程
    std::atomic<int> m_thread_count; // 线程数量
    std::atomic<bool> m_stop; // 线程池是否停止
    std::mutex m_mutex; // 互斥量
    std::condition_variable m_cond; // 条件变量
};

// IO完成回调函数
void CALLBACK IoCompletionRoutine(DWORD error_code, DWORD bytes_transferred, LPOVERLAPPED overlapped) {
    IORequest* request = reinterpret_cast<IORequest*>(overlapped);
    if (error_code == 0) {
        request->bytes_transferred = bytes_transferred;
        // 将请求的IO请求添加到IOCP队列中
        if (PostQueuedCompletionStatus(g_iocp, 0, reinterpret_cast<ULONG_PTR>(request), nullptr) == FALSE) {
            std::cerr << "Error queuing completion status: " << GetLastError() << std::endl;
        }
    } else {
        std::cerr << "IO request failed with error code " << error_code << std::endl;
    }
}

int main() {
// 初始化IO处理线程池
    IOThreadPool io_thread_pool;
    if (!io_thread_pool.Initialize(4)) {
        return 1;
    }
    // 打开文件
    HANDLE file_handle = CreateFile("test.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file: " << GetLastError() << std::endl;
        return 1;
    }

    // 构造IO请求
    IORequest request;
    request.file_handle = file_handle;
    request.bytes_to_transfer = 1024;
    request.buffer.resize(request.bytes_to_transfer);
    memset(&request.overlapped, 0, sizeof(request.overlapped));
    request.overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // 添加IO请求到IOCP队列
    io_thread_pool.AddRequest(&request);

    // 等待IO请求完成
    if (WaitForSingleObject(request.overlapped.hEvent, INFINITE) == WAIT_FAILED) {
        std::cerr << "Error waiting for IO request to complete: " << GetLastError() << std::endl;
        return 1;
    }

    // 关闭文件句柄
    CloseHandle(file_handle);

    // 停止IO处理线程池
    io_thread_pool.Stop();

    return 0;
}