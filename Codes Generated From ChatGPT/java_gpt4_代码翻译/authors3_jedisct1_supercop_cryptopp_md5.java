import java.nio.ByteBuffer;

public class MD5 {

    private static final int[] S = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
            5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    private static final int[] K = new int[64];

    static {
        for (int i = 0; i < 64; i++) {
            K[i] = (int) (Math.abs(Math.sin(i + 1)) * Math.pow(2, 32));
        }
    }

    public static int[] initState() {
        return new int[]{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    }

    private static int F(int x, int y, int z) {
        return (x & y) | (~x & z);
    }

    private static int G(int x, int y, int z) {
        return (x & z) | (y & ~z);
    }

    private static int H(int x, int y, int z) {
        return x ^ y ^ z;
    }

    private static int I(int x, int y, int z) {
        return y ^ (x | ~z);
    }

    private static int rotateLeft(int x, int n) {
        return (x << n) | (x >>> (32 - n));
    }

    public static void transform(int[] digest, byte[] data) {
        int[] buffer = new int[16];
        ByteBuffer.wrap(data).asIntBuffer().get(buffer);

        int a = digest[0];
        int b = digest[1];
        int c = digest[2];
        int d = digest[3];

        for (int i = 0; i < 64; i++) {
            int f, g;
            if (i < 16) {
                f = F(b, c, d);
                g = i;
            } else if (i < 32) {
                f = G(b, c, d);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = H(b, c, d);
                g = (3 * i + 5) % 16;
            } else {
                f = I(b, c, d);
                g = (7 * i) % 16;
            }

            int tmp = d;
            d = c;
            c = b;
            b = b + rotateLeft(a + f + K[i] + buffer[g], S[i]);
            a = tmp;
        }
        digest[0] += a;
        digest[1] += b;
        digest[2] += c;
        digest[3] += d;
    }

    public static byte[] md5(byte[] message) {
        int[] digest = initState();
        int messageLengthBits = message.length * 8;

        byte[] padding = new byte[64 - (message.length + 8) % 64];
        padding[0] = (byte) 0x80;

        byte[] messageWithPadding = new byte[message.length + padding.length + 8];
        System.arraycopy(message, 0, messageWithPadding, 0, message.length);
        System.arraycopy(padding, 0, messageWithPadding, message.length, padding.length);

        ByteBuffer.wrap(messageWithPadding, message.length + padding.length, 8).putLong(messageLengthBits);

        for (int i = 0; i < messageWithPadding.length; i += 64) {
            byte[] block = new byte[64];
            System.arraycopy(messageWithPadding, i, block, 0, 64);
            transform(digest, block);
        }

        byte[] result = new byte[16];
        ByteBuffer.wrap(result).asIntBuffer().put(digest);
        return result;
    }

    public static void main(String[] args) {
        String testString = "The quick brown fox jumps over the lazy dog";
        byte[] testBytes = testString.getBytes();

        byte[] md5Hash = md5(testBytes);
        StringBuilder sb = new StringBuilder();
        for (byte b : md5Hash) {
            sb.append(String.format("%02x", b));
        }
        System.out.println("MD5 Hash: " + sb.toString());
    }
}

