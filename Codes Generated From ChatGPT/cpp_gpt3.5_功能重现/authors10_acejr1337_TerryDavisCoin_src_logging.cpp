#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_set>

class Logger {
    public:
    enum class MessageType {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    explicit Logger(bool console_output = true, bool file_output = true,
        const std::string& file_path = "log.txt")
        : console_output_(console_output),
        file_output_(file_output),
        file_path_(file_path),
        log_file_() {}

    void OpenLogFile() {
        if (!file_output_) return;
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_.open(file_path_, std::ios::out | std::ios::app);
    }

    void CloseLogFile() {
        if (!file_output_) return;
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_.close();
    }

    void EnableMessageType(MessageType type) {
        std::lock_guard<std::mutex> lock(mutex_);
        enabled_types_.insert(type);
    }

    void DisableMessageType(MessageType type) {
        std::lock_guard<std::mutex> lock(mutex_);
        enabled_types_.erase(type);
    }

    bool IsMessageTypeEnabled(MessageType type) const {
        return enabled_types_.count(type) > 0;
    }

    template <typename... Args>
    void Log(MessageType type, const std::string& format, Args... args) {
        if (!IsMessageTypeEnabled(type)) return;
        std::string message = FormatMessage(format, args...);
        std::string escaped_message = EscapeMessage(message);
        if (console_output_) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::cout << escaped_message << std::endl;
        }
        if (file_output_) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!log_file_.is_open()) OpenLogFile();
            log_file_ << escaped_message << std::endl;
            if (log_file_.tellp() > kMaxLogFileSize) ShrinkLogFile();
        }
    }

    void DeleteLogFile() {
        if (!file_output_) return;
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_.close();
        std::remove(file_path_.c_str());
    }

    private:
    static const std::unordered_set<MessageType> kDefaultEnabledTypes;

    bool console_output_;
    bool file_output_;
    std::string file_path_;
    std::ofstream log_file_;
    std::mutex mutex_;
    std::unordered_set<MessageType> enabled_types_{kDefaultEnabledTypes};

    static constexpr std::streampos kMaxLogFileSize = 1024 * 1024 * 10;  // 10 MB

    std::string FormatMessage(const std::string& format) const {
        return format;
    }

    template <typename T, typename... Args>
    std::string FormatMessage(const std::string& format, T arg, Args... args) const {
        size_t pos = format.find("{}");
        if (pos == std::string::npos) {
            return format;
        }
        std::string result = format.substr(0, pos) + std::to_string(arg);
        result += FormatMessage(format.substr(pos + 2), args...);
        return result;
    }

    std::string EscapeMessage(const std::string& message) const {
        std::string escaped_message;
        escaped_message.reserve(message.size());
        for (char c : message) {
            if (c == '\n') {
                escaped_message += "\\n";
            } else if (c == '\r') {
                escaped_message += "\\r";
            } else if (c == '\t') {
                escaped_message += "\\t";
            } else if (c == '\b') {
                escaped_message += "\\b";
            } else if (c == '\f') {
                escaped_message += "\\f";
            } else if (c == '\\') {
                escaped_message += "\\\\";
            } else if (c == '\"') {
                escaped_message += "\\\"";
            } else {
                escaped_message += c;
            }
        }
        return escaped_message;
    }

    void ShrinkLogFile() {
        if (!file_output_) return;
        log_file_.close();
        std::ifstream input_file(file_path_);
        std::string content((std::istreambuf_iterator<char>(input_file)),
            (std::istreambuf_iterator<char>()));
        std::ofstream output_file(file_path_, std::ios::out | std::ios::trunc);
        output_file << content.substr(content.size() / 2);
        log_file_.open(file_path_, std::ios::out | std::ios::app);
    }
};

const std::unordered_setLogger::MessageType Logger::kDefaultEnabledTypes{
    Logger::MessageType::DEBUG, Logger::MessageType::INFO,
        Logger::MessageType::WARNING, Logger::MessageType::ERROR,
        Logger::MessageType::FATAL};