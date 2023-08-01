import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.security.*;
import java.util.Base64;

public class ReceiveSocket {
    private Socket socket;
    private DataInputStream in;
    private byte[] dataReturnedFromDecrypt;
    private EncryptionHelper encryptionHelper;

    public ReceiveSocket(Socket socket) {
        this.socket = socket;
        try {
            this.in = new DataInputStream(socket.getInputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.encryptionHelper = new EncryptionHelper();
    }

    public void freeDecryptedData() {
        dataReturnedFromDecrypt = null;
    }

    public byte[] receiveEncryptedData(int inSize) throws IOException {
        if (dataReturnedFromDecrypt != null) {
            freeDecryptedData();
        }

        byte[] input = new byte[inSize];
        in.readFully(input, 0, inSize);

        String[] passwords = {"password1", "password2"}; // Replace with actual passwords
        byte[] output = null;

        for (String password : passwords) {
            try {
                output = encryptionHelper.decrypt(input, password);
                if (output != null) {
                    break;
                }
            } catch (GeneralSecurityException e) {
                e.printStackTrace();
            }
        }

        dataReturnedFromDecrypt = output;

        return output;
    }

    public boolean receiveExactSize(byte[] data, int size) throws IOException {
        int bytesRead;
        int totalBytesRead = 0;
        int remainingSize = size;

        while (remainingSize > 0) {
            bytesRead = in.read(data, totalBytesRead, remainingSize);
            if (bytesRead == -1) {
                return false;
            }
            remainingSize -= bytesRead;
            totalBytesRead += bytesRead;
        }

        return true;
    }

    public boolean receiveSendInfo(SendInfo info) throws IOException {
        int encryptedSizeSendInfo = 508;
        byte[] data = receiveEncryptedData(encryptedSizeSendInfo);
        if (data != null) {
            ByteArrayInputStream byteIn = new ByteArrayInputStream(data);
            ObjectInputStream objectIn = new ObjectInputStream(byteIn);
            try {
                SendInfo receivedInfo = (SendInfo) objectIn.readObject();
                info.copyFrom(receivedInfo);
                return true;
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } finally {
                objectIn.close();
            }
        }
        return false;
    }

    // Define your SendInfo class here
    public static class SendInfo implements Serializable {
        // Your fields and methods
        public void copyFrom(SendInfo other) {
            // Copy data from other to this instance
        }
    }

    // Encryption helper class
    public static class EncryptionHelper {
        private static final String ALGORITHM = "AES";
        private static final int KEY_SIZE = 128;

        public byte[] decrypt(byte[] data, String password) throws GeneralSecurityException {
            SecretKey secretKey = generateKey(password);
            Cipher cipher = Cipher.getInstance(ALGORITHM);
            cipher.init(Cipher.DECRYPT_MODE, secretKey);
            return cipher.doFinal(Base64.getDecoder().decode(data));
        }

        private SecretKey generateKey(String password) throws NoSuchAlgorithmException {
            MessageDigest sha = MessageDigest.getInstance("SHA-1");
            byte[] key = sha.digest(password.getBytes(StandardCharsets.UTF_8));
            key = java.util.Arrays.copyOf(key, KEY_SIZE / 8);
            return new SecretKeySpec(key, ALGORITHM);
        }
    }
}
