import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class GOST {
    private static final int[][] SBOX = {
            {4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3},
            {14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9},
            {5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11},
            {7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3},
            {6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2},
            {4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14},
            {13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12},
            {1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12}};

    private static boolean tableCalculated = false;
    private static int[][] STABLE = new int[4][256];
    private int[] key = new int[8];

    public GOST(byte[] userKey) {
        if (userKey.length != 32) {
            throw new IllegalArgumentException("Invalid key length");
        }
        precalculateSTable();
        ByteBuffer buffer = ByteBuffer.wrap(userKey).order(ByteOrder.LITTLE_ENDIAN);
        for (int i = 0; i < 8; i++) {
            key[i] = buffer.getInt();
        }
    }

    private static void precalculateSTable() {
        if (!tableCalculated) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 256; j++) {
                    int temp = SBOX[2 * i][j % 16] | (SBOX[2 * i + 1][j / 16] << 4);
                    STABLE[i][j] = Integer.rotateLeft(temp, 11 + 8 * i);
                }
            }
            tableCalculated = true;
        }
    }

    private static int f(int x) {
        return STABLE[3][(x >> 24) & 0xFF] ^ STABLE[2][(x >> 16) & 0xFF] ^ STABLE[1][(x >> 8) & 0xFF] ^ STABLE[0][x & 0xFF];
    }

    public byte[] encrypt(byte[] input) {
        if ((input.length != 8) {
            throw new IllegalArgumentException("Invalid input block size");
        }
        ByteBuffer buffer = ByteBuffer.wrap(input).order(ByteOrder.LITTLE_ENDIAN);
        int n1 = buffer.getInt();
        int n2 = buffer.getInt();
        int t;
    
        for (int i = 0; i < 3; i++) {
            n2 ^= f(n1 + key[0]);
            n1 ^= f(n2 + key[1]);
            n2 ^= f(n1 + key[2]);
            n1 ^= f(n2 + key[3]);
            n2 ^= f(n1 + key[4]);
            n1 ^= f(n2 + key[5]);
            n2 ^= f(n1 + key[6]);
            n1 ^= f(n2 + key[7]);
        }
    
        n2 ^= f(n1 + key[7]);
        n1 ^= f(n2 + key[6]);
        n2 ^= f(n1 + key[5]);
        n1 ^= f(n2 + key[4]);
        n2 ^= f(n1 + key[3]);
        n1 ^= f(n2 + key[2]);
        n2 ^= f(n1 + key[1]);
        n1 ^= f(n2 + key[0]);
    
        buffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
        buffer.putInt(n2);
        buffer.putInt(n1);
        return buffer.array();
    }
    
    public byte[] decrypt(byte[] input) {
        if (input.length != 8) {
            throw new IllegalArgumentException("Invalid input block size");
        }
    
        ByteBuffer buffer = ByteBuffer.wrap(input).order(ByteOrder.LITTLE_ENDIAN);
        int n1 = buffer.getInt();
        int n2 = buffer.getInt();
        int t;
    
        n2 ^= f(n1 + key[0]);
        n1 ^= f(n2 + key[1]);
        n2 ^= f(n1 + key[2]);
        n1 ^= f(n2 + key[3]);
        n2 ^= f(n1 + key[4]);
        n1 ^= f(n2 + key[5]);
        n2 ^= f(n1 + key[6]);
        n1 ^= f(n2 + key[7]);
    
        for (int i = 0; i < 3; i++) {
            n2 ^= f(n1 + key[7]);
            n1 ^= f(n2 + key[6]);
            n2 ^= f(n1 + key[5]);
            n1 ^= f(n2 + key[4]);
            n2 ^= f(n1 + key[3]);
            n1 ^= f(n2 + key[2]);
            n2 ^= f(n1 + key[1]);
            n1 ^= f(n2 + key[0]);
        }
    
        buffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
        buffer.putInt(n2);
        buffer.putInt(n1);
        return buffer.array();
    }
}                
            
