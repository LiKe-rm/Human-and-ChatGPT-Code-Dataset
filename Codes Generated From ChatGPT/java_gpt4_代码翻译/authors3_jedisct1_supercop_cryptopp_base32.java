import java.util.HashMap;
import java.util.Map;

public class Base32 {

    private static final String STD_UPPER = "ABCDEFGHIJKMNPQRSTUVWXYZ23456789";
    private static final String STD_LOWER = "abcdefghijkmnpqrstuvwxyz23456789";
    private static final String HEX_UPPER = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    private static final String HEX_LOWER = "0123456789abcdefghijklmnopqrstuv";

    private static final int[] ARRAY = new int[256];
    private static final int[] HEX_ARRAY = new int[256];

    static {
        for (int i = 0; i < 256; i++) {
            ARRAY[i] = -1;
            HEX_ARRAY[i] = -1;
        }
        for (int i = 0; i < STD_UPPER.length(); i++) {
            ARRAY[STD_UPPER.charAt(i)] = i;
            ARRAY[STD_LOWER.charAt(i)] = i;
        }
        for (int i = 0; i < HEX_UPPER.length(); i++) {
            HEX_ARRAY[HEX_UPPER.charAt(i)] = i;
            HEX_ARRAY[HEX_LOWER.charAt(i)] = i;
        }
    }

    public static String encode(byte[] input, boolean hex, boolean uppercase) {
        StringBuilder sb = new StringBuilder();
        int log2Base = 5;
        String alphabet = (hex ? (uppercase ? HEX_UPPER : HEX_LOWER) : (uppercase ? STD_UPPER : STD_LOWER));

        int buffer = 0;
        int bitsLeft = 0;
        for (byte b : input) {
            buffer = (buffer << 8) | (b & 0xFF);
            bitsLeft += 8;
            while (bitsLeft >= log2Base) {
                int index = (buffer >>> (bitsLeft - log2Base)) & ((1 << log2Base) - 1);
                sb.append(alphabet.charAt(index));
                bitsLeft -= log2Base;
            }
        }
        if (bitsLeft > 0) {
            int index = (buffer << (log2Base - bitsLeft)) & ((1 << log2Base) - 1);
            sb.append(alphabet.charAt(index));
        }
        return sb.toString();
    }

    public static byte[] decode(String input, boolean hex) {
        int[] lookup = hex ? HEX_ARRAY : ARRAY;
        int log2Base = 5;

        int buffer = 0;
        int bitsLeft = 0;
        int outputLen = (input.length() * log2Base + 7) / 8;
        byte[] output = new byte[outputLen];
        int outIndex = 0;

        for (char c : input.toCharArray()) {
            int value = lookup[c];
            if (value < 0) {
                throw new IllegalArgumentException("Invalid character in input: " + c);
            }
            buffer = (buffer << log2Base) | value;
            bitsLeft += log2Base;
            if (bitsLeft >= 8) {
                output[outIndex++] = (byte) ((buffer >>> (bitsLeft - 8)) & 0xFF);
                bitsLeft -= 8;
            }
        }
        return output;
    }
}
