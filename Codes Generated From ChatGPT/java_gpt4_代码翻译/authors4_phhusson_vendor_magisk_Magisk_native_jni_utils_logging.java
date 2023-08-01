import java.util.logging.*;

class LoggingExample {
    public enum LogType {
        DEBUG,
        INFO,
        WARN,
        ERROR
    }

    interface LogCallback {
        void log(String message);
        void exit(int status);
    }

    static class NoOperationCallback implements LogCallback {
        public void log(String message) {}
        public void exit(int status) {}
    }

    static class JavaLoggerCallback implements LogCallback {
        private Logger logger;

        JavaLoggerCallback(String tag, Level level) {
            logger = Logger.getLogger(tag);
            logger.setLevel(level);
        }

        public void log(String message) {
            logger.log(logger.getLevel(), message);
        }

        public void exit(int status) {}
    }

    static class LogHandler {
        private LogCallback debugCallback;
        private LogCallback infoCallback;
        private LogCallback warnCallback;
        private LogCallback errorCallback;

        LogHandler() {
            disableLogging();
        }

        void disableLogging() {
            NoOperationCallback noOp = new NoOperationCallback();
            debugCallback = noOp;
            infoCallback = noOp;
            warnCallback = noOp;
            errorCallback = noOp;
        }

        void enableJavaLogging(String tag) {
            debugCallback = new JavaLoggerCallback(tag, Level.FINE);
            infoCallback = new JavaLoggerCallback(tag, Level.INFO);
            warnCallback = new JavaLoggerCallback(tag, Level.WARNING);
            errorCallback = new JavaLoggerCallback(tag, Level.SEVERE);
        }

        void handleLog(LogType type, String message) {
            switch (type) {
                case DEBUG:
                    debugCallback.log(message);
                    break;
                case INFO:
                    infoCallback.log(message);
                    break;
                case WARN:
                    warnCallback.log(message);
                    break;
                case ERROR:
                    errorCallback.log(message);
                    errorCallback.exit(1);
                    break;
            }
        }
    }

    public static void main(String[] args) {
        LogHandler logHandler = new LogHandler();

        logHandler.disableLogging(); // No logging
        logHandler.handleLog(LogType.DEBUG, "Debug message");

        logHandler.enableJavaLogging("MyTag"); // Java logging
        logHandler.handleLog(LogType.DEBUG, "Debug message");
        logHandler.handleLog(LogType.INFO, "Info message");
        logHandler.handleLog(LogType.WARN, "Warning message");
        logHandler.handleLog(LogType.ERROR, "Error message");
    }
}
