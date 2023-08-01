import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class ClientXmlTransportPStream {

    private final Socket socket;
    private final InputStream inputStream;
    private final OutputStream outputStream;

    public ClientXmlTransportPStream(Socket socket) throws IOException {
        this.socket = socket;
        this.inputStream = socket.getInputStream();
        this.outputStream = socket.getOutputStream();
    }

    public void call(String callXml, StringBuilder responseXml) throws IOException {
        byte[] callBytes = callXml.getBytes();
        int callLength = callBytes.length;

        outputStream.write(intToByteArray(callLength));
        outputStream.write(callBytes);
        outputStream.flush();

        byte[] responseLengthBytes = new byte[4];
        int bytesRead = inputStream.read(responseLengthBytes);
        if (bytesRead != 4) {
            throw new IOException("Error reading response length");
        }

        int responseLength = byteArrayToInt(responseLengthBytes);
        byte[] responseBytes = new byte[responseLength];
        bytesRead = inputStream.read(responseBytes);
        if (bytesRead != responseLength) {
            throw new IOException("Error reading response");
        }

        responseXml.append(new String(responseBytes));
    }

    private static int byteArrayToInt(byte[] bytes) {
        return ((bytes[0] & 0xFF) << 24) | ((bytes[1] & 0xFF) << 16) | ((bytes[2] & 0xFF) << 8) | (bytes[3] & 0xFF);
    }
    private static byte[] intToByteArray(int value) {
        return new byte[]{
                (byte) (value >>> 24),
                (byte) (value >>> 16),
                (byte) (value >>> 8),
                (byte) value
        };
    }
    
    public void close() throws IOException {
        socket.close();
    }
}    
