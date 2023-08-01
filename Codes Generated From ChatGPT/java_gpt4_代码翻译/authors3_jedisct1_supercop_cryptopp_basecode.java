import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class BaseNCodec {
    private final int bitsPerChar;
    private final byte[] alphabet;
    private final int[] lookup;
    private int bytePos;
    private int bitPos;
    private final int outputBlockSize;
    private final byte[] outBuf;
    
    public BaseNCodec(String alphabet, int bitsPerChar) {
        this.alphabet = alphabet.getBytes(StandardCharsets.UTF_8);
        this.bitsPerChar = bitsPerChar;

        bytePos = bitPos = 0;

        int i = 8;
        while (i % bitsPerChar != 0) {
            i += 8;
        }
        outputBlockSize = i / bitsPerChar;
        outBuf = new byte[outputBlockSize];

        lookup = new int[256];
        Arrays.fill(lookup, -1);
        for (int j = 0; j < alphabet.length(); j++) {
            lookup[alphabet.charAt(j)] = j;
        }
    }

    public byte[] encode(byte[] input) {
        // Encoding logic here
    }

    public byte[] decode(byte[] input) {
        // Decoding logic here
    }

    public static void main(String[] args) {
        BaseNCodec baseNCodec = new BaseNCodec("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", 6);

        byte[] input = "hello world".getBytes(StandardCharsets.UTF_8);
        byte[] encoded = baseNCodec.encode(input);
        System.out.println(new String(encoded, StandardCharsets.UTF_8));

        byte[] decoded = baseNCodec.decode(encoded);
        System.out.println(new String(decoded, StandardCharsets.UTF_8));
    }
}
