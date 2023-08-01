import java.security.InvalidKeyException;
import java.util.Arrays;

public class ARC4Base {
    private static final int STATE_SIZE = 256;

    private byte[] state = new byte[STATE_SIZE];
    private int x;
    private int y;

    public ARC4Base() {
        x = y = 0;
    }

    public void setKey(byte[] key) throws InvalidKeyException {
        if (key == null || key.length == 0) {
            throw new InvalidKeyException("Invalid key length");
        }

        x = 1;
        y = 0;

        for (int i = 0; i < STATE_SIZE; i++) {
            state[i] = (byte) i;
        }

        int keyIndex = 0, stateIndex = 0;
        for (int i = 0; i < STATE_SIZE; i++) {
            int a = state[i] & 0xFF;
            stateIndex += (key[keyIndex] & 0xFF) + a;
            stateIndex &= 0xFF;
            state[i] = state[stateIndex];
            state[stateIndex] = (byte) a;
            if (++keyIndex >= key.length) {
                keyIndex = 0;
            }
        }
    }

    private int makeByte() {
        int a = state[x] & 0xFF;
        y = (y + a) & 0xFF;
        int b = state[y] & 0xFF;
        state[x] = (byte) b;
        state[y] = (byte) a;
        x = (x + 1) & 0xFF;
        return state[(a + b) & 0xFF];
    }

    public void generateBlock(byte[] output) {
        for (int i = 0; i < output.length; i++) {
            output[i] = (byte) makeByte();
        }
    }

    public void processData(byte[] out, byte[] in) {
        for (int i = 0; i < in.length; i++) {
            out[i] = (byte) (in[i] ^ makeByte());
        }
    }

    public void discardBytes(int n) {
        for (int i = 0; i < n; i++) {
            makeByte();
        }
    }

    public static void main(String[] args) throws InvalidKeyException {
        byte[] key = "test-key".getBytes();
        byte[] input = "Hello, World!".getBytes();
        byte[] output = new byte[input.length];

        ARC4Base arc4 = new ARC4Base();
        arc4.setKey(key);
        arc4.processData(output, input);

        System.out.println("Encrypted: " + Arrays.toString(output));

        arc4.setKey(key);
        arc4.processData(output, output);

        System.out.println("Decrypted: " + new String(output));
    }
}
