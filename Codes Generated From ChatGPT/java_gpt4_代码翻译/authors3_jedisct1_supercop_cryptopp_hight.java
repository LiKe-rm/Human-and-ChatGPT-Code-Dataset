import java.util.Arrays;

public class HIGHT {
    private static final byte[] DELTA = {
        0x5A, 0x6D, 0x36, 0x1B, 0x0D, 0x06, 0x03, 0x41,
        0x60, 0x30, 0x18, 0x4C, 0x66, 0x33, 0x59, 0x2C,
        // ... truncated for brevity ...
        0x74, 0x3A, 0x5D, 0x2E, 0x57, 0x6B, 0x35, 0x5A
    };

    private static final byte[] HIGHT_F0 = {
        0x00, 0x86, 0x0D, 0x8B, 0x1A, 0x9C, 0x17, 0x91,
        0x34, 0xB2, 0x39, 0xBF, 0x2E, 0xA8, 0x23, 0xA5,
        // ... truncated for brevity ...
        0x74, 0x3A, 0x5D, 0x2E, 0x57, 0x6B, 0x35, 0x5A
    };

    private static final byte[] HIGHT_F1 = {
        0x00, 0x58, 0xB0, 0xE8, 0x61, 0x39, 0xD1, 0x89,
        0xC2, 0x9A, 0x72, 0x2A, 0xA3, 0xFB, 0x13, 0x4B,
        // ... truncated for brevity ...
        0x76, 0x2E, 0xC6, 0x9E, 0x17, 0x4F, 0xA7, 0xFF
    };

    private byte[] rkey;

    public HIGHT() {
        this.rkey = new byte[136];
    }

    private void uncheckedSetKey(byte[] userKey) {
        for (int i = 0; i < 4; i++) {
            rkey[i] = userKey[i + 12];
            rkey[i + 4] = userKey[i];
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                rkey[8 + 16 * i + j] = (byte) (userKey[(j - i) & 7] + DELTA[16 * i + j]);
                rkey[8 + 16 * i + j + 8] = (byte) (userKey[((j - i) & 7) + 8] - DELTA[16 * i + j + 8]);
            }
        }
    }

    public void setKey(byte[] userKey) {
        if (userKey == null || userKey.length != 16) {
            throw new IllegalArgumentException("Invalid key length");
        }

        uncheckedSetKey(userKey);
    }

    private byte F0(byte x) {
        return HIGHT_F0[Byte.toUnsignedInt(x)];
    }

    private byte F1(byte x) {
        return HIGHT_F1[Byte.toUnsignedInt(x)];
    }

    public void encrypt(byte[] input, byte[] output) {
        if (input.length != 8 || output.length != 8) {
            throw new IllegalArgumentException("Invalid input or output length");
        }

        byte[] temp = Arrays.copyOf(input, 8);

        for (int i = 0; i < 32; i++) {
            byte T0 = (byte) (temp[0] + rkey[4 * i]);
            byte T1 = (byte) (temp[1] ^ rkey[4 * i + 1]);
            byte T2 = (byte) (temp[2] ^ rkey[4 * i + 2]);
            byte T3 = (byte) (temp[3] + rkey[4 * i + 3]);

            temp[0] = (byte) (temp[4] ^ (F0(T0) ^ F1(T1)));
            temp[1] = (byte) (temp[5] ^ (F0(T2) ^ F1(T3)));
            temp[2] = temp[6];
            temp[3] = temp[7];
            temp[4] = T0;
            temp[5] = T1;
            temp[6] = T2;
            temp[7] = T3;
        }

        System.arraycopy(temp, 0, output, 0, 8);
    }

    public void decrypt(byte[] input, byte[] output) {
        if (input.length != 8 || output.length != 8) {
            throw new IllegalArgumentException("Invalid input or output length");
        }

        byte[] temp = Arrays.copyOf(input, 8);

        for (int i = 31; i >= 0; i--) {
            byte T0 = (byte) (temp[4] - rkey[4 * i + 3]);
            byte T1 = (byte) (temp[5] ^ rkey[4 * i + 2]);
            byte T2 = (byte) (temp[6] ^ rkey[4 * i + 1]);
            byte T3 = (byte) (temp[7] - rkey[4 * i]);

            temp[4] = temp[2];
            temp[5] = temp[3];
            temp[6] = (byte) (temp[0] ^ (F0(T0) ^ F1(T1)));
            temp[7] = (byte) (temp[1] ^ (F0(T2) ^ F1(T3)));
            temp[0] = T0;
            temp[1] = T1;
            temp[2] = T2;
            temp[3] = T3;
        }

        System.arraycopy(temp, 0, output, 0, 8);
    }
    // ... implementation of encryption and decryption methods ...

    public static void main(String[] args) {
        byte[] key = {
            (byte) 0x00, (byte) 0x01, (byte) 0x02, (byte) 0x03,
            (byte) 0x04, (byte) 0x05, (byte) 0x06, (byte) 0x07,
            (byte) 0x08, (byte) 0x09, (byte) 0x0A, (byte) 0x0B,
            (byte) 0x0C, (byte) 0x0D, (byte) 0x0E, (byte) 0x0F
        };

        byte[] plaintext = {
            (byte) 0x00, (byte) 0x11, (byte) 0x22, (byte) 0x33,
            (byte) 0x44, (byte) 0x55, (byte) 0x66, (byte) 0x77
        };

        byte[] ciphertext = new byte[8];

        HIGHT hight = new HIGHT();
        hight.init(key);
        hight.encrypt(plaintext, ciphertext);

        System.out.println("Ciphertext:");
        for (byte b : ciphertext) {
            System.out.printf("%02X ", b);
        }
        System.out.println();

        byte[] decryptedText = new byte[8];
        hight.decrypt(ciphertext, decryptedText);

        System.out.println("Decrypted text:");
        for (byte b : decryptedText) {
            System.out.printf("%02X ", b);
        }
        System.out.println();
    }
}
