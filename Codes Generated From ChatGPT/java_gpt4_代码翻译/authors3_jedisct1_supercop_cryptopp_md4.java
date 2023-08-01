import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class MD4 {
    private static final int[] INIT_STATE = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

    private int[] state = new int[4];

    public MD4() {
        init();
    }

    private void init() {
        System.arraycopy(INIT_STATE, 0, state, 0, state.length);
    }

    private static int F(int x, int y, int z) {
        return (z ^ (x & (y ^ z)));
    }

    private static int G(int x, int y, int z) {
        return ((x & y) | (x & z) | (y & z));
    }

    private static int H(int x, int y, int z) {
        return (x ^ y ^ z);
    }

    private static int rotl(int x, int n) {
        return (x << n) | (x >>> (32 - n));
    }

    private static void function(int[] v, int a, int b, int c, int d, int k, int s) {
        v[a] = rotl(v[a] + F(v[b], v[c], v[d]) + k, s);
    }

    public void transform(byte[] in) {
        int[] input = new int[16];
        ByteBuffer buf = ByteBuffer.wrap(in).order(ByteOrder.LITTLE_ENDIAN);
        for (int i = 0; i < 16; i++) {
            input[i] = buf.getInt();
        }

        int[] digest = Arrays.copyOf(state, state.length);
        int A = digest[0];
        int B = digest[1];
        int C = digest[2];
        int D = digest[3];

        // Round 1
        for (int i = 0; i < 16; i++) {
            function(digest, i % 4, (i + 1) % 4, (i + 2) % 4, (i + 3) % 4, input[i], (i % 4 == 0) ? 3 : (i % 4 == 1) ? 7 : (i % 4 == 2) ? 11 : 19);
        }

        // Round 2
        for (int i = 0; i < 16; i++) {
            digest[i % 4] = rotl(digest[i % 4] + G(digest[(i + 1) % 4], digest[(i + 2) % 4], digest[(i + 3) % 4]) + input[i % 4 * 4 + i / 4] + 0x5a827999, (i % 4 == 0) ? 3 : (i % 4 == 1) ? 5 : (i % 4 == 2) ? 9 : 13);
        }

        // Round 3
        for (int i = 0; i < 16; i++) {
            digest[i % 4] = rotl(digest[i % 4] + H(digest[(i + 1) % 4], digest[(i + 2) % 4], digest[(i + 3) % 4]) + input[(i / 4) * 4 + i % 4] + 0x6ed9eba1, (i % 4 == 0) ? 3 : (i % 4 == 1) ? 9 : (i % 4 == 2) ? 11 : 15);
        }
        for (int i = 0; i < state.length; i++) {
            state[i] += digest[i];
        }
    }
    
    public static void main(String[] args) {
        // Test the MD4 implementation
        MD4 md4 = new MD4();
        byte[] input = new byte[64];
        Arrays.fill(input, (byte) 0);
        md4.transform(input);
    
        for (int i : md4.state) {
            System.out.printf("%08x ", i);
        }
        System.out.println();
    }

}
