import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;

public class DARN {
    private SecureRandom random;
    private byte[] temp;

    public DARN() throws NoSuchAlgorithmException {
        random = SecureRandom.getInstance("SHA1PRNG");
        temp = new byte[8];
    }

    public void generateBlock(byte[] output, int size) {
        if (size == 0) {
            return;
        }
        int i = 0;

        int alignment = ByteBuffer.wrap(output).order(ByteOrder.nativeOrder()).getInt() & 0x7;
        if (alignment != 0) {
            random.nextBytes(temp);
            System.arraycopy(temp, 0, output, 0, alignment);

            i += alignment;
            size -= alignment;
        }

        while (i < size) {
            int blockSize = Math.min(8, size - i);
            random.nextBytes(temp);
            System.arraycopy(temp, 0, output, i, blockSize);
            i += blockSize;
        }
    }

    public void discardBytes(int n) {
        n = (n + 7) & ~7; // Round up to a multiple of 8

        byte[] discard = new byte[16];
        int count = Math.min(n, discard.length);
        while (count > 0) {
            generateBlock(discard, count);
            n -= count;
            count = Math.min(n, discard.length);
        }
    }

    public static void main(String[] args) throws NoSuchAlgorithmException {
        DARN darn = new DARN();
        byte[] output = new byte[32];
        darn.generateBlock(output, output.length);
        System.out.println(Arrays.toString(output));

        darn.discardBytes(24);
    }
}
