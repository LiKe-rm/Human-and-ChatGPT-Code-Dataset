import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

import javax.crypto.KeyAgreement;
import javax.crypto.interfaces.DHPublicKey;
import javax.crypto.spec.DHParameterSpec;
import javax.crypto.spec.DHPublicKeySpec;
import javax.crypto.spec.SecretKeySpec;

public class CryptoUtils {

    public static boolean agree(byte[] agreedValue,
                                byte[] staticSecretKey, byte[] ephemeralSecretKey,
                                byte[] staticOtherPublicKey, byte[] ephemeralOtherPublicKey,
                                boolean validateStaticOtherPublicKey) {
        try {
            KeyAgreement keyAgreement = KeyAgreement.getInstance("DH");
            DHPublicKey staticOtherPubKey = bytesToDHPublicKey(staticOtherPublicKey);
            DHPublicKey ephemeralOtherPubKey = bytesToDHPublicKey(ephemeralOtherPublicKey);

            byte[] agreedValue1 = performKeyAgreement(keyAgreement, staticSecretKey, staticOtherPubKey);
            byte[] agreedValue2 = performKeyAgreement(keyAgreement, ephemeralSecretKey, ephemeralOtherPubKey);

            System.arraycopy(agreedValue1, 0, agreedValue, 0, agreedValue1.length);
            System.arraycopy(agreedValue2, 0, agreedValue, agreedValue1.length, agreedValue2.length);

            return true;
        } catch (NoSuchAlgorithmException | InvalidKeySpecException | InvalidKeyException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static byte[] performKeyAgreement(KeyAgreement keyAgreement, byte[] secretKey, DHPublicKey otherPubKey)
            throws InvalidKeyException, NoSuchAlgorithmException {
        DHParameterSpec params = otherPubKey.getParams();
        DHPublicKeySpec publicKeySpec = new DHPublicKeySpec(otherPubKey.getY(), params.getP(), params.getG());
        keyAgreement.init(secretKey, publicKeySpec);
        keyAgreement.doPhase(otherPubKey, true);
        byte[] agreedValue = keyAgreement.generateSecret();
        return agreedValue;
    }

    private static DHPublicKey bytesToDHPublicKey(byte[] publicKeyBytes)
            throws NoSuchAlgorithmException, InvalidKeySpecException {
        // Deserialize the DHPublicKey from the byte array, implementing this method depends on the chosen serialization
        // format for public keys.
        // Placeholder code (replace with actual deserialization):
        SecureRandom random = new SecureRandom();
        BigInteger p = BigInteger.probablePrime(1024, random);
        BigInteger g = BigInteger.probablePrime(1024, random);
        BigInteger y = new BigInteger(publicKeyBytes);
        DHParameterSpec dhParamSpec = new DHParameterSpec(p, g);
        DHPublicKeySpec dhPublicKeySpec = new DHPublicKeySpec(y, p, g);
        KeyFactory keyFactory = KeyFactory.getInstance("DH");
        DHPublicKey dhPublicKey = (DHPublicKey) keyFactory.generatePublic(dhPublicKeySpec);
        return dhPublicKey;
    }
}
