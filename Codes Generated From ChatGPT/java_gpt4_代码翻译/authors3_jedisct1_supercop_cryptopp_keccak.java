import java.nio.ByteBuffer;
import java.util.Arrays;

public class Keccak extends IteratedHashBase {
    private static final int KECCAK_STATE_SIZE = 25 * Long.BYTES;

    public Keccak(int blockSize, int digestSize) {
        super(blockSize, KECCAK_STATE_SIZE);
    }

    @Override
    public void init() {
        Arrays.fill(dataBuf, (byte) 0);
        Arrays.fill(stateBuf, (byte) 0);
    }

    @Override
    public void hashBlock(byte[] data) {
        if (data == null || data.length != blockSize) {
            throw new IllegalArgumentException("Invalid data block size");
        }

        ByteBuffer stateBuffer = ByteBuffer.wrap(stateBuf);
        ByteBuffer dataBuffer = ByteBuffer.wrap(data);

        for (int i = 0; i < blockSize; i++) {
            stateBuf[i] ^= data[i];
        }

        KeccakF1600(stateBuf);
    }

    private void KeccakF1600(byte[] state) {
        // Keccak core function implementation
    }

    @Override
    public byte[] digest(int size) {
        byte[] truncatedDigest = new byte[size];
        stateBuf[countLo % blockSize] ^= 0x01;
        stateBuf[blockSize - 1] ^= 0x80;

        KeccakF1600(stateBuf);
        System.arraycopy(stateBuf, 0, truncatedDigest, 0, size);
        restart();

        return truncatedDigest;
    }

    @Override
    public String getAlgorithmName() {
        return "Keccak";
    }

    @Override
    public ByteOrder getByteOrder() {
        return ByteOrder.LITTLE_ENDIAN;
    }
}
