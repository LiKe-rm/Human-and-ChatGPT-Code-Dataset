import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class CryptoPP {

    public static byte[] xorbuf(byte[] buf, byte[] mask) {
        assert buf != null && mask != null;
        byte[] result = new byte[buf.length];
        for (int i = 0; i < buf.length; i++) {
            result[i] = (byte) (buf[i] ^ mask[i % mask.length]);
        }
        return result;
    }

    public static byte[] xorbuf(byte[] output, byte[] input, byte[] mask) {
        assert output != null && input != null && mask != null;
        for (int i = 0; i < input.length; i++) {
            output[i] = (byte) (input[i] ^ mask[i % mask.length]);
        }
        return output;
    }

    public static boolean verifyBufsEqual(byte[] buf, byte[] mask) {
        assert buf != null && mask != null;
        return Arrays.equals(buf, mask);
    }

    public static String stringNarrow(String str, boolean throwOnError) {
        assert str != null;
        try {
            byte[] bytes = str.getBytes(StandardCharsets.UTF_16);
            return new String(bytes, StandardCharsets.ISO_8859_1);
        } catch (Exception e) {
            if (throwOnError) {
                throw new IllegalArgumentException("StringNarrow: call failed", e);
            } else {
                return "";
            }
        }
    }

    public static String stringWiden(String str, boolean throwOnError) {
        assert str != null;
        try {
            byte[] bytes = str.getBytes(StandardCharsets.ISO_8859_1);
            return new String(bytes, StandardCharsets.UTF_16);
        } catch (Exception e) {
            if (throwOnError) {
                throw new IllegalArgumentException("StringWiden: call failed", e);
            } else {
                return "";
            }
        }
    }

    public static void main(String[] args) {
        byte[] buf = new byte[]{1, 2, 3, 4, 5};
        byte[] mask = new byte[]{5, 4, 3, 2, 1};

        byte[] xorResult = xorbuf(buf, mask);
        System.out.println(Arrays.toString(xorResult));

        byte[] output = new byte[5];
        xorbuf(output, buf, mask);
        System.out.println(Arrays.toString(output));

        System.out.println(verifyBufsEqual(buf, mask));
        System.out.println(verifyBufsEqual(buf, buf));

        String wide = stringWiden("Hello, world!", false);
        System.out.println(wide);

        String narrow = stringNarrow(wide, false);
        System.out.println(narrow);
    }
}
