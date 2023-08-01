import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.time.LocalDateTime;
import java.time.ZoneId;

public class Log {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.printf("usage: %s dir%n", Log.class.getSimpleName());
            System.exit(1);
        }
        String dir = args[0];
        FileOutputStream log = null;
        int lastHour = -1;

        try (InputStream stdin = new BufferedInputStream(System.in)) {
            byte[] buffer = new byte[4096];

            while (true) {
                int bytesRead = stdin.read(buffer);
                if (bytesRead == -1) {
                    System.err.println("log: eof on input");
                    break;
                }

                int currentHour = LocalDateTime.now(ZoneId.of("UTC")).getHour();

                if (currentHour != lastHour) {
                    if (log != null) {
                        log.close();
                    }

                    File oldFile = new File(dir, String.format("NWR-%02d.raw", (currentHour + 24 - 3) % 24));
                    oldFile.delete();

                    File newFile = new File(dir, String.format("NWR-%02d.raw", currentHour));
                    log = new FileOutputStream(newFile, lastHour != -1);

                    lastHour = currentHour;
                }

                log.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        } finally {
            if (log != null) {
                try {
                    log.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
