#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>

class CLogBuffer {
public:
    void Init() {
        buffer.clear();
    }

    std::string Get() {
        return buffer;
    }

    void appendLog(const std::string &log) {
        std::unique_lock<std::mutex> lock(mtx);
        buffer += log;
        buffer += '\n';
    }

    CLogBuffer &operator<<(const std::string &log) {
        appendLog(log);
        return *this;
    }

private:
    std::string buffer;
    std::mutex mtx;
};

class CLogFile {
public:
    void InitLogFile(const std::string &filename) {
        logFile.open(filename, std::ios::out | std::ios::app);
    }

    void Write(const std::string &log) {
        if (logFile.is_open()) {
            logFile << log << std::endl;
        }
    }

private:
    std::ofstream logFile;
};

class CLogHeader {
public:
    std::string p_header1;
    std::string p_header2;
    std::string p_header3;
};

CLogBuffer g_dblogbuffer;
CLogBuffer g_gamelogbuffer;

void end() {
    g_dblogbuffer.Init();
    g_gamelogbuffer.Init();
}

void init(const std::string &dbLogFilename, const std::string &gameLogFilename) {
    g_dblogbuffer.Init();
    g_gamelogbuffer.Init();
    CLogFile dbLogFile, gameLogFile;
    dbLogFile.InitLogFile(dbLogFilename);
    gameLogFile.InitLogFile(gameLogFilename);
}

CLogHeader createLogHeader(const std::string &header1, const std::string &header2, const std::string &header3) {
    CLogHeader logHeader;
    logHeader.p_header1 = header1;
    logHeader.p_header2 = header2;
    logHeader.p_header3 = header3;
    return logHeader;
}

std::string getCurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

std::string formatLogHeader(const CLogHeader &header) {
    std::string formattedLogHeader = getCurrentDateTime() + " - ";
    formattedLogHeader += header.p_header1 + " | " + header.p_header2 + " | " + header.p_header3;
    return formattedLogHeader;
}

int main() {
    init("dblog.txt", "gamelog.txt");

    CLogHeader logHeader = createLogHeader("INFO", "Database", "Connection established");
    std::string logHeaderStr = formatLogHeader(logHeader);

    g_dblogbuffer << logHeaderStr << " - This is a database log";
    g_gamelogbuffer << logHeaderStr << " - This is a game log";

    CLogFile dbLogFile, gameLogFile;
    dbLogFile.InitLogFile("dblog.txt");
    gameLogFile.InitLogFile("gamelog.txt");

    dbLogFile.Write(g_dblogbuffer.Get());
    gameLogFile.Write(g_gamelogbuffer.Get());

    end();

    return 0;
}
