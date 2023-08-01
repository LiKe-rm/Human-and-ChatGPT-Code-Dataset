import java.security.GeneralSecurityException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Signature;
import java.security.spec.ECGenParameterSpec;
import java.util.concurrent.atomic.AtomicBoolean;

public class FIPS140 {
    private static final boolean ENABLE_FIPS_140_2_COMPLIANCE = false;
    private static AtomicBoolean powerUpSelfTestStatus = new AtomicBoolean(false);
    private static ThreadLocal<Boolean> selfTestInProgress = ThreadLocal.withInitial(() -> false);

    public static boolean isFIPS140ComplianceEnabled() {
        return ENABLE_FIPS_140_2_COMPLIANCE;
    }

    public static void setPowerUpSelfTestStatus(boolean status) {
        powerUpSelfTestStatus.set(status);
    }

    public static boolean getPowerUpSelfTestStatus() {
        return powerUpSelfTestStatus.get();
    }

    public static boolean isPowerUpSelfTestInProgress() {
        return selfTestInProgress.get();
    }

    public static void setPowerUpSelfTestInProgress(boolean inProgress) {
        selfTestInProgress.set(inProgress);
    }

    public static void signaturePairwiseConsistencyTestFIPS140(KeyPair keyPair, String algorithm)
            throws GeneralSecurityException {
        if (!ENABLE_FIPS_140_2_COMPLIANCE) {
            return;
        }

        PublicKey publicKey = keyPair.getPublic();
        PrivateKey privateKey = keyPair.getPrivate();

        Signature signer = Signature.getInstance(algorithm);
        signer.initSign(privateKey);

        byte[] message = "test message".getBytes();
        signer.update(message);
        byte[] signature = signer.sign();

        Signature verifier = Signature.getInstance(algorithm);
        verifier.initVerify(publicKey);
        verifier.update(message);

        if (!verifier.verify(signature)) {
            throw new GeneralSecurityException("FIPS 140-2: Signature pairwise consistency test failed");
        }
    }

    public static void main(String[] args) throws NoSuchAlgorithmException, GeneralSecurityException {
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("EC");
        keyPairGenerator.initialize(new ECGenParameterSpec("secp256r1"));

        KeyPair keyPair = keyPairGenerator.generateKeyPair();
        signaturePairwiseConsistencyTestFIPS140(keyPair, "SHA256withECDSA");
    }
}
