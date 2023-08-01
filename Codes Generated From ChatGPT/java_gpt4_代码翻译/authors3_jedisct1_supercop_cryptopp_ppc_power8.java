import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PPCPower8 {

    static {
        System.loadLibrary("ppcpower8");
    }

    public static void main(String[] args) {
        boolean hasPower8 = CPU_ProbePower8();
        boolean hasAES = CPU_ProbeAES();
        boolean hasSHA256 = CPU_ProbeSHA256();
        boolean hasSHA512 = CPU_ProbeSHA512();

        System.out.println("Power8: " + hasPower8);
        System.out.println("AES: " + hasAES);
        System.out.println("SHA-256: " + hasSHA256);
        System.out.println("SHA-512: " + hasSHA512);
    }

    // Native methods
    public static native boolean CPU_ProbePower8();
    public static native boolean CPU_ProbeAES();
    public static native boolean CPU_ProbeSHA256();
    public static native boolean CPU_ProbeSHA512();

    // Helper methods for working with byte arrays
    public static byte[] longToBytes(long value) {
        ByteBuffer buffer = ByteBuffer.allocate(Long.BYTES);
        buffer.order(ByteOrder.nativeOrder());
        buffer.putLong(value);
        return buffer.array();
    }

    public static long bytesToLong(byte[] bytes) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(ByteOrder.nativeOrder());
        return buffer.getLong();
    }

    public static byte[] intToBytes(int value) {
        ByteBuffer buffer = ByteBuffer.allocate(Integer.BYTES);
        buffer.order(ByteOrder.nativeOrder());
        buffer.putInt(value);
        return buffer.array();
    }

    public static int bytesToInt(byte[] bytes) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(ByteOrder.nativeOrder());
        return buffer.getInt();
    }
}
