import java.util.Arrays;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

public class CMAC {

    private byte[] reg;
    private byte[] k1;
    private byte[] k2;
    private int counter;
    private Cipher cipher;

    public CMAC(byte[] key) throws Exception {
        this.cipher = Cipher.getInstance("AES/ECB/NoPadding");
        SecretKey secretKey = new SecretKeySpec(key, "AES");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);

        int blockSize = cipher.getBlockSize();
        reg = new byte[blockSize];
        k1 = new byte[blockSize];
        k2 = new byte[blockSize];
        counter = 0;

        byte[] zeroBlock = new byte[blockSize];
        k1 = cipher.doFinal(zeroBlock);
        mulU(k1);
        System.arraycopy(k1, 0, k2, 0, blockSize);
        mulU(k2);
    }

    private void mulU(byte[] k) {
        byte carry = 0;
        int len = k.length;

        for (int i = len - 1; i >= 1; i -= 2) {
            byte carry2 = (byte) (k[i] >>> 7);
            k[i] = (byte) (k[i] + k[i] + carry);
            carry = (byte) (k[i - 1] >>> 7);
            k[i - 1] = (byte) (k[i - 1] + k[i - 1] + carry2);
        }

        if (carry != 0) {
            k[len - 1] ^= 0x87;
        }
    }

    public void update(byte[] input) {
        int blockSize = cipher.getBlockSize();
        if (counter > 0) {
            int len = Math.min(blockSize - counter, input.length);
            xorbuf(reg, counter, input, 0, len);
            input = Arrays.copyOfRange(input, len, input.length);
            counter += len;

            if (counter == blockSize && input.length > 0) {
                try {
                    reg = cipher.doFinal(reg);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                counter = 0;
            }
        }

        while (input.length > blockSize) {
            xorbuf(reg, 0, input, 0, blockSize);
            try {
                reg = cipher.doFinal(reg);
            } catch (Exception e) {
                e.printStackTrace();
            }
            input = Arrays.copyOfRange(input, blockSize, input.length);
        }

        if (input.length > 0) {
            xorbuf(reg, counter, input, 0, input.length);
            counter += input.length;
        }
    }

    public byte[] doFinal(int macSize) {
        byte[] mac = new byte[macSize];
        if (counter < cipher.getBlockSize()) {
            reg[counter] ^= 0x80;
            xorbuf(reg, 0, k2, 0, cipher.getBlockSize());
        } else {
            xorbuf(reg, 0, k1, 0, cipher.getBlockSize());
        }

        try {
            reg = cipher.doFinal(reg);
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.arraycopy(reg, 0, mac, 0, macSize);
        return mac;
    }

    private void xorbuf(byte[] dest, int destPos, byte[] src, int srcPos, int len) {
        for (int i = 0; i < len; i++) {
            dest[destPos + i] ^= src[srcPos + i];
        }
    }
    
    public static void main(String[] args) {
        try {
            byte[] key = new byte[16];
            byte[] data = new byte[100];
    
            CMAC cmac = new CMAC(key);
            cmac.update(data);
            byte[] mac = cmac.doFinal(16);
    
            System.out.println("MAC: " + bytesToHex(mac));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}