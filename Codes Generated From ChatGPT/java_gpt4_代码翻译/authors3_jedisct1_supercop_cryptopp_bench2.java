import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.*;
import java.util.*;
import java.time.*;

public class CryptoBenchmark {

    private static final int ITERATIONS = 1024;
    private static final byte[] defaultKey = new byte[32];

    public static void main(String[] args) {
        double allocatedTime = 3.0; // in seconds
        List<String> algorithms = List.of("AES", "DES", "DESede", "Blowfish", "RC2", "RC4");
        byte[] iv = new byte[16];

        for (String algorithm : algorithms) {
            try {
                Cipher cipher = Cipher.getInstance(algorithm + "/CTR/NoPadding");
                KeyGenerator keyGen = KeyGenerator.getInstance(algorithm);
                keyGen.init(new SecureRandom());
                SecretKey secretKey = keyGen.generateKey();

                IvParameterSpec ivSpec = new IvParameterSpec(iv);

                benchmarkKeying(cipher, secretKey, ivSpec, allocatedTime);
            } catch (NoSuchAlgorithmException | NoSuchPaddingException e) {
                System.err.println("Error initializing " + algorithm + ": " + e.getMessage());
            }
        }
    }

    private static void benchmarkKeying(Cipher cipher, SecretKey secretKey, IvParameterSpec ivSpec, double allocatedTime) {
        int iterations = 0;
        Instant startTime = Instant.now();
        Duration elapsedTime;

        do {
            for (int i = 0; i < ITERATIONS; i++) {
                try {
                    cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivSpec);
                } catch (InvalidKeyException | InvalidAlgorithmParameterException e) {
                    System.err.println("Error setting key and IV: " + e.getMessage());
                    return;
                }
            }
            iterations += ITERATIONS;
            elapsedTime = Duration.between(startTime, Instant.now());
        } while (elapsedTime.toMillis() < allocatedTime * 1000);

        double timeTaken = elapsedTime.toMillis() / 1000.0;
        outputResultKeying(cipher.getAlgorithm(), iterations, timeTaken);
    }

    private static void outputResultKeying(String algorithm, int iterations, double timeTaken) {
        double setupRate = iterations / timeTaken;
        System.out.printf("%s: %.2f setups/s\n", algorithm, setupRate);
    }
}
