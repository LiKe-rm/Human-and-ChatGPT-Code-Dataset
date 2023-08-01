import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;
import java.net.*;
import java.util.*;
import java.util.logging.*;

public class XWrap {
    public static void main(String[] args) {
        // Example usage
        try {
            FileInputStream fis = xFileInputStream("sample.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static FileInputStream xFileInputStream(String pathname) throws IOException {
        FileInputStream fis;
        try {
            fis = new FileInputStream(pathname);
        } catch (IOException e) {
            logError("FileInputStream: " + pathname, e);
            throw e;
        }
        return fis;
    }

    public static FileOutputStream xFileOutputStream(String pathname) throws IOException {
        FileOutputStream fos;
        try {
            fos = new FileOutputStream(pathname);
        } catch (IOException e) {
            logError("FileOutputStream: " + pathname, e);
            throw e;
        }
        return fos;
    }

    public static RandomAccessFile xRandomAccessFile(String pathname, String mode) throws IOException {
        RandomAccessFile raf;
        try {
            raf = new RandomAccessFile(pathname, mode);
        } catch (IOException e) {
            logError("RandomAccessFile: " + pathname, e);
            throw e;
        }
        return raf;
    }

    public static BufferedReader xBufferedReader(String pathname) throws IOException {
        BufferedReader br;
        try {
            br = Files.newBufferedReader(Path.of(pathname));
        } catch (IOException e) {
            logError("BufferedReader: " + pathname, e);
            throw e;
        }
        return br;
    }

    public static BufferedWriter xBufferedWriter(String pathname) throws IOException {
        BufferedWriter bw;
        try {
            bw = Files.newBufferedWriter(Path.of(pathname));
        } catch (IOException e) {
            logError("BufferedWriter: " + pathname, e);
            throw e;
        }
        return bw;
    }

    public static Path xCreateDirectories(String pathname) throws IOException {
        Path path;
        try {
            path = Files.createDirectories(Path.of(pathname));
        } catch (IOException e) {
            logError("CreateDirectories: " + pathname, e);
            throw e;
        }
        return path;
    }

    public static Path xCreateDirectory(String pathname) throws IOException {
        Path path;
        try {
            path = Files.createDirectory(Path.of(pathname));
        } catch (IOException e) {
            logError("CreateDirectory: " + pathname, e);
            throw e;
        }
        return path;
    }

    public static void xDelete(Path path) throws IOException {
        try {
            Files.delete(path);
        } catch (IOException e) {
            logError("Delete: " + path, e);
            throw e;
        }
    }

    public static void xMove(Path source, Path target, CopyOption... options) throws IOException {
        try {
            Files.move(source, target, options);
        } catch (IOException e) {
            logError("Move: " + source + " -> " + target, e);
            throw e;
        }
    }

    public static void xCopy(Path source, Path target, CopyOption... options) throws IOException {
        try {
            Files.copy(source, target, options);
        } catch (IOException e) {
            logError("Copy: " + source + " -> " + target, e);
            throw e;
        }
    }

    public static BasicFileAttributes xReadAttributes(Path path) throws IOException {
        BasicFileAttributes attrs;
        try {
            attrs = Files.readAttributes(path, BasicFileAttributes.class);
        } catch (IOException e) {
            logError("Copy: " + source + " -> " + target, e);
            throw e;
        }
    }
}

public class XWrap1 {
    private static final Logger LOGGER = Logger.getLogger(XWrap.class.getName());

    public static FileInputStream xFileInputStream(String pathname) {
        try {
            return new FileInputStream(pathname);
        } catch (FileNotFoundException e) {
            LOGGER.log(Level.SEVERE, "FileInputStream: " + pathname, e);
            return null;
        }
    }

    public static FileOutputStream xFileOutputStream(String pathname, boolean append) {
        try {
            return new FileOutputStream(pathname, append);
        } catch (FileNotFoundException e) {
            LOGGER.log(Level.SEVERE, "FileOutputStream: " + pathname, e);
            return null;
        }
    }

    public static FileReader xFileReader(String pathname) {
        try {
            return new FileReader(pathname);
        } catch (FileNotFoundException e) {
            LOGGER.log(Level.SEVERE, "FileReader: " + pathname, e);
            return null;
        }
    }

    public static FileWriter xFileWriter(String pathname, boolean append) {
        try {
            return new FileWriter(pathname, append);
        } catch (IOException e) {
            LOGGER.log(Level.SEVERE, "FileWriter: " + pathname, e);
            return null;
        }
    }

    // ... Add more x-prefixed functions

    public static void main(String[] args) {
        // Example usage
        FileInputStream fis = xFileInputStream("test.txt");
        // ... Perform operations
    }
}
