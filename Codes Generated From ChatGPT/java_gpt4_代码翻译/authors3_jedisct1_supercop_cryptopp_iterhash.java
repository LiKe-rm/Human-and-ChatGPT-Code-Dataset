import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public abstract class IteratedHashBase {
    protected long countLo, countHi;
    protected int blockSize;
    protected byte[] dataBuf;
    protected byte[] stateBuf;

    public IteratedHashBase(int blockSize, int stateSize) {
        this.blockSize = blockSize;
        this.dataBuf = new byte[blockSize];
        this.stateBuf = new byte[stateSize];
        this.countLo = 0;
        this.countHi = 0;
    }

    public void update(byte[] input, int length) {
        if (input == null || length == 0) {
            return;
        }

        long oldCountLo = countLo;
        long oldCountHi = countHi;
        if ((countLo = oldCountLo + length) < oldCountLo) {
            countHi++;
        }
        countHi += length >>> (8 * Long.BYTES);

        int num = (int) (oldCountLo % blockSize);
        if (num != 0) {
            if (num + length >= blockSize) {
                System.arraycopy(input, 0, dataBuf, num, blockSize - num);
                hashBlock(dataBuf);
                input = Arrays.copyOfRange(input, blockSize - num, input.length);
                length -= (blockSize - num);
                num = 0;
            } else {
                System.arraycopy(input, 0, dataBuf, num, length);
                return;
            }
        }

        while (length >= blockSize) {
            System.arraycopy(input, 0, dataBuf, 0, blockSize);
            hashBlock(dataBuf);
            input = Arrays.copyOfRange(input, blockSize, input.length);
            length -= blockSize;
        }

        if (input != null) {
            System.arraycopy(input, 0, dataBuf, 0, length);
        }
    }

    public byte[] createUpdateSpace(int[] size) {
        int num = (int) (countLo % blockSize);
        size[0] = blockSize - num;
        return Arrays.copyOfRange(dataBuf, num, dataBuf.length);
    }

    public void padLastBlock(int lastBlockSize, byte padFirst) {
        int num = (int) (countLo % blockSize);
        dataBuf[num++] = padFirst;

        if (num <= lastBlockSize) {
            Arrays.fill(dataBuf, num, lastBlockSize, (byte) 0);
        } else {
            Arrays.fill(dataBuf, num, blockSize, (byte) 0);
            hashBlock(dataBuf);
            Arrays.fill(dataBuf, 0, lastBlockSize, (byte) 0);
        }
    }

    public void restart() {
        countLo = countHi = 0;
        init();
    }

    public abstract void init();

    public abstract void hashBlock(byte[] data);

    public abstract byte[] digest(int size);

    public abstract String getAlgorithmName();

    public abstract ByteOrder getByteOrder();

    public long getBitCountLo() {
        return countLo * 8;
    }

    public long getBitCountHi() {
        return countHi * 8;
    }
}
