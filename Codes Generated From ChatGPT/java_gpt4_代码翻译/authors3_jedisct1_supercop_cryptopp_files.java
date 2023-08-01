import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileUtility {

    public static void main(String[] args) throws IOException {
        // Test
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        FileSource fileSource = new FileSource(inputFile);
        byte[] data = fileSource.readAllBytes();
        FileSink fileSink = new FileSink(outputFile);
        fileSink.write(data);
        fileSink.close();
    }

}

class FileSource {
    private final BufferedInputStream inputStream;

    public FileSource(String fileName) throws FileNotFoundException {
        inputStream = new BufferedInputStream(new FileInputStream(fileName));
    }

    public byte[] readAllBytes() throws IOException {
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        int bytesRead;
        byte[] chunk = new byte[4096];
        while ((bytesRead = inputStream.read(chunk, 0, chunk.length)) != -1) {
            buffer.write(chunk, 0, bytesRead);
        }
        buffer.flush();
        return buffer.toByteArray();
    }

    public void close() throws IOException {
        inputStream.close();
    }
}

class FileSink {
    private final BufferedOutputStream outputStream;

    public FileSink(String fileName) throws IOException {
        outputStream = new BufferedOutputStream(Files.newOutputStream(Paths.get(fileName), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING));
    }

    public void write(byte[] data) throws IOException {
        outputStream.write(data);
    }

    public void close() throws IOException {
        outputStream.flush();
        outputStream.close();
    }
}
