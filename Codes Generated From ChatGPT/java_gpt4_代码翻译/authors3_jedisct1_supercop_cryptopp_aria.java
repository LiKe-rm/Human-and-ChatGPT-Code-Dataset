import org.bouncycastle.crypto.BlockCipher;
import org.bouncycastle.crypto.engines.ARIAEngine;
import org.bouncycastle.crypto.params.KeyParameter;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ARIAJava {
    public static void main(String[] args) {
        byte[] key = new byte[]{/* Your key bytes here */};
        byte[] input = new byte[]{/* Your input bytes here */};
        byte[] output = new byte[input.length];

        ARIAEngine ariaEngine = new ARIAEngine();
        KeyParameter keyParameter = new KeyParameter(key);
        ariaEngine.init(true, keyParameter);

        for (int i = 0; i < input.length; i += ariaEngine.getBlockSize()) {
            ariaEngine.processBlock(input, i, output, i);
        }

        System.out.println("Encrypted:");
        for (byte b : output) {
            System.out.print(String.format("%02X", b));
        }
        System.out.println();
    }
}
