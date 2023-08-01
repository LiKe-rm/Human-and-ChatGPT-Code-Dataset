import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Base64 {

    private static final char[] table_b2a_base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
            .toCharArray();

    private static final int[] table_a2b_base64 = new int[128];

    private static final char base64Pad = '=';

    static {
        Arrays.fill(table_a2b_base64, -1);
        for (int i = 0; i < table_b2a_base64.length; i++) {
            table_a2b_base64[table_b2a_base64[i]] = i;
        }
        table_a2b_base64[base64Pad] = 0;
    }

    public static String base64FromBytes(List<Byte> bytes) {
        StringBuilder result = new StringBuilder();
        int buffer = 0;
        int bitsInBuffer = 0;

        for (Byte b : bytes) {
            buffer = (buffer << 8) | (b & 0xff);
            bitsInBuffer += 8;

            while (bitsInBuffer >= 6) {
                int theseBits = (buffer >> (bitsInBuffer - 6)) & 0x3f;
                bitsInBuffer -= 6;
                result.append(table_b2a_base64[theseBits]);
            }
        }
        if (bitsInBuffer > 0) {
            buffer <<= (6 - bitsInBuffer);
            int theseBits = buffer & 0x3f;
            result.append(table_b2a_base64[theseBits]);
            result.append(base64Pad);
        }

        return result.toString();
    }

    public static List<Byte> bytesFromBase64(String base64) {
        List<Byte> result = new ArrayList<>();
        int buffer = 0;
        int bitsInBuffer = 0;

        for (int i = 0; i < base64.length(); i++) {
            char c = base64.charAt(i);
            if (c == '\r' || c == '\n' || c == ' ') {
                continue;
            }

            if (c == base64Pad) {
                bitsInBuffer = 0;
            } else {
                int value = table_a2b_base64[c & 0x7f];
                if (value == -1) {
                    throw new IllegalArgumentException("Contains non-base64 character with ASCII code: " + (int) c);
                }

                buffer = (buffer << 6) | value;
                bitsInBuffer += 6;

                if (bitsInBuffer >= 8) {
                    int byteValue = (buffer >> (bitsInBuffer - 8)) & 0xff;
                    bitsInBuffer -= 8;
                    result.add((byte) byteValue);
                }
            }
        }
        if (bitsInBuffer > 0) {
            throw new IllegalArgumentException("Not a multiple of 4 characters");
        }

        return result;
    }

    public static void main(String[] args) {
        String testString = "Hello, World!";
        List<Byte> byteList = testString.chars().mapToObj(c -> (byte) c).collect(Collectors.toList());
        String encoded = base64FromBytes(byteList);
        System.out.println("Encoded: " + encoded);

        List<Byte> decodedBytes = bytesFromBase64(encoded);
        String decodedString = decodedBytes.stream().map(b -> (char) (b & 0xff)).collect(Collectors.joining());
        System.out.println("Decoded: " + decodedString);
    }
}