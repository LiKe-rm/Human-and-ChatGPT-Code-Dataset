import org.bouncycastle.crypto.Digest;
import org.bouncycastle.crypto.InvalidCipherTextException;
import org.bouncycastle.crypto.digests.SHA1Digest;
import org.bouncycastle.crypto.engines.RSAEngine;
import org.bouncycastle.crypto.params.RSAKeyParameters;
import org.bouncycastle.util.Arrays;

import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Random;

public class OAEPBase {

    private final Digest hash;
    private final MaskGenerator maskGenerator;

    public OAEPBase(Digest hash, MaskGenerator maskGenerator) {
        this.hash = hash;
        this.maskGenerator = maskGenerator;
    }

    public int getMaxUnpaddedLength(int paddedLength) {
        return Math.max(0, (paddedLength / 8) - 1 - (2 * hash.getDigestSize()));
    }

    public byte[] pad(Random random, byte[] input, int inputLength, int oaepBlockLen) throws NoSuchAlgorithmException {
        int maxUnpaddedLength = getMaxUnpaddedLength(oaepBlockLen);
        if (inputLength > maxUnpaddedLength) {
            throw new IllegalArgumentException("Input is too long");
        }

        ByteBuffer oaepBlock = ByteBuffer.allocate(oaepBlockLen / 8);
        int hLen = hash.getDigestSize();
        int seedLen = hLen, dbLen = oaepBlockLen / 8 - seedLen;
        byte[] maskedSeed = new byte[seedLen];
        byte[] maskedDB = new byte[dbLen];

        byte[] pHash = new byte[hLen];
        hash.update(new byte[0], 0, 0);
        hash.doFinal(pHash, 0);

        System.arraycopy(pHash, 0, maskedDB, 0, hLen);
        maskedDB[dbLen - inputLength - 1] = 0x01;
        System.arraycopy(input, 0, maskedDB, dbLen - inputLength, inputLength);

        random.nextBytes(maskedSeed);
        maskGenerator.generateAndMask(hash, maskedDB, dbLen, maskedSeed, seedLen);
        maskGenerator.generateAndMask(hash, maskedSeed, seedLen, maskedDB, dbLen);

        oaepBlock.put(maskedSeed);
        oaepBlock.put(maskedDB);
        return oaepBlock.array();
    }

    public byte[] unpad(byte[] oaepBlock, int oaepBlockLen) throws InvalidCipherTextException {
        if (oaepBlockLen % 8 != 0) {
            if (oaepBlock[0] != 0) {
                throw new InvalidCipherTextException("Invalid OAEP block");
            }
            oaepBlock = Arrays.copyOfRange(oaepBlock, 1, oaepBlock.length);
            oaepBlockLen -= 8;
        }

        int hLen = hash.getDigestSize();
        int seedLen = hLen, dbLen = oaepBlockLen / 8 - seedLen;
        byte[] maskedSeed = Arrays.copyOfRange(oaepBlock, 0, seedLen);
        byte[] maskedDB = Arrays.copyOfRange(oaepBlock, seedLen, oaepBlock.length);

        if (oaepBlockLen < 2 * hLen + 1) {
            throw new InvalidCipherTextException("Invalid OAEP block length");
        }

        maskGenerator.generateAndMask(hash, maskedSeed, seedLen, maskedDB, dbLen);
        maskGenerator.generateAndMask(hash, maskedDB, dbLen, maskedSeed, seedLen);

        byte[] pHash = new byte[hLen];
        hash.update(new byte[0], 0, 0);
        hash.doFinal(pHash, 0);

        if (!Arrays.areEqual(Arrays.copyOfRange(maskedDB, 0, hLen), pHash)) {
            throw new InvalidCipherTextException("Invalid OAEP block");
        }

        int separatorIndex = -1;
        for (int i = hLen; i < dbLen; i++) {
            if (maskedDB[i] == 0x01) {
                separatorIndex = i;
                break;
            } else if (maskedDB[i] != 0) {
                throw new InvalidCipherTextException("Invalid OAEP block");
            }
        }

        if (separatorIndex == -1) {
            throw new InvalidCipherTextException("Invalid OAEP block");
        }

        return Arrays.copyOfRange(maskedDB, separatorIndex + 1, dbLen);
    }

    public static void main(String[] args) {
        // Example usage of the OAEPBase class
        try {
            byte[] input = "Hello, World!".getBytes();
            Digest hash = new SHA1Digest();
            MaskGenerator mgf = new MaskGenerator1(hash);
            OAEPBase oaep = new OAEPBase(hash, mgf);

            // Generate a random RSA key pair for testing
            BigInteger n = new BigInteger("00a040a6d9b4f218c50b2d1121c4507b1da1f52423c3ec8b14b3df9ec56f9a7cb1", 16);
            BigInteger e = new BigInteger("010001", 16);
            BigInteger d = new BigInteger("008eb1b9e796f6e7d6af1774a4e50e532f31dce4b6758e77a46a0999df1b456e19", 16);
            RSAKeyParameters publicKey = new RSAKeyParameters(false, n, e);
            RSAKeyParameters privateKey = new RSAKeyParameters(true, n, d);
            RSAEngine rsaEngine = new RSAEngine();

            byte[] padded = oaep.pad(new SecureRandom(), input, input.length, n.bitLength());
            rsaEngine.init(true, publicKey);
            byte[] encrypted = rsaEngine.processBlock(padded, 0, padded.length);

            rsaEngine.init(false, privateKey);
            byte[] decrypted = rsaEngine.processBlock(encrypted, 0, encrypted.length);
            byte[] unpadded = oaep.unpad(decrypted, n.bitLength());

            System.out.println("Original: " + new String(input));
            System.out.println("Unpadded: " + new String(unpadded));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

