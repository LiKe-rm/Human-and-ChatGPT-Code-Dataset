import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.concurrent.locks.ReentrantLock;

public class LidarNeato {
    private Uart uart;
    private static final int DISTANCES_SIZE = 360;
    private static final short[] distances = new short[DISTANCES_SIZE];
    private static final ReentrantLock distancesLock = new ReentrantLock();

    public LidarNeato(Gpio rx, Uart u) {
        this.uart = u;
        u.configGpio(rx)
                .enable()
                .setMantissa(0x16)
                .setFraction(0x9)
                .enableReceive();

        rx.setDirection(Gpio.Direction.INPUT);
    }

    public LidarNeato readPacket(LidarNeatoPacket packet) throws InterruptedException {
        byte c = 0;
        while (c != (byte) 0xfa) {
            c = uart.readByte();
        }

        packet.index = uart.readByte();
        byte firstSpeed = uart.readByte();
        byte secondSpeed = uart.readByte();
        packet.speed = ByteBuffer.wrap(new byte[]{0, 0, firstSpeed, secondSpeed}).getShort();

        for (int i = 0; i < 4; ++i) {
            byte[] dataBytes = new byte[4];
            for (int j = 0; j < 4; ++j) {
                dataBytes[j] = uart.readByte();
            }
            packet.data[i] = ByteBuffer.wrap(dataBytes).getInt();
        }

        byte firstChecksum = uart.readByte();
        byte secondChecksum = uart.readByte();
        packet.checksum = ByteBuffer.wrap(new byte[]{0, 0, firstChecksum, secondChecksum}).getShort();

        distancesLock.lock();
        try {
            for (int i = 0; i < 4; ++i) {
                int pos = (packet.index - 0xa0) * 4 + i;
                if (pos < 0 || pos >= DISTANCES_SIZE)
                    continue;
                distances[pos] = (short) (packet.data[i] & 0x3fff);
            }
        } finally {
            distancesLock.unlock();
        }

        return this;
    }

    public short getDistance(int angle) {
        distancesLock.lock();
        try {
            return distances[angle];
        } finally {
            distancesLock.unlock();
        }
    }
}

class LidarNeatoPacket {
    public byte index;
    public short speed;
    public int[] data = new int[4];
    public short checksum;
}
