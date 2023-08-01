import java.awt.*;
import java.nio.ByteBuffer;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

public class NewRandom {
    private static final int INTRAND_SIZE = 256;
    private static final AtomicInteger instanceCounter = new AtomicInteger(0);
    private static final int[] xorShiftState = new int[4];

    private byte[] pseudoRandom;
    private int counter;

    public NewRandom() {
        reset();
        initialize();
    }

    private void reset() {
        pseudoRandom = new byte[INTRAND_SIZE];
        counter = 0;
    }

    private void initialize() {
        ByteBuffer buffer = ByteBuffer.wrap(pseudoRandom);

        instanceCounter.incrementAndGet();
        reset();

        buffer.putInt((int) System.currentTimeMillis());

        Point cursorPosition = MouseInfo.getPointerInfo().getLocation();
        buffer.putInt(cursorPosition.x);
        buffer.putInt(cursorPosition.y);

        buffer.putInt(new Random().nextInt());

        buffer.putInt(Runtime.getRuntime().availableProcessors());

        buffer.putInt(System.identityHashCode(System.in));
        buffer.putInt(System.identityHashCode(System.out));
        buffer.putInt(System.identityHashCode(System.err));

        buffer.putInt(Thread.currentThread().hashCode());
        buffer.putInt(System.identityHashCode(Thread.currentThread().getThreadGroup()));

        for (int i = 0; i < 4; i++) {
            xorShiftState[i] = new Random().nextInt();
        }
    }

    public void getRandomBuffer(byte[] buffer, int size) {
        try {
            MessageDigest sha256 = MessageDigest.getInstance("SHA-256");
            ByteBuffer counterBuffer = ByteBuffer.allocate(4);
            int bytesLeft = size;

            while (bytesLeft > 0) {
                counter++;
                counterBuffer.putInt(0, counter);

                sha256.reset();
                sha256.update(pseudoRandom);
                sha256.update(counterBuffer.array());
                byte[] temp = sha256.digest();

                int bytesToCopy = Math.min(bytesLeft, 32);
                System.arraycopy(temp, 0, buffer, size - bytesLeft, bytesToCopy);

                bytesLeft -= bytesToCopy;
            }
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("SHA-256 algorithm not found.", e);
        }
    }

    public static int randXorShift() {
        int tmp = xorShiftState[0] ^ (xorShiftState[0] << 15);
        System.arraycopy(xorShiftState, 1, xorShiftState, 0, 3);
        xorShiftState[3] = xorShiftState[3] ^ (xorShiftState[3] >>> 21) ^ (tmp ^ (tmp >>> 4));
        return xorShiftState[3];
    }

    public static void randCreateUUID(byte[] uuid16, NewRandom randomSource) {
        ByteBuffer buffer = ByteBuffer.wrap(uuid16);
        buffer.putLong(System.currentTimeMillis());
        buffer.putLong(randXorShift());
        randomSource.getRandomBuffer(uuid16, uuid16.length);
    }

    public static void main(String[] args) {
        NewRandom random = new NewRandom();
        byte[] buffer = new byte[16];
        random.getRandomBuffer(buffer, buffer.length);

        for (byte b : buffer) {
            System.out.printf("%02X ", b);
        }
        System.out.println();

        byte[] uuid = new byte[16];
        randCreateUUID(uuid, random);

        for (byte b : uuid) {
            System.out.printf("%02X ", b);
        }
        System.out.println();
    }
}
