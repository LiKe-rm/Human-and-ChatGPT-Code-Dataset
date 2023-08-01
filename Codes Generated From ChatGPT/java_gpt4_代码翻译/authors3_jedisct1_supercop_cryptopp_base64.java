import java.util.Arrays;
import java.util.Base64;

public class Base64EncoderDecoder {

    private static final String STD_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    private static final String URL_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    private static final char PADDING = '=';
    private static final int[] STD_LOOKUP_ARRAY = new int[256];
    private static final int[] URL_LOOKUP_ARRAY = new int[256];

    static {
        Arrays.fill(STD_LOOKUP_ARRAY, -1);
        for (int i = 0; i < STD_ALPHABET.length(); i++) {
            STD_LOOKUP_ARRAY[STD_ALPHABET.charAt(i)] = i;
        }

        Arrays.fill(URL_LOOKUP_ARRAY, -1);
        for (int i = 0; i < URL_ALPHABET.length(); i++) {
            URL_LOOKUP_ARRAY[URL_ALPHABET.charAt(i)] = i;
        }
    }

    public static String encodeBase64(String input) {
        return base64Encode(input.getBytes(), STD_ALPHABET);
    }

    public static String encodeBase64Url(String input) {
        return base64Encode(input.getBytes(), URL_ALPHABET);
    }

    private static String base64Encode(byte[] input, String alphabet) {
        Base64.Encoder encoder = Base64.getEncoder();
        String encoded = new String(encoder.encode(input));
        StringBuilder result = new StringBuilder(encoded.length());
        for (int i = 0; i < encoded.length(); i++) {
            char c = encoded.charAt(i);
            if (c == '+') {
                result.append(alphabet.charAt(62));
            } else if (c == '/') {
                result.append(alphabet.charAt(63));
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    public static String decodeBase64(String input) {
        return new String(base64Decode(input, STD_LOOKUP_ARRAY));
    }

    public static String decodeBase64Url(String input) {
        return new String(base64Decode(input, URL_LOOKUP_ARRAY));
    }

    private static byte[] base64Decode(String input, int[] lookupArray) {
        Base64.Decoder decoder = Base64.getDecoder();
        StringBuilder temp = new StringBuilder(input.length());
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c == '+' || c == '-') {
                temp.append('/');
            } else if (c == '/' || c == '_') {
                temp.append('+');
            } else {
                temp.append(c);
            }
        }
        return decoder.decode(temp.toString());
    }

    public static void main(String[] args) {
        String input = "This is a sample input string.";
        String base64 = encodeBase64(input);
        String base64Url = encodeBase64Url(input);
        System.out.println("Base64: " + base64);
        System.out.println("Base64Url: " + base64Url);

        String decodedBase64 = decodeBase64(base64);
        String decodedBase64Url = decodeBase64Url(base64Url);
        System.out.println("Decoded Base64: " + decodedBase64);
        System.out.println("Decoded Base64Url: " + decodedBase64Url);
    }
}
