#include <iostream>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>
#include <memory>
using namespace std;

class Thread {
public:
    Thread(DWORD id, HANDLE handle) : m_id(id), m_handle(handle) {}
    DWORD getId() const { return m_id; }
    HANDLE getHandle() const { return m_handle; }
    ~Thread() {
        if (m_handle) {
            CloseHandle(m_handle);
            m_handle = nullptr;
        }
    }
private:
    DWORD m_id;
    HANDLE m_handle;
};

class Process {
public:
    Process(DWORD pid) : m_pid(pid) {}
    vector<Thread> getAll() const {
        vector<Thread> threads;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hSnap == INVALID_HANDLE_VALUE) {
            return threads;
        }
        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);
        if (!Thread32First(hSnap, &te)) {
            CloseHandle(hSnap);
            return threads;
        }
        do {
            if (te.th32OwnerProcessID == m_pid) {
                HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
                if (hThread) {
                    threads.push_back(Thread(te.th32ThreadID, hThread));
                }
            }
        } while (Thread32Next(hSnap, &te));
        CloseHandle(hSnap);
        return threads;
    }
    shared_ptr<Thread> getMain() const {
        HANDLE hThread = GetCurrentThread();
        return make_shared<Thread>(GetCurrentThreadId(), hThread);
    }
    shared_ptr<Thread> getLeastExecuted() const {
        vector<Thread> threads = getAll();
        if (threads.empty()) {
            return nullptr;
        }
        HANDLE hLeastThread = threads[0].getHandle();
        FILETIME ftLeast = { 0xFFFFFFFF, 0xFFFFFFFF };
        for (size_t i = 0; i < threads.size(); i++) {
            FILETIME ftCreation, ftExit, ftKernel, ftUser;
            if (GetThreadTimes(threads[i].getHandle(), &ftCreation, &ftExit, &ftKernel, &ftUser)) {
                ULARGE_INTEGER ulKernel, ulUser;
                ulKernel.LowPart = ftKernel.dwLowDateTime;
                ulKernel.HighPart = ftKernel.dwHighDateTime;
                ulUser.LowPart = ftUser.dwLowDateTime;
                ulUser.HighPart = ftUser.dwHighDateTime;
                ULARGE_INTEGER ulExecuted;
                ulExecuted.QuadPart = ulKernel.QuadPart + ulUser.QuadPart;
                if (ulExecuted.QuadPart < ftLeast.QuadPart) {
                    ftLeast = ulExecuted;
                    hLeastThread = threads[i].getHandle();
                }
            }
        }
        return make_shared<Thread>(GetThreadId(hLeastThread), hLeastThread);
    }
    shared_ptr<Thread> getMostExecuted() const {
        vector<Thread> threads = getAll();
        if (threads.empty()) {
            return nullptr;
        }
        HANDLE hMostThread = threads[0].getHandle();
        FILETIME ftMost = { 0, 0 };
        for (size_t i = 0; i < threads.size(); i++) {
            FILETIME ftCreation, ftExit, ftKernel, ftUser;
            if (GetThreadTimes(threads[i].getHandle(), &ftCreation, &ftExit, &ftKernel, &ftUser)) {
                ULARGE_INTEGER ulKernel, ulUser;
                ulKernel.LowPart = ftKernel.dwLowDateTime;
                ulKernel.HighPart = ftKernel.dwHighDateTime;
                ulUser.LowPart = ftUser.dwLowDateTime;
                ulUser.HighPart = ftUser.dwHighDateTime;
                ULARGE_INTEGER ulExecuted;
                ulExecuted.QuadPart = ulKernel.QuadPart + ulUser.QuadPart;
                if (ulExecuted.QuadPart > ftMost.QuadPart) {
                    ftMost = ulExecuted;
                    hMostThread = threads[i].getHandle();
                }
            }
        }
        return make_shared<Thread>(GetThreadId(hMostThread), hMostThread);
    }
    shared_ptr<Thread> getRandom() const {
        vector<Thread> threads = getAll();
        if (threads.empty()) {
            return nullptr;
        }
        size_t index = rand() % threads.size();
        HANDLE hThread = threads[index].getHandle();
        return make_shared<Thread>(GetThreadId(hThread), hThread);
    }
    shared_ptr<Thread> get(DWORD id) const {
        vector<Thread> threads = getAll();
        for (size_t i = 0; i < threads.size(); i++) {
            if (threads[i].getId() == id) {
                HANDLE hThread = threads[i].getHandle();
                return make_shared<Thread>(id, hThread);
            }
        }
        return nullptr;
    }
    shared_ptr<Thread> CreateNew() {
        HANDLE hThread = CreateThread(nullptr, 0, [](LPVOID lpParam) -> DWORD {
            Sleep(1000);
            return 0;
        }, nullptr, 0, nullptr);
        if (hThread) {
            return make_shared<Thread>(GetThreadId(hThread), hThread);
        }
        return nullptr;
    }
private:
    DWORD m_pid;
};
