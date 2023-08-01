import java.io.InputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class QCryptographicHash {
    public enum Algorithm {
        MD5("MD5"),
        SHA1("SHA-1"),
        SHA224("SHA-224"),
        SHA256("SHA-256"),
        SHA384("SHA-384"),
        SHA512("SHA-512");

        private final String algorithm;

        Algorithm(String algorithm) {
            this.algorithm = algorithm;
        }

        public String getAlgorithm() {
            return algorithm;
        }
    }

    private MessageDigest messageDigest;

    public QCryptographicHash(Algorithm algorithm) {
        try {
            messageDigest = MessageDigest.getInstance(algorithm.getAlgorithm());
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Invalid algorithm", e);
        }
    }

    public void addData(byte[] data) {
        messageDigest.update(data);
    }

    public void addData(InputStream inputStream) {
        byte[] buffer = new byte[4096];
        int bytesRead;
        try {
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                messageDigest.update(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            throw new RuntimeException("Error reading from input stream", e);
        }
    }

    public void addData(String data, int length) {
        messageDigest.update(data.getBytes(), 0, length);
    }

    public void reset() {
        messageDigest.reset();
    }

    public byte[] result() {
        return messageDigest.digest();
    }

    public static byte[] hash(byte[] data, Algorithm algorithm) {
        QCryptographicHash hash = new QCryptographicHash(algorithm);
        hash.addData(data);
        return hash.result();
    }
}
