import org.bouncycastle.crypto.Mac;
import org.bouncycastle.crypto.digests.GeneralDigest;
import org.bouncycastle.crypto.engines.ChaChaEngine;
import org.bouncycastle.crypto.generators.Poly1305KeyGenerator;
import org.bouncycastle.crypto.macs.Poly1305;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.crypto.params.ParametersWithIV;
import org.bouncycastle.util.Arrays;
import org.bouncycastle.util.Pack;

import java.nio.ByteOrder;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public class Poly1305Java {

    public static void main(String[] args) throws InvalidKeyException, NoSuchAlgorithmException {
        byte[] key = Base64.getDecoder().decode("abcdefghijklmnopqrstuvwxyz123456");
        byte[] nonce = Base64.getDecoder().decode("abcdefghijklmnop");

        byte[] message = "This is a test message.".getBytes();

        Poly1305Mac mac = new Poly1305Mac();
        mac.init(key, nonce);
        byte[] output = mac.calculateMac(message);

        System.out.println("MAC: " + Base64.getEncoder().encodeToString(output));
    }

    public static class Poly1305Mac {
        private Mac mac;

        public Poly1305Mac() {
            mac = new Poly1305(new ChaChaEngine());
        }

        public void init(byte[] key, byte[] nonce) throws InvalidKeyException {
            if (key.length < 32) {
                throw new InvalidKeyException("Key must be at least 32 bytes.");
            }

            // Clamp key
            byte[] clampedKey = new byte[32];
            System.arraycopy(key, 0, clampedKey, 0, 32);
            Poly1305KeyGenerator.clampKey(clampedKey);

            // Initialize the Mac with key and nonce
            mac.init(new ParametersWithIV(new KeyParameter(clampedKey), nonce));
        }

        public byte[] calculateMac(byte[] message) {
            byte[] output = new byte[mac.getMacSize()];
            mac.update(message, 0, message.length);
            mac.doFinal(output, 0);
            return output;
        }
    }
}
