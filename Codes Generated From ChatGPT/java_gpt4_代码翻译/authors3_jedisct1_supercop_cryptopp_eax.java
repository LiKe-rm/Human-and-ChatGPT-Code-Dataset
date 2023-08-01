import org.bouncycastle.crypto.BlockCipher;
import org.bouncycastle.crypto.CipherParameters;
import org.bouncycastle.crypto.Mac;
import org.bouncycastle.crypto.engines.AESEngine;
import org.bouncycastle.crypto.macs.CMac;
import org.bouncycastle.crypto.modes.SICBlockCipher;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.crypto.params.ParametersWithIV;
import org.bouncycastle.util.Arrays;
import org.bouncycastle.util.encoders.Hex;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.nio.ByteBuffer;
import java.security.GeneralSecurityException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

public class EAX {
    private final BlockCipher cipher;
    private final Mac mac;
    private final SICBlockCipher ctr;
    private final byte[] macBuffer;

    public EAX(BlockCipher cipher, Mac mac) {
        this.cipher = cipher;
        this.mac = mac;
        this.ctr = new SICBlockCipher(cipher);
        this.macBuffer = new byte[2 * mac.getMacSize()];
    }

    public void setKey(byte[] key) {
        CipherParameters keyParam = new KeyParameter(key);
        cipher.init(true, keyParam);
        mac.init(keyParam);
    }

    public void resync(byte[] iv) {
        int blockSize = mac.getMacSize();
        Arrays.fill(macBuffer, 0, blockSize, (byte) 0);
        mac.update(macBuffer, 0, blockSize);
        mac.doFinal(macBuffer, blockSize);

        ctr.init(true, new ParametersWithIV(null, macBuffer, blockSize, blockSize));
    }

    public byte[] process(byte[] data, int offset, int length) {
        byte[] output = new byte[length];
        ctr.processBytes(data, offset, length, output, 0);
        mac.update(output, 0, length);
        return output;
    }

    public byte[] getTag(int tagSize) {
        byte[] tag = new byte[tagSize];
        mac.doFinal(tag, 0);
        for (int i = 0; i < tagSize; i++) {
            tag[i] ^= macBuffer[mac.getMacSize() + i];
        }
        return tag;
    }

    public static void main(String[] args) throws GeneralSecurityException {
        byte[] key = Hex.decode("000102030405060708090A0B0C0D0E0F");
        byte[] iv = Hex.decode("101112131415161718191A1B1C1D1E1F");
        byte[] plaintext = Hex.decode("202122232425262728292A2B2C2D2E2F3031323334353637");

        EAX eax = new EAX(new AESEngine(), new CMac(new AESEngine()));
        eax.setKey(key);
        eax.resync(iv);

        byte[] ciphertext = eax.process(plaintext, 0, plaintext.length);
        byte[] tag = eax.getTag(16);

        System.out.println("Ciphertext: " + Hex.toHexString(ciphertext));
        System.out.println("Tag: " + Hex.toHexString(tag));
    }
}
