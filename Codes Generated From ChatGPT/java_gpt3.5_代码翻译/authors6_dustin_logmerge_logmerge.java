import java.io.*;
import java.util.*;

public class LogMerge {

    private static PriorityQueue<LogFile> queue = new PriorityQueue<>();

    public static void main(String[] args) {
        testMonthParsing();

        if (args.length > 0) {
            initLogfiles(args);
        } else {
            initLogfilesFromStdin();
        }

        outputLogfiles();
    }

    private static void initLogfiles(String[] filenames) {
        for (String filename : filenames) {
            initLogfile(filename);
        }
    }

    private static void initLogfilesFromStdin() {
        System.out.println("No logfiles given, accepting list from stdin");
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String filename = scanner.nextLine();
            initLogfile(filename);
        }
        scanner.close();
    }

    private static void initLogfile(String filename) {
        try {
            LogFile logFile = new LogFile(filename);
            queue.add(logFile);
        } catch (LogFileException e) {
            System.err.println("*** Error initializing \"" + filename + "\": " + e.getMessage());
        }
    }

    private static void outputLogfiles() {
        int entries = 0;

        while (!queue.isEmpty()) {
            entries++;
            LogFile logFile = queue.poll();
            logFile.writeLine();

            if (logFile.nextLine()) {
                queue.add(logFile);
            } else {
                logFile.close();
            }
        }

        System.err.println("Read " + entries + " entries");
    }

    private static void testMonthParsing() {
        // Implement testMonthParsing() if needed
    }
}
