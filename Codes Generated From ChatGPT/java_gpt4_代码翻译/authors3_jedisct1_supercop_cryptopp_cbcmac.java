import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

import javax.crypto.NoSuchPaddingException;

public class CBCMac {

    private Cipher cipher;
    private byte[] reg;
    private int counter;

    public CBCMac() {
    }

    public void uncheckedSetKey(byte[] key, String transformation) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, InvalidAlgorithmParameterException {
        cipher = Cipher.getInstance(transformation);
        SecretKeySpec keySpec = new SecretKeySpec(key, "AES");
        IvParameterSpec ivSpec = new IvParameterSpec(new byte[cipher.getBlockSize()]);
        cipher.init(Cipher.ENCRYPT_MODE, keySpec, ivSpec);

        reg = new byte[cipher.getBlockSize()];
        counter = 0;
    }

    public void update(byte[] input) throws ShortBufferException {
        int blockSize = cipher.getBlockSize();

        for (byte b : input) {
            reg[counter++] ^= b;
            if (counter == blockSize) {
                processBuf();
            }
        }
    }

    public byte[] truncatedFinal(int size) {
        if (counter != 0) {
            processBuf();
        }

        byte[] mac = Arrays.copyOf(reg, size);
        Arrays.fill(reg, (byte) 0);
        return mac;
    }

    private void processBuf() {
        try {
            cipher.doFinal(reg, 0, reg.length, reg, 0);
            counter = 0;
        } catch (IllegalBlockSizeException | BadPaddingException | ShortBufferException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        CBCMac cbcMac = new CBCMac();
        byte[] key = "samplekey1234567".getBytes();
        byte[] data = "Sample text to be authenticated".getBytes();

        try {
            cbcMac.uncheckedSetKey(key, "AES/CBC/NoPadding");
            cbcMac.update(data);
            byte[] mac = cbcMac.truncatedFinal(16);
            System.out.println("Generated MAC: " + Arrays.toString(mac));
        } catch (NoSuchAlgorithmException | NoSuchPaddingException | InvalidKeyException | InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        }
    }
}
