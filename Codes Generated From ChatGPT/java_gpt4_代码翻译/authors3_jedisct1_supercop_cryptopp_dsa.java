import java.math.BigInteger;
import java.security.Signature;
import java.security.KeyPairGenerator;
import java.security.KeyPair;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidKeyException;
import java.security.SignatureException;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.DSAPrivateKeySpec;
import java.security.spec.DSAPublicKeySpec;
import java.security.KeyFactory;
import java.io.IOException;
import org.bouncycastle.asn1.ASN1Integer;
import org.bouncycastle.asn1.ASN1Sequence;
import org.bouncycastle.asn1.DERSequence;
import org.bouncycastle.asn1.DEROctetString;
import org.bouncycastle.util.BigIntegers;
import org.bouncycastle.util.Arrays;

public class DSAConverter {

    public enum DSASignatureFormat {
        DSA_P1363, DSA_DER, DSA_OPENPGP
    }

    public static byte[] dsaConvertSignatureFormat(byte[] signature, DSASignatureFormat toFormat, DSASignatureFormat fromFormat)
            throws IOException {

        BigInteger r, s;

        switch (fromFormat) {
            case DSA_P1363:
                int halfLen = signature.length / 2;
                r = new BigInteger(1, Arrays.copyOfRange(signature, 0, halfLen));
                s = new BigInteger(1, Arrays.copyOfRange(signature, halfLen, signature.length));
                break;
            case DSA_DER:
                ASN1Sequence seq = ASN1Sequence.getInstance(signature);
                r = ASN1Integer.getInstance(seq.getObjectAt(0)).getValue();
                s = ASN1Integer.getInstance(seq.getObjectAt(1)).getValue();
                break;
            case DSA_OPENPGP:
                // OpenPGP format not supported in this example
                throw new UnsupportedOperationException("DSA_OPENPGP format not supported in this example");
            default:
                throw new IllegalArgumentException("Invalid fromFormat");
        }

        byte[] result;

        switch (toFormat) {
            case DSA_P1363:
                byte[] rBytes = BigIntegers.asUnsignedByteArray(r);
                byte[] sBytes = BigIntegers.asUnsignedByteArray(s);
                result = new byte[rBytes.length + sBytes.length];
                System.arraycopy(rBytes, 0, result, 0, rBytes.length);
                System.arraycopy(sBytes, 0, result, rBytes.length, sBytes.length);
                break;
            case DSA_DER:
                ASN1Integer asn1R = new ASN1Integer(r);
                ASN1Integer asn1S = new ASN1Integer(s);
                DERSequence derSeq = new DERSequence(new ASN1Integer[]{asn1R, asn1S});
                result = derSeq.getEncoded();
                break;
            case DSA_OPENPGP:
                // OpenPGP format not supported in this example
                throw new UnsupportedOperationException("DSA_OPENPGP format not supported in this example");
            default:
                throw new IllegalArgumentException("Invalid toFormat");
        }

        return result;
    }

    public static void main(String[] args)
            throws NoSuchAlgorithmException, InvalidKeyException, SignatureException, IOException {
        // Generate a DSA key pair
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("DSA");
        keyPairGenerator.initialize(1024);
        KeyPair keyPair = keyPairGenerator.generateKeyPair();

        // Sign a message
        byte[] message = "Hello, World!".getBytes();
        Signature signer = Signature.getInstance("SHA1withDSA");
        signer.initSign(keyPair.getPrivate());
        signer.update(message);
        byte[] signature = signer.sign();

        // Convert
        try {
            byte[] p1363Signature = dsaConvertSignatureFormat(signature, DSASignatureFormat.DSA_P1363, DSASignatureFormat.DSA_DER);

            // Verify the signature using the P1363 format
            Signature verifier = Signature.getInstance("SHA1withDSA");
            verifier.initVerify(keyPair.getPublic());
            verifier.update(message);
            boolean isVerified = verifier.verify(p1363Signature);

            System.out.println("Signature verified using P1363 format: " + isVerified);

            // Convert the signature format from P1363 back to DER
            byte[] derSignature = dsaConvertSignatureFormat(p1363Signature, DSASignatureFormat.DSA_DER, DSASignatureFormat.DSA_P1363);

            // Verify the signature using the DER format
            verifier.initVerify(keyPair.getPublic());
            verifier.update(message);
            isVerified = verifier.verify(derSignature);

            System.out.println("Signature verified using DER format: " + isVerified);
        } catch (IOException e) {
            System.err.println("Error while converting signature format: " + e.getMessage());
        } catch (IllegalArgumentException | UnsupportedOperationException e) {
            System.err.println("Invalid format or unsupported operation: " + e.getMessage());
        }
    }
}
