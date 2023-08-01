#include <windows.h>
#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>

// ����IOCP����
HANDLE g_iocp = INVALID_HANDLE_VALUE;

// ����ÿ��IO����Ľṹ��
struct IORequest {
    OVERLAPPED overlapped; // �ص��ṹ��
    HANDLE file_handle; // �ļ����
    DWORD bytes_to_transfer; // Ҫ������ֽ���
    DWORD bytes_transferred; // �Ѿ�������ֽ���
    std::vector<char> buffer; // ���ݻ�����
};

// ����IO�����̳߳���
class IOThreadPool {
    public:
    IOThreadPool(): m_thread_count(0), m_stop(false) {}

    // ��ʼ���̳߳�
    bool Initialize(int thread_count) {
        // ����IOCP����
        g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (g_iocp == NULL) {
            std::cerr << "Error creating IOCP: " << GetLastError() << std::endl;
            return false;
        }

        // ����IO�����߳�
        for (int i = 0; i < thread_count; i++) {
            m_threads.emplace_back(&IOThreadPool::WorkerThread, this);
        }
        m_thread_count = thread_count;

        return true;
    }

    // ��IOCP�����IO����
    void AddRequest(IORequest* request) {
        // ���������IOCP����
        if (CreateIoCompletionPort(request->file_handle, g_iocp, reinterpret_cast<ULONG_PTR>(request), 0) == NULL) {
            std::cerr << "Error adding request to IOCP: " << GetLastError() << std::endl;
            return;
        }

        // �����첽IO����
        DWORD bytes_transferred = 0;
        if (!ReadFileEx(request->file_handle, &request->buffer[0], request->bytes_to_transfer, &request->overlapped, IoCompletionRoutine)) {
            DWORD last_error = GetLastError();
            if (last_error != ERROR_IO_PENDING) {
                std::cerr << "Error starting IO request: " << last_error << std::endl;
                return;
            }
        }
    }

    // ֹͣ�̳߳�
    void Stop() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
        }
        m_cond.notify_all();

        // �ȴ������߳��˳�
        for (auto& thread : m_threads) {
            thread.join();
        }

        // �ر�IOCP����
        CloseHandle(g_iocp);
        g_iocp = INVALID_HANDLE_VALUE;
    }

    private:
        // IO�����̺߳���
    void WorkerThread() {
        while (true) {
            DWORD bytes_transferred = 0;
            IORequest* request = nullptr;
            ULONG_PTR completion_key = 0;
            DWORD error = 0;

            // �ȴ�IOCP֪ͨ
            if (GetQueuedCompletionStatus(g_iocp, &bytes_transferred, &completion_key
                , reinterpret_cast<LPOVERLAPPED*>(&request), INFINITE) == FALSE) {
                error = GetLastError();
            }
                    // ����̳߳���ֹͣ�����˳��߳�
            if (m_stop && request == nullptr) {
                break;
            }

            // ����IO����
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

    // ������ɵ�IO����
    void HandleRequest(IORequest* request) {
        // TODO: �������󣬱��罫���ݷ��͵�����Ȳ���
    }
    private:
    std::vectorstd::thread m_threads; // IO�����߳�
    std::atomic<int> m_thread_count; // �߳�����
    std::atomic<bool> m_stop; // �̳߳��Ƿ�ֹͣ
    std::mutex m_mutex; // ������
    std::condition_variable m_cond; // ��������
};

// IO��ɻص�����
void CALLBACK IoCompletionRoutine(DWORD error_code, DWORD bytes_transferred, LPOVERLAPPED overlapped) {
    IORequest* request = reinterpret_cast<IORequest*>(overlapped);
    if (error_code == 0) {
        request->bytes_transferred = bytes_transferred;
        // �������IO������ӵ�IOCP������
        if (PostQueuedCompletionStatus(g_iocp, 0, reinterpret_cast<ULONG_PTR>(request), nullptr) == FALSE) {
            std::cerr << "Error queuing completion status: " << GetLastError() << std::endl;
        }
    } else {
        std::cerr << "IO request failed with error code " << error_code << std::endl;
    }
}

int main() {
// ��ʼ��IO�����̳߳�
    IOThreadPool io_thread_pool;
    if (!io_thread_pool.Initialize(4)) {
        return 1;
    }
    // ���ļ�
    HANDLE file_handle = CreateFile("test.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file: " << GetLastError() << std::endl;
        return 1;
    }

    // ����IO����
    IORequest request;
    request.file_handle = file_handle;
    request.bytes_to_transfer = 1024;
    request.buffer.resize(request.bytes_to_transfer);
    memset(&request.overlapped, 0, sizeof(request.overlapped));
    request.overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // ���IO����IOCP����
    io_thread_pool.AddRequest(&request);

    // �ȴ�IO�������
    if (WaitForSingleObject(request.overlapped.hEvent, INFINITE) == WAIT_FAILED) {
        std::cerr << "Error waiting for IO request to complete: " << GetLastError() << std::endl;
        return 1;
    }

    // �ر��ļ����
    CloseHandle(file_handle);

    // ֹͣIO�����̳߳�
    io_thread_pool.Stop();

    return 0;
}