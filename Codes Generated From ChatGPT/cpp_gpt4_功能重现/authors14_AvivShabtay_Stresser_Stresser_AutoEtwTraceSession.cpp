#include <iostream>
#include <thread>
#include <evntrace.h>
#include <evntcons.h>

class ETWTraceManager {
public:
    ETWTraceManager(const std::wstring& sessionName, const std::wstring& logfileName, const TRACE_PROPERTIES& traceProperties)
        : m_sessionName(sessionName), m_logfileName(logfileName), m_traceProperties(traceProperties), m_traceHandle(0) {
        startTrace();
    }

    ~ETWTraceManager() {
        stopTrace();
    }

    void reset(const std::wstring& sessionName, const std::wstring& logfileName, const TRACE_PROPERTIES& traceProperties) {
        stopTrace();
        m_sessionName = sessionName;
        m_logfileName = logfileName;
        m_traceProperties = traceProperties;
        startTrace();
    }

    void release() {
        stopTrace();
    }

    void startTrace() {
        EVENT_TRACE_PROPERTIES properties;
        initProperties(properties);

        ULONG status = StartTrace(&m_traceHandle, m_sessionName.c_str(), &properties);
        if (ERROR_SUCCESS != status) {
            std::cerr << "Failed to start trace: " << status << std::endl;
            return;
        }

        m_traceThread = std::thread(&ETWTraceManager::traceThreadFunc, this);
    }

    void stopTrace() {
        if (m_traceHandle) {
            ULONG status = ControlTrace(m_traceHandle, nullptr, nullptr, EVENT_TRACE_CONTROL_STOP);
            if (ERROR_SUCCESS != status) {
                std::cerr << "Failed to stop trace: " << status << std::endl;
            }

            if (m_traceThread.joinable()) {
                m_traceThread.join();
            }
            m_traceHandle = 0;
        }
    }

    void setProperties(const TRACE_PROPERTIES& traceProperties) {
        m_traceProperties = traceProperties;
    }

    const TRACE_PROPERTIES& getProperties() const {
        return m_traceProperties;
    }

private:
    void initProperties(EVENT_TRACE_PROPERTIES& properties) {
        ZeroMemory(&properties, sizeof(EVENT_TRACE_PROPERTIES));
        properties.Wnode.BufferSize = sizeof(EVENT_TRACE_PROPERTIES) + m_sessionName.size() * sizeof(wchar_t) + m_logfileName.size() * sizeof(wchar_t);
        properties.Wnode.Flags = WNODE_FLAG_TRACED_GUID;
        properties.Wnode.ClientContext = 1;
        properties.BufferSize = 64;
        properties.MinimumBuffers = 20;
        properties.MaximumBuffers = 200;
        properties.LogFileMode = m_traceProperties.LogFileMode;
        properties.FlushTimer = 1;
        properties.LogFileNameOffset = sizeof(EVENT_TRACE_PROPERTIES) + m_sessionName.size() * sizeof(wchar_t);
        properties.LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
    }

    void traceThreadFunc() {
        // Implement your trace processing logic here.
    }

private:
    std::wstring m_sessionName;
    std::wstring m_logfileName;
    TRACE_PROPERTIES m_traceProperties;
    TRACEHANDLE m_traceHandle;
    std::thread m_traceThread;
};

int main() {
    TRACE_PROPERTIES traceProperties;
    traceProperties.LogFileMode = EVENT_TRACE_FILE_MODE_SEQUENTIAL;

    ETWTraceManager traceManager(L"MySession", L"MyLog.etl", traceProperties);

    // Simulate your application's work.
    std::this_thread::sleep_for(std::chrono::seconds(10));

    traceManager.release();

    return 0;
}
