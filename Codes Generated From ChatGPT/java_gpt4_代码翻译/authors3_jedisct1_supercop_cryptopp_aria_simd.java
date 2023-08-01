import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class AriaSimd {
    private static final int[] S1 = new int[256];
    private static final int[] S2 = new int[256];
    private static final int[] X1 = new int[256];
    private static final int[] X2 = new int[256];
    private static final int[][] KRK = new int[3][4];

    public static void main(String[] args) {
        // Test data
        byte[] rk = new byte[16];
        int[] ws = new int[32];
        int keylen = 16;
        byte[] xorBlock = new byte[16];
        byte[] outBlock = new byte[16];

        uncheckedSetKeyScheduleNEON(rk, ws, keylen);
        processAndXorBlockNEON(xorBlock, outBlock, rk, ws);
    }

    private static byte ariaBrf(int x, int y) {
        return (byte) (x >>> (8 * y));
    }

    private static void ariaGsrkNEON(int n, ByteBuffer x, ByteBuffer y, ByteBuffer rk) {
        int q1 = (4 - (n / 32)) % 4;
        int q2 = (3 - (n / 32)) % 4;
        int r = n % 32;

        ByteBuffer temp = ByteBuffer.allocate(16).order(ByteOrder.LITTLE_ENDIAN);
        y.position(q1 * 4);
        temp.putInt(y.getInt());
        temp.putInt(y.getInt());
        temp.putInt(y.getInt());
        temp.putInt(y.getInt());
        y.position(0);
        temp.position(0);

        temp.putInt(temp.getInt(0) >>> r | temp.getInt(4) << (32 - r));
        temp.putInt(temp.getInt(4) >>> r | temp.getInt(8) << (32 - r));
        temp.putInt(temp.getInt(8) >>> r | temp.getInt(12) << (32 - r));
        temp.putInt(temp.getInt(12) >>> r | temp.getInt(0) << (32 - r));

        temp.position(0);
        y.position(q2 * 4);
        temp.putInt(temp.getInt(0) ^ (y.getInt() << (32 - r)));
        temp.putInt(temp.getInt(4) ^ (y.getInt() << (32 - r)));
        temp.putInt(temp.getInt(8) ^ (y.getInt() << (32 - r)));
        temp.putInt(temp.getInt(12) ^ (y.getInt() << (32 - r)));

        temp.position(0);
        rk.putInt(x.getInt(0) ^ temp.getInt(0));
        rk.putInt(x.getInt(4) ^ temp.getInt(4));
        rk.putInt(x.getInt(8) ^ temp.getInt(8));
        rk.putInt(x.getInt(12) ^ temp.getInt(12));
    }

    private static void uncheckedSetKeyScheduleNEON(byte[] rk, int[] ws, int keylen) {
        ByteBuffer w0 = ByteBuffer.wrap(rk, 0, 16).order(ByteOrder.LITTLE_ENDIAN);
        ByteBuffer w1 = ByteBuffer.wrap(rk, 16, 16).order(ByteOrder.LITTLE_ENDIAN);
        ByteBuffer w2 = ByteBuffer.wrap(rk, 32, 16).order(ByteOrder.LITTLE_ENDIAN);
        ByteBuffer w3 = ByteBuffer.wrap(rk, 48, 16).order(ByteOrder.LITTLE_ENDIAN);

        ariaGsrkNEON(19, w0, w1, ByteBuffer.wrap(rk, 0, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(19, w1, w2, ByteBuffer.wrap(rk, 16, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(19, w2, w3, ByteBuffer.wrap(rk, 32, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(19, w3, w0, ByteBuffer.wrap(rk, 48, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(31, w0, w1, ByteBuffer.wrap(rk, 64, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(31, w1, w2, ByteBuffer.wrap(rk, 80, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(31, w2, w3, ByteBuffer.wrap(rk, 96, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(31, w3, w0, ByteBuffer.wrap(rk, 112, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(67, w0, w1, ByteBuffer.wrap(rk, 128, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(67, w1, w2, ByteBuffer.wrap(rk, 144, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(67, w2, w3, ByteBuffer.wrap(rk, 160, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(67, w3, w0, ByteBuffer.wrap(rk, 176, 16).order(ByteOrder.LITTLE_ENDIAN));
        ariaGsrkNEON(97, w0, w1, ByteBuffer.wrap(rk, 192, 16).order(ByteOrder.LITTLE_ENDIAN));
        if (keylen > 16) {
            ariaGsrkNEON(97, w1, w2, ByteBuffer.wrap(rk, 208, 16).order(ByteOrder.LITTLE_ENDIAN));
            ariaGsrkNEON(97, w2, w3, ByteBuffer.wrap(rk, 224, 16).order(ByteOrder.LITTLE_ENDIAN));
    
            if (keylen > 24) {
                ariaGsrkNEON(97, w3, w0, ByteBuffer.wrap(rk, 240, 16).order(ByteOrder.LITTLE_ENDIAN));
                ariaGsrkNEON(109, w0, w1, ByteBuffer.wrap(rk, 256, 16).order(ByteOrder.LITTLE_ENDIAN));
            }
        }
    }
    
    private static void processAndXorBlockNEON(byte[] xorBlock, byte[] outBlock, byte[] rk, int[] t) {
        outBlock[0] = (byte) (X1[ariaBrf(t[0], 3)] & 0xFF);
        outBlock[1] = (byte) ((X2[ariaBrf(t[0], 2)] >> 8) & 0xFF);
        outBlock[2] = (byte) (S1[ariaBrf(t[0], 1)] & 0xFF);
        outBlock[3] = (byte) (S2[ariaBrf(t[0], 0)] & 0xFF);
        outBlock[4] = (byte) (X1[ariaBrf(t[1],3)] & 0xFF);
        outBlock[5] = (byte) ((X2[ariaBrf(t[1], 2)] >> 8) & 0xFF);
        outBlock[6] = (byte) (S1[ariaBrf(t[1], 1)] & 0xFF);
        outBlock[7] = (byte) (S2[ariaBrf(t[1], 0)] & 0xFF);
        outBlock[8] = (byte) (X1[ariaBrf(t[2], 3)] & 0xFF);
        outBlock[9] = (byte) ((X2[ariaBrf(t[2], 2)] >> 8) & 0xFF);
        outBlock[10] = (byte) (S1[ariaBrf(t[2], 1)] & 0xFF);
        outBlock[11] = (byte) (S2[ariaBrf(t[2], 0)] & 0xFF);
        outBlock[12] = (byte) (X1[ariaBrf(t[3], 3)] & 0xFF);
        outBlock[13] = (byte) ((X2[ariaBrf(t[3], 2)] >> 8) & 0xFF);
        outBlock[14] = (byte) (S1[ariaBrf(t[3], 1)] & 0xFF);
        outBlock[15] = (byte) (S2[ariaBrf(t[3], 0)] & 0xFF);
        if (xorBlock != null) {
            ByteBuffer xorByteBuffer = ByteBuffer.wrap(xorBlock).order(ByteOrder.LITTLE_ENDIAN);
            ByteBuffer outByteBuffer = ByteBuffer.wrap(outBlock).order(ByteOrder.LITTLE_ENDIAN);
            ByteBuffer rkByteBuffer = ByteBuffer.wrap(rk).order(ByteOrder.LITTLE_ENDIAN);
            outByteBuffer.putInt(0, outByteBuffer.getInt(0) ^ xorByteBuffer.getInt(0) ^ rkByteBuffer.getInt(0));
            outByteBuffer.putInt(4, outByteBuffer.getInt(4) ^ xorByteBuffer.getInt(4) ^ rkByteBuffer.getInt(4));
            outByteBuffer.putInt(8, outByteBuffer.getInt(8) ^ xorByteBuffer.getInt(8) ^ rkByteBuffer.getInt(8));
            outByteBuffer.putInt(12, outByteBuffer.getInt(12) ^ xorByteBuffer.getInt(12) ^ rkByteBuffer.getInt(12));
        } else {
            ByteBuffer outByteBuffer = ByteBuffer.wrap(outBlock).order(ByteOrder.LITTLE_ENDIAN);
            ByteBuffer rkByteBuffer = ByteBuffer.wrap(rk).order(ByteOrder.LITTLE_ENDIAN);
            outByteBuffer.putInt(0, outByteBuffer.getInt(0) ^ rkByteBuffer.getInt(0));
            outByteBuffer.putInt(4, outByteBuffer.getInt(4) ^ rkByteBuffer.getInt(4));
            outByteBuffer.putInt(8, outByteBuffer.getInt(8) ^ rkByteBuffer.getInt(8));
            outByteBuffer.putInt(12, outByteBuffer.getInt(12) ^ rkByteBuffer.getInt(12));
        }
    }
}        