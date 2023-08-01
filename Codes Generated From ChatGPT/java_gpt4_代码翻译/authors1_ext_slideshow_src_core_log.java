import java.io.*;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Log {
    public enum Severity {
        DEBUG, VERBOSE, INFO, WARNING, FATAL
    }

    public interface Destination {
        void write(String content, String decorated);
    }

    public static class FileDestination implements Destination {
        private final BufferedWriter writer;
        private final boolean autoClose;

        public FileDestination(String fileName) throws IOException {
            this.writer = new BufferedWriter(new FileWriter(fileName, true));
            this.autoClose = true;
        }

        public FileDestination(Writer writer) {
            this.writer = new BufferedWriter(writer);
            this.autoClose = false;
        }

        @Override
        public void write(String content, String decorated) {
            try {
                writer.write(decorated);
                writer.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public void close() throws IOException {
            if (autoClose) {
                writer.close();
            }
        }
    }

    private static List<Destination> destinations = new ArrayList<>();

    public static void addDestination(Destination destination) {
        destinations.add(destination);
    }

    public static void message(Severity severity, String format, Object... args) {
        String content = String.format(format, args);
        String decorated = String.format("(%s) [%s] %s", severityString(severity), timestamp(), content);

        for (Destination destination : destinations) {
            destination.write(content, decorated);
        }
    }

    private static String timestamp() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return sdf.format(new Date());
    }

    private static String severityString(Severity severity) {
        switch (severity) {
            case DEBUG:
                return "DD";
            case VERBOSE:
                return "--";
            case INFO:
                return "  ";
            case WARNING:
                return "WW";
            case FATAL:
                return "!!";
            default:
                return null;
        }
    }

    public static void debug(String format, Object... args) {
        message(Severity.DEBUG, format, args);
    }

    public static void verbose(String format, Object... args) {
        message(Severity.VERBOSE, format, args);
    }

    public static void info(String format, Object... args) {
        message(Severity.INFO, format, args);
    }

    public static void warning(String format, Object... args) {
        message(Severity.WARNING, format, args);
    }

    public static void fatal(String format, Object... args) {
        message(Severity.FATAL, format, args);
    }
}