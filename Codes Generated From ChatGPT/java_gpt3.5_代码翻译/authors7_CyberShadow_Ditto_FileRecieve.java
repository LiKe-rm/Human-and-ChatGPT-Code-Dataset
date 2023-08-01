import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class FileReceive {
    private final String receivingFromIP;
    private final Socket socket;
    private final FileTransferProgressListener progressListener;
    private final List<Path> receivedFiles = new ArrayList<>();

    public FileReceive(Socket socket, String receivingFromIP, FileTransferProgressListener progressListener) {
        this.socket = socket;
        this.receivingFromIP = receivingFromIP;
        this.progressListener = progressListener;
    }

    public boolean receiveFiles() throws IOException {
        DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
        int numFiles;
        boolean userCanceled = false;

        while (true) {
            SendInfo info = SendInfo.readFromStream(dataInputStream);
            if (info == null) {
                break;
            }

            switch (info.getType()) {
                case START:
                    numFiles = info.getParameter1();
                    progressListener.setNumFiles(numFiles);
                    progressListener.logMessage(String.format("Start receiving files. File count: %d", numFiles));
                    break;

                case DATA_START:
                    String fileName = new String(info.getDescription(), StandardCharsets.UTF_8);
                    int filesReceived = progressListener.incrementAllFiles();
                    progressListener.setMessage(String.format("Copying file %d of %d", filesReceived, numFiles));
                    progressListener.setFileMessage(String.format("Copying %s", fileName));

                    if (progressListener.isCancelled()) {
                        userCanceled = true;
                        break;
                    }

                    long fileSize = info.getParameter1();
                    progressListener.logMessage(String.format("START of receiving the file %s, size: %d, file %d of %d",
                            fileName, fileSize, filesReceived, numFiles));

                    boolean receiveFileResult = receiveFileData(fileSize, fileName);
                    if (!receiveFileResult) {
                        userCanceled = true;
                        progressListener.logMessage(String.format("Error receiving the file %s", fileName));
                        break;
                    }

                    progressListener.logMessage(String.format("END of receiving the file %s, size: %d", fileName, fileSize));
                    break;

                case DATA_END:
                    break;

                case END:
                    return !userCanceled;

                default:
                    progressListener.logMessage("::ERROR unknown action type exiting");
                    return false;
            }

            if (userCanceled) {
                break;
            }
        }

        return false;
    }

    private boolean receiveFileData(long fileSize, String fileName) throws IOException {
        Path remoteFilesPath = Paths.get(System.getProperty("user.home"), "remote_files", receivingFromIP);
        Files.createDirectories(remoteFilesPath);
        Path filePath = remoteFilesPath.resolve(fileName);

        try (OutputStream outputStream = Files.newOutputStream(filePath);
             DataInputStream dataInputStream = new DataInputStream(socket.getInputStream())) {

            byte[] buffer = new byte[4096];
            long bytesRead = 0;
            int prevPercent = 0;

            while (bytesRead < fileSize) {
                int bytesToRead = (int) Math.min(buffer.length, fileSize - bytesRead);
                int read = dataInputStream.read(buffer, 0, bytesToRead);
                if (read == -1) {
                    break;
                }

                outputStream.write(buffer, 0, read);
                bytesRead += read;

                int percent = (int) (((double) bytesRead / fileSize) * 100);
                if (percent - prevPercent > 5) {
                    progressListener.setSingleFilePos(percent);
                    if (progressListener.isCancelled()) {
                        return false;
                    }
                    prevPercent = percent;
                }
            }

            if (bytesRead >= fileSize) {
                progressListener.setSingleFilePos(100);
                receivedFiles.add(filePath);
                return true;
            } else {
                return false;
            }
        }
    }

    public List<Path> getReceivedFiles() {
        return receivedFiles;
    }

    public interface FileTransferProgressListener {
        void setNumFiles(int numFiles);

        int incrementAllFiles();

        void setMessage(String message);

        void setFileMessage(String fileMessage);

        void setSingleFilePos(int percent);

        boolean isCancelled();

        void logMessage(String message);
    }
}
