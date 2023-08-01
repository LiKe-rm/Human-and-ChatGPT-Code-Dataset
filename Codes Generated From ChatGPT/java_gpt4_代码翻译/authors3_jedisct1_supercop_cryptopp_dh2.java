import javax.crypto.KeyAgreement;
import java.security.*;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;

public class DH2 {
    private KeyAgreement keyAgreement1;
    private KeyAgreement keyAgreement2;

    public DH2(KeyAgreement keyAgreement1, KeyAgreement keyAgreement2) {
        this.keyAgreement1 = keyAgreement1;
        this.keyAgreement2 = keyAgreement2;
    }

    public boolean agree(byte[] agreedValue,
                         PrivateKey staticSecretKey, PrivateKey ephemeralSecretKey,
                         byte[] staticOtherPublicKey, byte[] ephemeralOtherPublicKey,
                         boolean validateStaticOtherPublicKey) {
        try {
            KeyFactory keyFactory = KeyFactory.getInstance("DH");
            PublicKey staticOtherPublicKeyObj = keyFactory.generatePublic(new X509EncodedKeySpec(staticOtherPublicKey));
            PublicKey ephemeralOtherPublicKeyObj = keyFactory.generatePublic(new X509EncodedKeySpec(ephemeralOtherPublicKey));

            keyAgreement1.init(staticSecretKey);
            keyAgreement1.doPhase(staticOtherPublicKeyObj, validateStaticOtherPublicKey);
            byte[] agreedValue1 = keyAgreement1.generateSecret();

            keyAgreement2.init(ephemeralSecretKey);
            keyAgreement2.doPhase(ephemeralOtherPublicKeyObj, true);
            byte[] agreedValue2 = keyAgreement2.generateSecret();

            System.arraycopy(agreedValue1, 0, agreedValue, 0, agreedValue1.length);
            System.arraycopy(agreedValue2, 0, agreedValue, agreedValue1.length, agreedValue2.length);

            return true;
        } catch (InvalidKeyException | NoSuchAlgorithmException | InvalidKeySpecException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        try {
            KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("DH");
            keyPairGenerator.initialize(2048);
            KeyPair keyPair1 = keyPairGenerator.generateKeyPair();
            KeyPair keyPair2 = keyPairGenerator.generateKeyPair();

            KeyAgreement keyAgreement1 = KeyAgreement.getInstance("DH");
            KeyAgreement keyAgreement2 = KeyAgreement.getInstance("DH");

            DH2 dh2 = new DH2(keyAgreement1, keyAgreement2);

            byte[] agreedValue = new byte[512];
            boolean result = dh2.agree(agreedValue,
                    keyPair1.getPrivate(), keyPair2.getPrivate(),
                    keyPair1.getPublic().getEncoded(), keyPair2.getPublic().getEncoded(),
                    true);

            System.out.println("Agreement: " + result);
            System.out.println("Agreed value: " + byteArrayToHexString(agreedValue));
        } catch (NoSuchAlgorithmException | InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        }
    }

    public static String byteArrayToHexString(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}
