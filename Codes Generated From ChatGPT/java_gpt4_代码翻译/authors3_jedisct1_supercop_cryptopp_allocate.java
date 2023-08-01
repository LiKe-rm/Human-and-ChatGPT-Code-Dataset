import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Allocator {

    public static void callNewHandler() {
        try {
            throw new OutOfMemoryError();
        } catch (OutOfMemoryError e) {
            System.gc();
        }
    }

    public static ByteBuffer alignedAllocate(int size) {
        ByteBuffer buffer;

        try {
            buffer = ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
        } catch (OutOfMemoryError e) {
            callNewHandler();
            buffer = ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
        }

        if (buffer.isDirect()) {
            return buffer;
        } else {
            throw new IllegalStateException("Unable to allocate aligned memory");
        }
    }

    public static void alignedDeallocate(ByteBuffer buffer) {
        if (buffer != null && buffer.isDirect()) {
            sun.misc.Cleaner cleaner = ((sun.nio.ch.DirectBuffer) buffer).cleaner();
            if (cleaner != null) {
                cleaner.clean();
            }
        }
    }

    public static byte[] unalignedAllocate(int size) {
        byte[] buffer;
        try {
            buffer = new byte[size];
        } catch (OutOfMemoryError e) {
            callNewHandler();
            buffer = new byte[size];
        }
        return buffer;
    }

    public static void unalignedDeallocate(byte[] buffer) {
        if (buffer != null) {
            buffer = null;
            System.gc();
        }
    }

    public static void main(String[] args) {
        ByteBuffer alignedBuffer = alignedAllocate(128);
        byte[] unalignedBuffer = unalignedAllocate(128);

        System.out.println("Aligned buffer: " + alignedBuffer);
        System.out.println("Unaligned buffer: " + unalignedBuffer);

        alignedDeallocate(alignedBuffer);
        unalignedDeallocate(unalignedBuffer);

        System.out.println("Deallocated buffers");
    }
}
