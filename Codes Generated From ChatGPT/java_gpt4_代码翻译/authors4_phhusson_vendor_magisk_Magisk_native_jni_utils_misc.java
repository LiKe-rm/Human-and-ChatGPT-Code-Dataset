import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.function.*;
import java.util.stream.*;

public class MiscUtils {
    public static int getShellUid() {
        ProcessBuilder builder = new ProcessBuilder("id", "-u", "shell");
        builder.redirectErrorStream(true);

        try {
            Process process = builder.start();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                return Integer.parseInt(reader.readLine().trim());
            } finally {
                process.waitFor();
            }
        } catch (IOException | InterruptedException e) {
            return 2000;
        }
    }

    public static String generateRandomString(int maxLength, boolean variableLength) {
        int length = variableLength ? ThreadLocalRandom.current().nextInt(maxLength / 2, maxLength) : maxLength;
        return ThreadLocalRandom.current().ints(length, 0, 62)
                .mapToObj(i -> Character.toString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".charAt(i)))
                .collect(Collectors.joining());
    }

    public static boolean endsWith(String s1, String s2) {
        return s1.endsWith(s2);
    }

    public static String rtrim(String str) {
        int i = str.length() - 1;
        while (i >= 0 && Character.isWhitespace(str.charAt(i))) {
            i--;
        }
        return str.substring(0, i + 1);
    }

    public static int parseInt(String s) {
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    public static int executeCommand(String... command) {
        try {
            ProcessBuilder builder = new ProcessBuilder(command);
            Process process = builder.start();
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            return -1;
        }
    }

    public static int executeCommandAndRedirectOutput(String outputFile, String... command) {
        try {
            ProcessBuilder builder = new ProcessBuilder(command);
            builder.redirectOutput(new File(outputFile));
            Process process = builder.start();
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            return -1;
        }
    }

    public static void executeCommandAsync(Consumer<Integer> callback, String... command) {
        CompletableFuture.supplyAsync(() -> executeCommand(command))
                .thenAccept(callback);
    }

    public static String executeCommandAndGetOutput(String... command) {
        try {
            ProcessBuilder builder = new ProcessBuilder(command);
            builder.redirectErrorStream(true);
            Process process = builder.start();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String output = reader.lines().collect(Collectors.joining("\n"));
                process.waitFor();
                return output;
            }
        } catch (IOException | InterruptedException e) {
            return null;
        }
    }

    public static void main(String[] args) {
        System.out.println("Shell UID: " + getShellUid());
        System.out.println("Random string: " + generateRandomString(10, true));
        System.out.println("Ends with: " + endsWith("hello.txt", ".txt"));
        System.out.println("Right trim: '" + rtrim("  hello world  ") + "'");
        System.out.println("Parse int: " + parseInt("42"));

        System.out.println("Executing 'ls':");
        System.out.println(executeCommandAndGetOutput("ls"));

        System.out.println("Executing 'ls' and redirecting output:");
        String outputFileName = "ls_output.txt";
        executeCommandAndRedirectOutput(outputFileName, "ls");
        System.out.println("Output saved to: " + outputFileName);
        System.out.println("Executing 'ls' asynchronously:");
        executeCommandAsync(exitValue -> System.out.println("Async 'ls' command finished with exit value: " + exitValue), "ls");
    }
}    