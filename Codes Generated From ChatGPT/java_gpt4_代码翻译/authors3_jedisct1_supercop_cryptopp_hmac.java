import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

public class HMAC {
    private final String algorithm;
    private final int blockSize;
    private final Mac macInstance;

    private byte[] key;
    private byte[] innerPadding;
    private byte[] outerPadding;

    public HMAC(String algorithm, int blockSize) throws NoSuchAlgorithmException {
        this.algorithm = algorithm;
        this.blockSize = blockSize;
        this.macInstance = Mac.getInstance(algorithm);
    }

    public void setKey(byte[] userKey) throws InvalidKeyException {
        byte[] actualKey = userKey;

        if (userKey.length > blockSize) {
            actualKey = hash(userKey);
        }

        key = new byte[blockSize];
        System.arraycopy(actualKey, 0, key, 0, actualKey.length);

        innerPadding = new byte[blockSize];
        outerPadding = new byte[blockSize];

        for (int i = 0; i < blockSize; i++) {
            innerPadding[i] = (byte) (key[i] ^ 0x36);
            outerPadding[i] = (byte) (key[i] ^ 0x5c);
        }
    }

    public byte[] compute(byte[] message) throws IllegalStateException, InvalidKeyException {
        if (key == null) {
            throw new IllegalStateException("Key must be set before computing HMAC");
        }

        byte[] innerResult = hash(concatenate(innerPadding, message));
        byte[] outerResult = hash(concatenate(outerPadding, innerResult));

        return outerResult;
    }

    private byte[] hash(byte[] data) throws InvalidKeyException {
        SecretKeySpec secretKeySpec = new SecretKeySpec(data, algorithm);
        macInstance.init(secretKeySpec);
        return macInstance.doFinal();
    }

    private static byte[] concatenate(byte[] a, byte[] b) {
        byte[] result = new byte[a.length + b.length];
        System.arraycopy(a, 0, result, 0, a.length);
        System.arraycopy(b, 0, result, a.length, b.length);
        return result;
    }

    public static void main(String[] args) {
        try {
            String algorithm = "HmacSHA256";
            int blockSize = 64;
            HMAC hmac = new HMAC(algorithm, blockSize);

            byte[] key = "test-key".getBytes(StandardCharsets.UTF_8);
            hmac.setKey(key);

            byte[] message = "Hello, World!".getBytes(StandardCharsets.UTF_8);
            byte[] computedHMAC = hmac.compute(message);

            System.out.println("Computed HMAC:");
            for (byte b : computedHMAC) {
                System.out.printf("%02X ", b);
            }
            System.out.println();
        } catch (NoSuchAlgorithmException | InvalidKeyException e) {
            e.printStackTrace();
        }
    }
}
