import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class LuaLogger {
    public enum LogMessageType {
        ENTER,
        LEAVE,
        MESSAGE
    }

    public static class LogMessage {
        public String sender;
        public String category;
        public String message;

        public LogMessage(String sender, String category, String message) {
            this.sender = sender;
            this.category = category;
            this.message = message;
        }
    }

    private static final List<Consumer<LogMessage>> loggers = new ArrayList<>();

    public static int addLogger(Consumer<LogMessage> logger) {
        loggers.add(logger);
        return loggers.size() - 1;
    }

    public static void removeLogger(int loggerIndex) {
        if (loggerIndex >= 0 && loggerIndex < loggers.size()) {
            loggers.set(loggerIndex, null);
        }
    }

    public static void dispatchLog(LogMessageType messageType, LogMessage message) {
        loggers.forEach(logger -> {
            if (logger != null) {
                logger.accept(message);
            }
        });
    }

    public static void log(String message) {
        log("", "", message);
    }

    public static void log(String sender, String message) {
        log(sender, "", message);
    }

    public static void log(String sender, String category, String message) {
        LogMessage logMessage = new LogMessage(sender, category, message);
        dispatchLog(LogMessageType.MESSAGE, logMessage);
    }
}
