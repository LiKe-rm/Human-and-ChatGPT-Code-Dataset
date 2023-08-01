import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class OSRNG {
    private static final int DEFAULT_SEED_SIZE = 32;

    public static class RNGException extends Exception {
        public RNGException(String message) {
            super(message);
        }
    }

    public static class BlockingRNG {
        private SecureRandom random;

        public BlockingRNG() throws RNGException {
            try {
                random = SecureRandom.getInstance("NativePRNGBlocking");
            } catch (NoSuchAlgorithmException e) {
                throw new RNGException("Failed to create Blocking RNG: " + e.getMessage());
            }
        }

        public void generateBlock(byte[] output, int size) {
            random.nextBytes(output);
        }
    }

    public static class NonBlockingRNG {
        private SecureRandom random;

        public NonBlockingRNG() throws RNGException {
            try {
                random = SecureRandom.getInstance("NativePRNGNonBlocking");
            } catch (NoSuchAlgorithmException e) {
                throw new RNGException("Failed to create Non-Blocking RNG: " + e.getMessage());
            }
        }

        public void generateBlock(byte[] output, int size) {
            random.nextBytes(output);
        }
    }

    public static void osGenerateRandomBlock(boolean blocking, byte[] output, int size) throws RNGException {
        if (blocking) {
            BlockingRNG rng = new BlockingRNG();
            rng.generateBlock(output, size);
        } else {
            NonBlockingRNG rng = new NonBlockingRNG();
            rng.generateBlock(output, size);
        }
    }

    public static void autoSeededRandomPool(boolean blocking, int seedSize, byte[] output) throws RNGException {
        osGenerateRandomBlock(blocking, output, seedSize);
    }

    public static void main(String[] args) {
        try {
            byte[] randomBytes = new byte[32];
            autoSeededRandomPool(false, DEFAULT_SEED_SIZE, randomBytes);

            for (byte b : randomBytes) {
                System.out.printf("%02x", b);
            }

            System.out.println();
        } catch (RNGException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
