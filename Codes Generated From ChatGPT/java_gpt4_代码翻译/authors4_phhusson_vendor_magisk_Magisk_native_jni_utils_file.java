import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;
import java.util.function.*;

public class FileUtils {
    public static void copyAttributes(Path src, Path dest) throws IOException {
        BasicFileAttributes srcAttrs = Files.readAttributes(src, BasicFileAttributes.class);
        FileTime lastModifiedTime = srcAttrs.lastModifiedTime();
        FileTime creationTime = srcAttrs.creationTime();
        FileTime lastAccessTime = srcAttrs.lastAccessTime();
        
        Files.setAttribute(dest, "basic:lastModifiedTime", lastModifiedTime);
        Files.setAttribute(dest, "basic:creationTime", creationTime);
        Files.setAttribute(dest, "basic:lastAccessTime", lastAccessTime);
    }

    public static void copyDirectory(Path src, Path dest) throws IOException {
        Files.walkFileTree(src, new SimpleFileVisitor<Path>() {
            @Override
            public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                Path targetDir = dest.resolve(src.relativize(dir));
                Files.createDirectories(targetDir);
                copyAttributes(dir, targetDir);
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                Path targetFile = dest.resolve(src.relativize(file));
                Files.copy(file, targetFile, StandardCopyOption.REPLACE_EXISTING);
                copyAttributes(file, targetFile);
                return FileVisitResult.CONTINUE;
            }
        });
    }

    public static void moveDirectory(Path src, Path dest) throws IOException {
        copyDirectory(src, dest);
        deleteDirectory(src);
    }

    public static void deleteDirectory(Path path) throws IOException {
        Files.walkFileTree(path, new SimpleFileVisitor<Path>() {
            @Override
            public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                Files.delete(file);
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                Files.delete(dir);
                return FileVisitResult.CONTINUE;
            }
        });
    }

    public static void readFileLines(String filename, Consumer<String> action) {
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                action.accept(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void parseProperties(String filename, BiConsumer<String, String> action) {
        readFileLines(filename, line -> {
            line = line.trim();
            if (!line.startsWith("#")) {
                int eqPos = line.indexOf('=');
                if (eqPos > 0) {
                    String key = line.substring(0, eqPos).trim();
                    String value = line.substring(eqPos + 1).trim();
                    action.accept(key, value);
                }
            }
        });
    }

    public static void main(String[] args) {
        String src = "src";
        String dest = "dest";
        try {
            copyDirectory(Paths.get(src), Paths.get(dest));
        } catch (IOException e) {
            e.printStackTrace();
        }

        readFileLines("example.txt", System.out::println);

        parseProperties("example.properties", (key, value) -> {
            System.out.println("Key: " + key + ", Value: " + value);
        });
    }
}
