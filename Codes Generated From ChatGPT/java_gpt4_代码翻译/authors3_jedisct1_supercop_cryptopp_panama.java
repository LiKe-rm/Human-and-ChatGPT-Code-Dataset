import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class Panama {

    private static final int STATE_SIZE = 34;
    private int[] state = new int[STATE_SIZE];
    private int[] buffer = new int[32];
    private int bufferIndex = 0;

    public Panama() {
        reset();
    }

    public void reset() {
        Arrays.fill(state, 0);
        Arrays.fill(buffer, 0);
        bufferIndex = 0;
    }

    private void gammaAndPi(int[] x) {
        int[] temp = new int[17];
        System.arraycopy(x, 0, temp, 0, 17);

        for (int i = 0; i < 17; i++) {
            int index = (5 * i) % 17;
            x[index] = temp[i] >>> (index * (index + 1) / 2 % 32);
        }
    }

    private void theta(int[] x) {
        int[] temp = new int[17];
        System.arraycopy(x, 0, temp, 0, 17);

        for (int i = 0; i < 17; i++) {
            int index = (i + 1) % 17;
            x[i] = temp[i] ^ temp[index];
        }
    }

    private void outputKeystream(int[] z, int[] y) {
        int[] temp = new int[17];
        System.arraycopy(state, 0, temp, 0, 17);

        gammaAndPi(temp);
        theta(temp);

        for (int i = 0; i < 8; i++) {
            z[i] = temp[i] ^ y[i];
        }
    }

    public void process(byte[] data, int offset, int length) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(data, offset, length);
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN);

        while (byteBuffer.hasRemaining()) {
            int[] z = new int[8];
            int[] y = new int[8];

            for (int i = 0; i < 8 && byteBuffer.hasRemaining(); i++) {
                y[i] = byteBuffer.getInt();
            }

            outputKeystream(z, y);

            for (int i = 0; i < 8 && byteBuffer.hasRemaining(); i++) {
                int output = z[i] ^ buffer[bufferIndex];
                byteBuffer.putInt(output);
                buffer[bufferIndex] = y[i];
                bufferIndex = (bufferIndex + 1) % 32;
            }
        }
    }
}
