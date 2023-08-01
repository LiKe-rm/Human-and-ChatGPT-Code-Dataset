import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Encoder {
    private final FileOutputStream file;
    private final double sampleRate;
    private int samples;
    private int bits;

    public Encoder(FileOutputStream file, int sampleRate) {
        this.file = file;
        this.sampleRate = sampleRate;
        this.samples = 0;
        this.bits = 0;
    }

    public void encode(String text) throws IOException {
        for (int i = 0; i < text.length(); i++) {
            encodeByte((byte) text.charAt(i));
        }
    }

    public void encodeByte(byte b) throws IOException {
        for (int i = 0; i < 8; i++) {
            encodeBit(b & 1);
            b >>= 1;
        }
    }

    public void encodeBit(int b) throws IOException {
        bits++;
        int cycles = b != 0 ? 4 : 3;
        double f = 2 * Math.PI * (cycles / 1920e-6);

        while (samples < bits * sampleRate * 1920e-6) {
            short s = (short) (32767 * Math.sin(samples / sampleRate * f));
            ByteBuffer buffer = ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort(s);
            file.write(buffer.array());
            samples++;
        }
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: java Encoder <output_file> <text>");
            System.exit(1);
        }

        try (FileOutputStream file = new FileOutputStream(args[0])) {
            Encoder encoder = new Encoder(file, 11025);
            encoder.encode("\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB\u00AB");
            encoder.encode(args[1]);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
    }
}
