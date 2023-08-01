import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class QDataStream {
    private InputStream inputStream;
    private OutputStream outputStream;
    private ByteOrder byteOrder;
    private Status status;

    public enum Status {
        Ok, ReadPastEnd, ReadCorruptData, WriteFailed
    }

    public QDataStream() {
        this.byteOrder = ByteOrder.BIG_ENDIAN;
        this.status = Status.Ok;
    }

    public QDataStream(InputStream inputStream) {
        this();
        this.inputStream = inputStream;
    }

    public QDataStream(OutputStream outputStream) {
        this();
        this.outputStream = outputStream;
    }

    public boolean atEnd() {
        try {
            return inputStream.available() == 0;
        } catch (IOException e) {
            throw new RuntimeException("Error checking if InputStream is at the end", e);
        }
    }

    public ByteOrder getByteOrder() {
        return byteOrder;
    }

    public void setByteOrder(ByteOrder byteOrder) {
        this.byteOrder = byteOrder;
    }

    public InputStream getInputStream() {
        return inputStream;
    }

    public void setInputStream(InputStream inputStream) {
        this.inputStream = inputStream;
    }

    public OutputStream getOutputStream() {
        return outputStream;
    }

    public void setOutputStream(OutputStream outputStream) {
        this.outputStream = outputStream;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public void writeBytes(byte[] data) {
        try {
            ByteBuffer buffer = ByteBuffer.allocate(4 + data.length);
            buffer.order(byteOrder);
            buffer.putInt(data.length);
            buffer.put(data);
            outputStream.write(buffer.array());
        } catch (IOException e) {
            setStatus(Status.WriteFailed);
            throw new RuntimeException("Error writing bytes", e);
        }
    }

    public byte[] readBytes() {
        try {
            byte[] lengthBytes = new byte[4];
            int bytesRead = inputStream.read(lengthBytes);
            if (bytesRead != 4) {
                setStatus(Status.ReadCorruptData);
                return null;
            }

            ByteBuffer buffer = ByteBuffer.wrap(lengthBytes);
            buffer.order(byteOrder);
            int length = buffer.getInt();

            byte[] data = new byte[length];
            bytesRead = inputStream.read(data);
            if (bytesRead != length) {
                setStatus(Status.ReadPastEnd);
                return null;
            }

            return data;
        } catch (IOException e) {
            setStatus(Status.ReadCorruptData);
            throw new RuntimeException("Error reading bytes", e);
        }
    }

    public void resetStatus() {
        setStatus(Status.Ok);
    }
}
