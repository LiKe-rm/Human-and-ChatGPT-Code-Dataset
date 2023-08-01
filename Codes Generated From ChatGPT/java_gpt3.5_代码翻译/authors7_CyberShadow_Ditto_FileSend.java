import java.io.*;
import java.net.Socket;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;

public class FileSend {
    private static final int CHUNK_WRITE_SIZE = 4096;

    private Send send;

    public FileSend() {
        this.send = new Send();
    }

    public boolean sendClientFiles(Socket socket, List<Path> files) {
        if (files == null || files.isEmpty()) {
            System.out.println("::ERROR SendClientFiles called with an empty file list");
            return false;
        }

        send.setSocket(socket);

        SendInfo info = new SendInfo();
        boolean result = false;

        List<Path> copyFiles = new ArrayList<>();
        for (Path file : files) {
            if (!Files.isDirectory(file)) {
                copyFiles.add(file);
            }
        }

        info.setParameter1(copyFiles.size());
        if (info.getParameter1() > 0) {
            if (send.sendSendData(info, MyEnums.START)) {
                for (int i = 0; i < info.getParameter1(); i++) {
                    sendFile(copyFiles.get(i));
                }

                if (send.sendSendData(info, MyEnums.END)) {
                    result = true;
                }
            }
        }

        return result;
    }

    private boolean sendFile(Path filePath) {
        File file = filePath.toFile();
        boolean result = false;
        SendInfo info = new SendInfo();

        byte[] buffer = new byte[CHUNK_WRITE_SIZE];

        try (FileInputStream fis = new FileInputStream(file)) {
            info.setDesc(filePath.toString());
            info.setParameter1((int) file.length());

            if (send.sendSendData(info, MyEnums.DATA_START)) {
                int bytesRead;
                boolean error = false;

                do {
                    bytesRead = fis.read(buffer);

                    if (bytesRead < 0) {
                        break;
                    }

                    if (!send.sendExactSize(buffer, bytesRead)) {
                        System.out.println("Error sending SendExactSize in SendFile");
                        error = true;
                        break;
                    }

                } while (bytesRead >= CHUNK_WRITE_SIZE);

                if (!error) {
                    if (send.sendSendData(info, MyEnums.DATA_END)) {
                        result = true;
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Error in SendFile: " + e.getMessage());
        }

        return result;
    }
}
