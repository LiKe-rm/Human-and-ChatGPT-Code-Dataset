import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.PBEParameterSpec;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.security.GeneralSecurityException;
import java.security.spec.KeySpec;
import java.util.Base64;

public class SendSocket {
    private static final String ENCRYPTION_ALGORITHM = "PBEWithMD5AndDES";
    private static final byte[] SALT = new byte[]{(byte) 0xc7, (byte) 0x73, (byte) 0x21, (byte) 0x8c, (byte) 0x7e, (byte) 0xc8, (byte) 0xee, (byte) 0x99};
    private static final int ITERATION_COUNT = 20;

    private Cipher encryptor;
    private Socket connection;

    public SendSocket() {
        this.encryptor = null;
        this.connection = null;
    }

    public void initializeEncryptor(String password) throws GeneralSecurityException {
        KeySpec keySpec = new PBEKeySpec(password.toCharArray());
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance(ENCRYPTION_ALGORITHM);
        SecretKey key = keyFactory.generateSecret(keySpec);
        encryptor = Cipher.getInstance(ENCRYPTION_ALGORITHM);
        PBEParameterSpec paramSpec = new PBEParameterSpec(SALT, ITERATION_COUNT);
        encryptor.init(Cipher.ENCRYPT_MODE, key, paramSpec);
    }

    public void connect(String ipAddress, int port) throws IOException {
        connection = new Socket(ipAddress, port);
    }

    public void disconnect() throws IOException {
        if (connection != null) {
            connection.close();
            connection = null;
        }
    }

    public boolean sendCSendData(SendInfo data, SendType type) {
        data.setType(type);
        return sendExactSize(data.toString().getBytes(StandardCharsets.UTF_8), true);
    }

    public boolean sendExactSize(byte[] data, boolean encrypt) {
        boolean result = false;

        if (encryptor == null && encrypt) {
            System.err.println("Encryption not initialized");
            return result;
        }

        System.out.println("START SendExactSize Total " + data.length);

        byte[] output;
        int outputLength = data.length;

        if (!encrypt || encrypt(data, output = new byte[outputLength], outputLength)) {
            int bytesRead = 0;
            int expected = outputLength;

            try (DataOutputStream dataOutputStream = new DataOutputStream(connection.getOutputStream())) {
                dataOutputStream.write(output, bytesRead, expected - bytesRead);
                bytesRead += expected - bytesRead;
                dataOutputStream.flush();

                if (bytesRead == expected) {
                    result = true;
                }
            } catch (IOException e) {
                System.err.println("Error in sendExactSize: " + e.getMessage());
            }
        } else {
            System.err.println("SendExactSize: Failed to encrypt data");
        }

        System.out.println("END SendExactSize Total " + bytesRead);

        return result;
    }

    private boolean encrypt(byte[] data, byte[] output, int outputLength) {
        try {
            byte[] encryptedData = encryptor.doFinal(data);
            System.arraycopy(encryptedData, 0, output, 0, encryptedData.length);
            return true;
        } catch (GeneralSecurityException e) {
            System.err.println("Error encrypting data: " + e.getMessage());
            return false;
        }
    }
    public static void main(String[] args) {
        SendSocket sendSocket = new SendSocket();

        try {
            sendSocket.initializeEncryptor("your-password");
            sendSocket.connect("127.0.0.1", 8080);

            SendInfo sendInfo = new SendInfo();
            sendInfo.setContent("Hello, World!");

            if (sendSocket.sendCSendData(sendInfo, SendType.SOME_TYPE)) {
                System.out.println("Data sent successfully");
            } else {
                System.err.println("Failed to send data");
            }

            sendSocket.disconnect();
        } catch (IOException | GeneralSecurityException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}

enum SendType {
    SOME_TYPE,
    ANOTHER_TYPE
}

class SendInfo {
    private SendType type;
    private String content;
    public SendType getType() {
        return type;
    }

    public void setType(SendType type) {
        this.type = type;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    @Override
    public String toString() {
        return type.name() + ":" + content;
    }
}
