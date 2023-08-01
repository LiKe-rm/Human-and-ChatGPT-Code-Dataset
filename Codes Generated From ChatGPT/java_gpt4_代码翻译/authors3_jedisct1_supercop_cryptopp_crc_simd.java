import java.nio.ByteBuffer;
import java.util.zip.CRC32;
import java.util.zip.Checksum;

public class CRC32Simd {

    public static void main(String[] args) {
        byte[] data = new byte[100];
        int crc32 = updateCRC32(data);
        int crc32c = updateCRC32C(data);

        System.out.println("CRC32: " + Integer.toHexString(crc32));
        System.out.println("CRC32C: " + Integer.toHexString(crc32c));
    }

    public static int updateCRC32(byte[] data) {
        CRC32 crc32 = new CRC32();
        crc32.update(data);
        return (int) crc32.getValue();
    }

    public static int updateCRC32C(byte[] data) {
        CRC32C crc32c = new CRC32C();
        crc32c.update(data, 0, data.length);
        return (int) crc32c.getValue();
    }
}

class CRC32C implements Checksum {

    private static final int[] CRC_TABLE = new int[256];
    private int crc = 0xFFFFFFFF;

    static {
        for (int n = 0; n < 256; n++) {
            int c = n;
            for (int k = 8; --k >= 0;) {
                if ((c & 1) != 0) {
                    c = 0x82F63B78 ^ (c >>> 1);
                } else {
                    c = c >>> 1;
                }
            }
            CRC_TABLE[n] = c;
        }
    }

    @Override
    public void update(int b) {
        crc = CRC_TABLE[(crc ^ b) & 0xFF] ^ (crc >>> 8);
    }

    @Override
    public void update(byte[] b, int off, int len) {
        for (int i = 0; i < len; i++) {
            update(b[off + i]);
        }
    }

    @Override
    public long getValue() {
        return (~crc) & 0xFFFFFFFFL;
    }

    @Override
    public void reset() {
        crc = 0xFFFFFFFF;
    }
}
