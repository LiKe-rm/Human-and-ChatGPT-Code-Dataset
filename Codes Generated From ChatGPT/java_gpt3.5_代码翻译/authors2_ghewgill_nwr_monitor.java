import java.io.*;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.LinkedList;

public class Monitor {

    private static LinkedList<EasMessage> messages = new LinkedList<>();

    private static void writeTitle() {
        StringBuilder title = new StringBuilder();

        for (EasMessage message : messages) {
            if (title.length() > 0) {
                title.append(" / ");
            }
            title.append(message.eventDesc);
            title.append(" until ").append(LocalDateTime.ofInstant(message.purge.toInstant(), ZoneId.systemDefault()).format(DateTimeFormatter.ofPattern("HH:mm")));
        }

        if (title.length() == 0) {
            System.out.println("Weather Radio");
        } else {
            System.out.println(title);
        }
        System.out.flush();
    }

    private static void easActivate(String s) {
        EasMessage message = EasDecode.decode(s);
        if (message == null) {
            System.out.printf("bad eas header: %s%n", s);
            return;
        }
        messages.addFirst(message);
        writeTitle();
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java Monitor <file>");
            System.exit(1);
        }

        try (InputStream inputStream = args[0].equals("-") ? System.in : new FileInputStream(args[0])) {
            EasDemodulator demodulator = new EasDemodulator();
            demodulator.setActivateCallback(Monitor::easActivate);
            writeTitle();

            byte[] buf = new byte[4096];
            int bytesRead;

            while ((bytesRead = inputStream.read(buf)) != -1) {
                float[] fbuf = new float[bytesRead / 2];
                for (int i = 0; i < bytesRead / 2; i++) {
                    fbuf[i] = (short) (((buf[i * 2 + 1] & 0xFF) << 8) | (buf[i * 2] & 0xFF)) * (1.0f / 32768.0f);
                }
                demodulator.demodulate(fbuf);

                messages.removeIf(message -> message.purge.getTime() <= System.currentTimeMillis());
                writeTitle();
            }
        } catch (IOException e) {
            System.err.println("monitor: error on input");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
