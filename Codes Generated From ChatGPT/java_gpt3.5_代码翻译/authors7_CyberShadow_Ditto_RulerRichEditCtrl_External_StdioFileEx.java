import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class StdioFileEx {
    private static final char UNICODE_BOM = '\uFEFF';

    private File file;
    private RandomAccessFile randomAccessFile;
    private boolean isUnicodeText;

    public StdioFileEx(String fileName, String mode) throws FileNotFoundException {
        file = new File(fileName);
        processFlags(mode);
        randomAccessFile = new RandomAccessFile(file, mode);
    }

    public boolean readString(StringBuilder sb) throws IOException {
        boolean readData;
        if (randomAccessFile.getFilePointer() == 0 && isUnicodeText) {
            randomAccessFile.readChar();
        }

        readData = readLine(sb);

        if (readData) {
            int len = sb.length();
            if (len > 1 && sb.substring(len - 2).equals("\r\n")) {
                sb.setLength(len - 2);
            } else if (len > 0 && (sb.charAt(len - 1) == '\r' || sb.charAt(len - 1) == '\n')) {
                sb.setLength(len - 1);
            }
        }

        return readData;
    }

    public void writeString(String s) throws IOException {
        if (randomAccessFile.getFilePointer() == 0 && isUnicodeText) {
            randomAccessFile.writeChar(UNICODE_BOM);
        }

        if (isUnicodeText) {
            randomAccessFile.writeChars(s);
        } else {
            randomAccessFile.writeBytes(s);
        }
    }

    private void processFlags(String mode) {
        isUnicodeText = mode.equalsIgnoreCase("rw") && isFileUnicode(file);
    }

    private static boolean isFileUnicode(File file) {
        try (FileInputStream fis = new FileInputStream(file);
             InputStreamReader isr = new InputStreamReader(fis, StandardCharsets.UTF_16);
             BufferedReader br = new BufferedReader(isr)) {

            char firstChar = (char) br.read();
            return firstChar == UNICODE_BOM;

        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    private boolean readLine(StringBuilder sb) throws IOException {
        boolean isEndOfLine = false;
        boolean isEndOfFile = false;
        char currentChar;

        while (!isEndOfLine && !isEndOfFile) {
            try {
                currentChar = randomAccessFile.readChar();
            } catch (EOFException e) {
                isEndOfFile = true;
                break;
            }

            if (currentChar == '\n') {
                isEndOfLine = true;
            } else if (currentChar == '\r') {
                isEndOfLine = true;
                if (randomAccessFile.getFilePointer() < randomAccessFile.length()) {
                    char nextChar = randomAccessFile.readChar();
                    if (nextChar != '\n') {
                        randomAccessFile.seek(randomAccessFile.getFilePointer() - 2);
                    }
                }
            } else {
                sb.append(currentChar);
            }
        }

        return sb.length() > 0 || !isEndOfFile;
    }
}
