import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipException;

public class LogFile {

    private String filename;
    private BufferedReader reader;
    private InputStream fileInputStream;
    private String line;
    private long timestamp;

    public LogFile(String filename) throws IOException {
        this.filename = filename;
        openLogFile();
        if (!nextLine()) {
            closeLogFile();
            throw new IOException("Error trying to read an initial record.");
        }
        closeLogFile();
    }

    private void openLogFile() throws IOException {
        fileInputStream = new FileInputStream(filename);

        if (isGzipFile()) {
            fileInputStream = new GZIPInputStream(fileInputStream);
        }

        reader = new BufferedReader(new InputStreamReader(fileInputStream));
    }

    private boolean isGzipFile() {
        try {
            byte[] buffer = new byte[2];
            int bytesRead = fileInputStream.read(buffer);
            if (bytesRead < 2) {
                return false;
            }
            int magic = ((buffer[0] & 0xff) << 8) | (buffer[1] & 0xff);
            fileInputStream.reset();
            return magic == GZIPInputStream.GZIP_MAGIC;
        } catch (IOException e) {
            return false;
        }
    }

    private long parseTimestamp() throws ParseException {
        if (line == null || line.isEmpty()) {
            return -1;
        }

        int openBracketIndex = line.indexOf('[');
        if (openBracketIndex == -1) {
            return -1;
        }

        int closeBracketIndex = line.indexOf(']', openBracketIndex);
        if (closeBracketIndex == -1) {
            return -1;
        }

        String dateString = line.substring(openBracketIndex + 1, closeBracketIndex);
        SimpleDateFormat format = new SimpleDateFormat("dd/MMM/yyyy:HH:mm:ss Z", Locale.ENGLISH);
        Date date = format.parse(dateString);

        return date.getTime();
    }

    public boolean nextLine() throws IOException {
        line = reader.readLine();
        if (line == null) {
            return false;
        }

        try {
            timestamp = parseTimestamp();
            return timestamp != -1;
        } catch (ParseException e) {
            return false;
        }
    }

    public void writeLine(BufferedWriter writer) throws IOException {
        if (reader == null) {
            openLogFile();
            nextLine();
        }
        writer.write(line);
    }

    private void closeLogFile() throws IOException {
        if (reader != null) {
            reader.close();
        }
        if (fileInputStream != null) {
            fileInputStream.close();
        }
        line = null;
        timestamp = -1;
    }

    public static void main(String[] args) {
        try {
            LogFile logFile = new LogFile("path/to/your/logfile.log");
            BufferedWriter writer = Files.newBufferedWriter(Paths.get("path/to/output.txt"));
            logFile.writeLine(writer);
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
