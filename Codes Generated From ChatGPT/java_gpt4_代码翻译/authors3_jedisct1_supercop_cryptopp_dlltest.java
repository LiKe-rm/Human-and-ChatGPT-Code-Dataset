import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.*;
import java.security.spec.*;
import java.util.Arrays;
import java.io.*;

public class CryptoSample {

    public static void main(String[] args) {
        try {
            cryptoSampleApplication();
        } catch (Exception e) {
            System.err.println("Exception occurred: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void cryptoSampleApplication() throws Exception {
        // Encrypt and decrypt
        byte[] key = {
            0x01, 0x23, 0x45, 0x67, 0x89, (byte) 0xab, (byte) 0xcd, (byte) 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, (byte) 0xab, (byte) 0xcd, (byte) 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, (byte) 0xab, (byte) 0xcd, (byte) 0xef
        };
        byte[] iv = {
            0x12, 0x34, 0x56, 0x78, (byte) 0x90, (byte) 0xab, (byte) 0xcd, (byte) 0xef
        };
        byte[] plaintext = {
            0x4e, 0x6f, 0x77, 0x20, 0x69, 0x73, 0x20, 0x74,
            0x68, 0x65, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x20,
            0x66, 0x6f, 0x72, 0x20, 0x61, 0x6c, 0x6c, 0x20
        };
        byte[] ciphertext;
        byte[] decrypted;

        Cipher encryptionCipher = Cipher.getInstance("DESede/CFB/NoPadding");
        encryptionCipher.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key, "DESede"), new IvParameterSpec(iv));
        ciphertext = encryptionCipher.doFinal(plaintext);

        Cipher decryptionCipher = Cipher.getInstance("DESede/CFB/NoPadding");
        decryptionCipher.init(Cipher.DECRYPT_MODE, new SecretKeySpec(key, "DESede"), new IvParameterSpec(iv));
        decrypted = decryptionCipher.doFinal(ciphertext);

        if (!Arrays.equals(plaintext, decrypted)) {
            System.err.println("DES-EDE3-CFB Encryption/decryption failed.");
            System.exit(1);
        }
        System.out.println("1. DES-EDE3-CFB Encryption/decryption succeeded.");

        // Hash
        byte[] message = {'a', 'b', 'c'};
        byte[] expectedDigest = {
            (byte) 0xA9, (byte) 0x99, 0x3E, 0x36, 0x47, 0x06, (byte) 0x81, 0x6A,
            (byte) 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, (byte) 0xC2, 0x6C,
            (byte) 09C, (byte) 0xD0, (byte) 0xD8, (byte) 0x9D
        };
        byte[] digest;
        MessageDigest sha = MessageDigest.getInstance("SHA-1");
        sha.update(message);
        digest = sha.digest();
    
        if (!Arrays.equals(digest, expectedDigest)) {
            System.err.println("SHA-1 hash failed.");
            System.exit(1);
        }
        System.out.println("2. SHA-1 hash succeeded.");
    
        // Generate DSA key
        KeyPairGenerator dsaKeyPairGenerator = KeyPairGenerator.getInstance("DSA");
        dsaKeyPairGenerator.initialize(1024, new SecureRandom());
        KeyPair dsaKeyPair = dsaKeyPairGenerator.generateKeyPair();
        DSAPublicKey dsaPublicKey = (DSAPublicKey) dsaKeyPair.getPublic();
        DSAPrivateKey dsaPrivateKey = (DSAPrivateKey) dsaKeyPair.getPrivate();
    
        System.out.println("3. DSA key generation succeeded.");
    
        // Sign and verify
        Signature dsaSigner = Signature.getInstance("SHA1withDSA");
        dsaSigner.initSign(dsaPrivateKey);
        dsaSigner.update(message);
        byte[] signature = dsaSigner.sign();
    
        Signature dsaVerifier = Signature.getInstance("SHA1withDSA");
        dsaVerifier.initVerify(dsaPublicKey);
        dsaVerifier.update(message);
        boolean isVerified = dsaVerifier.verify(signature);
    
        if (!isVerified) {
            System.err.println("DSA signature and verification failed.");
            System.exit(1);
        }
        System.out.println("4. DSA signature and verification succeeded.");
    
        // Try to verify an invalid signature
        signature[0] ^= 1;
        dsaVerifier.update(message);
        isVerified = dsaVerifier.verify(signature);
        if (isVerified) {
            System.err.println("DSA signature verification failed to detect bad signature.");
            System.exit(1);
        }
        System.out.println("5. DSA signature verification successfully detected bad signature.");
    
        System.out.println("\nCrypto Sample Application completed normally.");
    }
}    