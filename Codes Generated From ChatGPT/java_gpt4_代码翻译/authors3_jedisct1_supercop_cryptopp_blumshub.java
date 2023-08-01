import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.security.SecureRandom;

public class BlumBlumShub {
    private BigInteger modn;
    private BigInteger current;
    private int maxBits;
    private int bitsLeft;

    public BlumBlumShub(BigInteger n, BigInteger seed) {
        this.modn = n;
        this.current = modn.multiply(modn).multiply(seed).mod(modn);
        this.maxBits = n.bitLength() - 1;
        this.bitsLeft = maxBits;
    }

    public int generateBit() {
        if (bitsLeft == 0) {
            current = modn.multiply(modn).mod(modn);
            bitsLeft = maxBits;
        }

        return current.testBit(--bitsLeft) ? 1 : 0;
    }

    public byte generateByte() {
        byte b = 0;
        for (int i = 0; i < 8; i++) {
            b = (byte) ((b << 1) | generateBit());
        }
        return b;
    }

    public void generateBlock(byte[] output) {
        for (int i = 0; i < output.length; i++) {
            output[i] = generateByte();
        }
    }

    public void processData(byte[] outString, byte[] inString) {
        for (int i = 0; i < inString.length; i++) {
            outString[i] = (byte) (inString[i] ^ generateByte());
        }
    }

    public static void main(String[] args) {
        SecureRandom random = new SecureRandom();
        BigInteger p = BigInteger.probablePrime(128, random);
        BigInteger q = BigInteger.probablePrime(128, random);
        BigInteger seed = new BigInteger(256, random);

        BlumBlumShub blumBlumShub = new BlumBlumShub(p.multiply(q), seed);

        byte[] inBlock = "abcdefgh".getBytes();
        byte[] outBlock = new byte[inBlock.length];

        blumBlumShub.processData(outBlock, inBlock);
        System.out.println(new String(outBlock));
    }
}
