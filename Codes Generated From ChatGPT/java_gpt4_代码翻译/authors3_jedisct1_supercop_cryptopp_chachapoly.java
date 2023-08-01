import org.bouncycastle.crypto.engines.ChaCha20Poly1305;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.crypto.params.ParametersWithIV;
import org.bouncycastle.util.Arrays;

import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class ChaCha20Poly1305Example {

    public static void main(String[] args) throws Exception {
        byte[] key = new byte[32];
        byte[] iv = new byte[12];
        byte[] aad = "Sample AAD".getBytes();
        byte[] message = "Sample message".getBytes();

        SecureRandom random = new SecureRandom();
        random.nextBytes(key);
        random.nextBytes(iv);

        byte[] ciphertext = encrypt(key, iv, aad, message);
        byte[] decryptedMessage = decrypt(key, iv, aad, ciphertext);

        if (Arrays.areEqual(message, decryptedMessage)) {
            System.out.println("Decryption successful");
        } else {
            System.out.println("Decryption failed");
        }
    }

    public static byte[] encrypt(byte[] key, byte[] iv, byte[] aad, byte[] message) throws InvalidKeyException, InvalidAlgorithmParameterException, NoSuchAlgorithmException {
        ChaCha20Poly1305 cipher = new ChaCha20Poly1305();
        cipher.init(true, new ParametersWithIV(new KeyParameter(key), iv));

        if (aad != null && aad.length > 0) {
            cipher.updateAAD(aad, 0, aad.length);
        }

        byte[] output = new byte[message.length + 16];
        cipher.processBytes(message, 0, message.length, output, 0);
        cipher.doFinal(output, message.length);

        return output;
    }

    public static byte[] decrypt(byte[] key, byte[] iv, byte[] aad, byte[] ciphertext) throws Exception {
        ChaCha20Poly1305 cipher = new ChaCha20Poly1305();
        cipher.init(false, new ParametersWithIV(new KeyParameter(key), iv));

        if (aad != null && aad.length > 0) {
            cipher.updateAAD(aad, 0, aad.length);
        }

        byte[] output = new byte[ciphertext.length - 16];
        int result = cipher.processBytes(ciphertext, 0, ciphertext.length, output, 0);

        if (result < 0) {
            throw new Exception("Authentication failed");
        }

        return output;
    }
}
