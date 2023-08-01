import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class IDEA {
    private static final int ROUNDS = 8;
    private static final int IDEA_KEYLEN = 6 * ROUNDS + 4;
    private short[] key = new short[IDEA_KEYLEN];

    public IDEA(byte[] userKey) {
        if (userKey.length != 16) {
            throw new IllegalArgumentException("Invalid key length");
        }
        setKey(userKey);
    }

    private void setKey(byte[] userKey) {
        ByteBuffer buffer = ByteBuffer.wrap(userKey).order(ByteOrder.BIG_ENDIAN);
        for (int i = 0; i < 8; i++) {
            key[i] = buffer.getShort();
        }

        for (int i = 8; i < IDEA_KEYLEN; i++) {
            int j = (i & 0x7) - 8;
            key[i] = (short) ((key[j + (i + 1) % 8] << 9 | key[j + (i + 2) % 8] >>> 7) & 0xFFFF);
        }
    }

    public byte[] encrypt(byte[] input) {
        if (input.length != 8) {
            throw new IllegalArgumentException("Invalid input length");
        }
        byte[] output = new byte[8];
        processBlock(input, output);
        return output;
    }

    private void processBlock(byte[] inBlock, byte[] outBlock) {
        ByteBuffer inBuffer = ByteBuffer.wrap(inBlock).order(ByteOrder.BIG_ENDIAN);
        short x0 = inBuffer.getShort();
        short x1 = inBuffer.getShort();
        short x2 = inBuffer.getShort();
        short x3 = inBuffer.getShort();

        for (int i = 0; i < ROUNDS; i++) {
            x0 = mul(x0, key[i * 6]);
            x1 += key[i * 6 + 1];
            x2 += key[i * 6 + 2];
            x3 = mul(x3, key[i * 6 + 3]);

            short t0 = (short) (x0 ^ x2);
            t0 = mul(t0, key[i * 6 + 4]);

            short t1 = (short) (t0 + (x1 ^ x3));
            t1 = mul(t1, key[i * 6 + 5]);

            t0 += t1;

            x0 ^= t1;
            x3 ^= t0;
            t0 ^= x1;
            x1 = (short) (x2 ^ t1);
            x2 = t0;
        }

        x0 = mul(x0, key[ROUNDS * 6]);
        x2 += key[ROUNDS * 6 + 1];
        x1 += key[ROUNDS * 6 + 2];
        x3 = mul(x3, key[ROUNDS * 6 + 3]);

        ByteBuffer outBuffer = ByteBuffer.wrap(outBlock).order(ByteOrder.BIG_ENDIAN);
        outBuffer.putShort(x0);
        outBuffer.putShort(x2);
        outBuffer.putShort(x1);
        outBuffer.putShort(x3);
    }
    private short mul(short a, short b) {
        if (a == 0) {
            a = (short) (0x10001 - b);
        } else if (b == 0) {
            a = (short) (0x10001 - a);
        } else {
            int p = a * b;
            int high = p >>> 16;
            int low = p & 0xFFFF;
            a = (short) (low - high);
    
            if (low < high) {
                a--;
            }
        }
        return a;
    }
    
    public static void main(String[] args) {
        byte[] key = new byte[]{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
        byte[] plaintext = new byte[]{0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    
        IDEA idea = new IDEA(key);
        byte[] ciphertext = idea.encrypt(plaintext);
    
        System.out.print("Ciphertext: ");
        for (byte b : ciphertext) {
            System.out.printf("%02X ", b);
        }
    }
}    