import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class PacketSniffer {
    private static final String PACKET_DUMP_FILE_PREFIX = "wowsniff";
    private static final String PACKET_DUMP_FILE_EXTENSION = ".pkt";

    private ReentrantLock lock = new ReentrantLock();
    private AtomicInteger cmsgCount = new AtomicInteger(0);
    private AtomicInteger smsgCount = new AtomicInteger(0);

    private File packetDumpFile;
    private FileOutputStream packetDumpFileStream;

    public void init() {
        try {
            packetDumpFile = createPacketDumpFile();
            packetDumpFileStream = new FileOutputStream(packetDumpFile);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private File createPacketDumpFile() throws IOException {
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss");
        String fileName = PACKET_DUMP_FILE_PREFIX + "_" + now.format(formatter) + PACKET_DUMP_FILE_EXTENSION;
        return new File(fileName);
    }

    public void dumpPacket(int packetType, int connectionId, int opcode, int size, byte[] buffer) {
        lock.lock();
        try {
            ByteBuffer byteBuffer = ByteBuffer.allocate(24 + size);
            byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
            byteBuffer.putInt(packetType);
            byteBuffer.putInt(connectionId);
            byteBuffer.putInt((int) System.currentTimeMillis());
            byteBuffer.putInt(0); // optional data size
            byteBuffer.putInt(size + 4);
            byteBuffer.putInt(opcode);
            byteBuffer.put(buffer, 0, size);

            byte[] data = byteBuffer.array();
            packetDumpFileStream.write(data);
            packetDumpFileStream.flush();

            if (packetType == 1) {
                cmsgCount.incrementAndGet();
            } else if (packetType == 2) {
                smsgCount.incrementAndGet();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    public void close() {
        try {
            packetDumpFileStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PacketSniffer packetSniffer = new PacketSniffer();
        packetSniffer.init();

        // Add your packet handling logic here.

        packetSniffer.close();
    }
}
