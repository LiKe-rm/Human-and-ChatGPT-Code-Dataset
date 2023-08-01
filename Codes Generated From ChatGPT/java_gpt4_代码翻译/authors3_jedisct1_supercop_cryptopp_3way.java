import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ThreeWay {

    private static final int START_E = 0x0b0b; // round constant of first encryption round
    private static final int START_D = 0xb1b1; // round constant of first decryption round

    private int[] key;
    private boolean isEncryption;
    private int rounds;

    public ThreeWay(byte[] key, boolean isEncryption, int rounds) {
        if (key.length != 12) {
            throw new IllegalArgumentException("Invalid key length");
        }
        this.key = new int[3];
        ByteBuffer buffer = ByteBuffer.wrap(key).order(ByteOrder.BIG_ENDIAN);
        for (int i = 0; i < 3; i++) {
            this.key[i] = buffer.getInt();
        }
        this.isEncryption = isEncryption;
        this.rounds = rounds;

        if (!isEncryption) {
            theta();
            mu();
            for (int i = 0; i < 3; i++) {
                this.key[i] = Integer.reverseBytes(this.key[i]);
            }
        }
    }

    private static int reverseBits(int a) {
        a = ((a & 0xAAAAAAAA) >>> 1) | ((a & 0x55555555) << 1);
        a = ((a & 0xCCCCCCCC) >>> 2) | ((a & 0x33333333) << 2);
        return ((a & 0xF0F0F0F0) >>> 4) | ((a & 0x0F0F0F0F) << 4);
    }

    private void mu() {
        key[1] = reverseBits(key[1]);
        int temp = reverseBits(key[0]);
        key[0] = reverseBits(key[2]);
        key[2] = temp;
    }

    private void piGammaPi() {
        int b0, b2;
        b2 = Integer.rotateLeft(key[2], 1);
        b0 = Integer.rotateLeft(key[0], 22);
        key[0] = Integer.rotateLeft(b0 ^ (key[1] | (~b2)), 1);
        key[2] = Integer.rotateLeft(b2 ^ (b0 | (~key[1])), 22);
        key[1] ^= (b2 | (~b0));
    }

    private void theta() {
        int b0, b1, c;
        c = key[0] ^ key[1] ^ key[2];
        c = Integer.rotateLeft(c, 16) ^ Integer.rotateLeft(c, 8);
        b0 = (key[0] << 24) ^ (key[2] >>> 8) ^ (key[1] << 8) ^ (key[0] >>> 24);
        b1 = (key[1] << 24) ^ (key[0] >>> 8) ^ (key[2] << 8) ^ (key[1] >>> 24);
        key[0] ^= c ^ b0;
        key[1] ^= c ^ b1;
        key[2] ^= c ^ (b0 >>> 16) ^ (b1 << 16);
    }

    private void rho() {
        theta();
        piGammaPi();
    }

    public byte[] processBlock(byte[] input) {
        if (input.length != 12) {
            throw new IllegalArgumentException("Invalid block length");
        }
        ByteBuffer buffer = ByteBuffer.wrap(input).order(ByteOrder.BIG_ENDIAN);
        int[] block = new int[3];
        for (int i = 0; i < 3; i++) {
        block[i] = buffer.getInt();
        }
        int rc = isEncryption ? START_E : START_D;

        for (int i = 0; i < rounds; i++) {
            block[0] ^= key[0] ^ (rc << 16);
            block[1] ^= key[1];
            block[2] ^= key[2] ^ rc;
            rho();
    
            rc <<= 1;
            if ((rc & 0x10000) != 0) rc ^= 0x11011;
        }
        block[0] ^= key[0] ^ (rc << 16);
        block[1] ^= key[1];
        block[2] ^= key[2] ^ rc;
        theta();
    
        if (!isEncryption) {
            mu();
        }
    
        byte[] output = new byte[12];
        buffer = ByteBuffer.wrap(output).order(ByteOrder.BIG_ENDIAN);
        for (int i = 0; i < 3; i++) {
            buffer.putInt(block[i]);
        }
        return output;
    }
    
    public static void main(String[] args) {
        byte[] key = new byte[]{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C};
        byte[] plaintext = new byte[]{0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
        ThreeWay threeWayEncryption = new ThreeWay(key, true, 11);
        byte[] ciphertext = threeWayEncryption.processBlock(plaintext);
        ThreeWay threeWayDecryption = new ThreeWay(key, false, 11);
        byte[] decryptedText = threeWayDecryption.processBlock(ciphertext);
    
        // Print the results
        System.out.println("Plaintext: " + bytesToHex(plaintext));
        System.out.println("Ciphertext: " + bytesToHex(ciphertext));
        System.out.println("Decrypted Text: " + bytesToHex(decryptedText));
    }
    
    private static String bytesToHex(byte[] bytes) {
        StringBuilder builder = new StringBuilder();
        for (byte b : bytes) {
            builder.append(String.format("%02x", b));
        }
        return builder.toString();
    }
}    