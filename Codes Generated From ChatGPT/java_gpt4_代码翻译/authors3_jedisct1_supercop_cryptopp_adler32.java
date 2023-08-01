import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Adler32 {

    private static final int BASE = 65521;

    private int s1;
    private int s2;

    public Adler32() {
        reset();
    }

    public void update(byte[] input) {
        int length = input.length;

        int s1 = this.s1;
        int s2 = this.s2;

        if (length % 8 != 0) {
            do {
                s1 += input[input.length - length] & 0xFF;
                s2 += s1;
                length--;
            } while (length % 8 != 0);

            if (s1 >= BASE)
                s1 -= BASE;
            s2 %= BASE;
        }

        while (length > 0) {
            for (int i = 0; i < 8; i++) {
                s1 += input[input.length - length] & 0xFF;
                s2 += s1;
                length--;
            }

            if (s1 >= BASE)
                s1 -= BASE;
            if (length % 0x8000 == 0)
                s2 %= BASE;
        }

        assert s1 < BASE;
        assert s2 < BASE;

        this.s1 = (short) s1;
        this.s2 = (short) s2;
    }

    public byte[] truncatedFinal(int size) {
        if (size < 0 || size > 4) {
            throw new IllegalArgumentException("Invalid truncated size");
        }

        ByteBuffer buffer = ByteBuffer.allocate(4).order(ByteOrder.BIG_ENDIAN);
        buffer.putShort((short) s2);
        buffer.putShort((short) s1);
        byte[] hash = buffer.array();

        reset();

        byte[] result = new byte[size];
        System.arraycopy(hash, 0, result, 0, size);
        return result;
    }

    private void reset() {
        s1 = 1;
        s2 = 0;
    }

    public static void main(String[] args) {
        Adler32 adler32 = new Adler32();
        byte[] input = "Hello, World!".getBytes();
        adler32.update(input);
        byte[] hash = adler32.truncatedFinal(4);

        System.out.println("Adler32 hash: " + bytesToHex(hash));
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder builder = new StringBuilder();
        for (byte b : bytes) {
            builder.append(String.format("%02x", b));
        }
        return builder.toString();
    }
}
