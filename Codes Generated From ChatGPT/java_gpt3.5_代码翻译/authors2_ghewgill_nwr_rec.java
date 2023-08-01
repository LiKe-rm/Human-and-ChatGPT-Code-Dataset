import javax.sound.sampled.*;
import java.io.*;

public class SoundCardRecorder {

    public static void main(String[] args) {
        boolean stereo = false;
        String output = null;

        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-")) {
                if (args[i].equals("-s")) {
                    stereo = true;
                } else {
                    System.err.printf("Unknown option: %s%n", args[i]);
                    System.exit(1);
                }
            } else {
                output = args[i];
                break;
            }
        }

        try {
            OutputStream outputStream = output != null && !output.equals("-")
                    ? new FileOutputStream(output)
                    : System.out;
            recordAudio(outputStream, stereo);
        } catch (IOException e) {
            System.err.println("Error opening file or stream");
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void recordAudio(OutputStream outputStream, boolean stereo) throws IOException {
        AudioFormat format = new AudioFormat(
                AudioFormat.Encoding.PCM_SIGNED, 11025, 16,
                stereo ? 2 : 1, stereo ? 4 : 2, 11025, false);
        TargetDataLine.Info info = new DataLine.Info(TargetDataLine.class, format);

        if (!AudioSystem.isLineSupported(info)) {
            System.err.println("Line not supported");
            System.exit(1);
        }

        try (TargetDataLine line = (TargetDataLine) AudioSystem.getLine(info)) {
            line.open(format);
            line.start();

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = line.read(buffer, 0, buffer.length)) > 0) {
                outputStream.write(buffer, 0, bytesRead);
            }

            line.stop();
        } catch (LineUnavailableException e) {
            System.err.println("Error recording audio");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
