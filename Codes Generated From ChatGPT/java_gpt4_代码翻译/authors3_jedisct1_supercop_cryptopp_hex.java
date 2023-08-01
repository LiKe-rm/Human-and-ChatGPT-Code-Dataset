import java.util.HashMap;
import java.util.Map;

public class Hex {

    private static final char[] UPPER_HEX_CHARS = "0123456789ABCDEF".toCharArray();
    private static final char[] LOWER_HEX_CHARS = "0123456789abcdef".toCharArray();
    private static final Map<Character, Integer> DECODING_MAP = createDecodingMap();

    public static String encode(byte[] data, boolean uppercase) {
        char[] hexChars = uppercase ? UPPER_HEX_CHARS : LOWER_HEX_CHARS;
        char[] result = new char[data.length * 2];
        for (int i = 0; i < data.length; i++) {
            int value = data[i] & 0xFF;
            result[i * 2] = hexChars[value >>> 4];
            result[i * 2 + 1] = hexChars[value & 0x0F];
        }
        return new String(result);
    }

    public static byte[] decode(String hexString) {
        if (hexString.length() % 2 != 0) {
            throw new IllegalArgumentException("Invalid hex string length");
        }

        char[] chars = hexString.toCharArray();
        byte[] result = new byte[chars.length / 2];
        for (int i = 0; i < chars.length; i += 2) {
            int highNibble = DECODING_MAP.getOrDefault(chars[i], -1);
            int lowNibble = DECODING_MAP.getOrDefault(chars[i + 1], -1);
            if (highNibble == -1 || lowNibble == -1) {
                throw new IllegalArgumentException("Invalid hex characters");
            }
            result[i / 2] = (byte) ((highNibble << 4) | lowNibble);
        }
        return result;
    }

    private static Map<Character, Integer> createDecodingMap() {
        Map<Character, Integer> map = new HashMap<>();
        for (int i = 0; i < 10; i++) {
            map.put((char) ('0' + i), i);
        }
        for (int i = 0; i < 6; i++) {
            map.put((char) ('A' + i), 10 + i);
            map.put((char) ('a' + i), 10 + i);
        }
        return map;
    }

}
