import javax.sound.sampled.*;
import java.io.*;

public class SoundCardPlayer {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java SoundCardPlayer <file>");
            System.exit(1);
        }

        try {
            InputStream inputStream = args[0].equals("-") ? System.in : new FileInputStream(args[0]);
            playAudio(inputStream);
        } catch (IOException e) {
            System.err.println("Error opening file or stream");
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void playAudio(InputStream inputStream) throws IOException {
        AudioFormat format = new AudioFormat(AudioFormat.Encoding.PCM_SIGNED, 11025, 16, 1, 2, 11025, false);
        SourceDataLine.Info info = new DataLine.Info(SourceDataLine.class, format);

        if (!AudioSystem.isLineSupported(info)) {
            System.err.println("Line not supported");
            System.exit(1);
        }

        try (SourceDataLine line = (SourceDataLine) AudioSystem.getLine(info)) {
            line.open(format);
            line.start();

            byte[] buffer = new byte[4096];
            int bytesRead;
            int totalBytes = 0;

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                line.write(buffer, 0, bytesRead);
                totalBytes += bytesRead;
                System.out.printf("\r%d", totalBytes);
                System.out.flush();
            }

            line.drain();
            line.stop();
            System.out.println();
        } catch (LineUnavailableException e) {
            System.err.println("Error playing audio");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
