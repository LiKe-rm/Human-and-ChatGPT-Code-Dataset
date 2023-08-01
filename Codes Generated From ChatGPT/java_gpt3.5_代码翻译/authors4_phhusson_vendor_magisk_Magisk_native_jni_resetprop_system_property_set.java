import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PropertyService {
    private static final String PROPERTY_SERVICE_SOCKET = "/dev/socket/property_service";
    private static final String SERVICE_VERSION_PROPERTY_NAME = "ro.property_service.version";
    private static final int PROP_MSG_SETPROP = 1;
    private static final int PROP_MSG_SETPROP2 = 2;
    private static final int PROP_NAME_MAX = 32;
    private static final int PROP_VALUE_MAX = 92;
    private static final int PROP_SUCCESS = 0;
    private static final int PROTOCOL_VERSION_1 = 1;
    private static final int PROTOCOL_VERSION_2 = 2;

    private static int propertyServiceProtocolVersion = 0;

    public static void main(String[] args) {
        setSystemProperty("test.property", "test value");
    }

    public static int setSystemProperty(String key, String value) {
        if (key == null) return -1;
        if (value == null) value = "";

        if (propertyServiceProtocolVersion == 0) {
            detectProtocolVersion();
        }

        try (Socket socket = new Socket(PROPERTY_SERVICE_SOCKET, 0)) {
            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            if (propertyServiceProtocolVersion == PROTOCOL_VERSION_1) {
                if (key.length() >= PROP_NAME_MAX || value.length() >= PROP_VALUE_MAX) {
                    return -1;
                }

                ByteBuffer buffer = ByteBuffer.allocate(4 + PROP_NAME_MAX + PROP_VALUE_MAX);
                buffer.putInt(PROP_MSG_SETPROP);
                byte[] keyBytes = key.getBytes(StandardCharsets.UTF_8);
                byte[] valueBytes = value.getBytes(StandardCharsets.UTF_8);
                buffer.put(keyBytes);
                buffer.position(4 + PROP_NAME_MAX);
                buffer.put(valueBytes);

                outputStream.write(buffer.array());
                outputStream.flush();
                socket.shutdownOutput();

                // Wait for the socket to close on the property service side
                int readResult = inputStream.read();
                if (readResult == -1) {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                if (value.length() >= PROP_VALUE_MAX && !key.startsWith("ro.")) {
                    return -1;
                }

                ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                DataOutputStream dataOutputStream = new DataOutputStream(byteArrayOutputStream);
                dataOutputStream.writeInt(PROP_MSG_SETPROP2);
                writeString(dataOutputStream, key);
                writeString(dataOutputStream, value);

                outputStream.write(byteArrayOutputStream.toByteArray());
                outputStream.flush();
                socket.shutdownOutput();

                int resultCode = inputStream.readInt();
                if (resultCode == PROP_SUCCESS) {
                    return 0;
                } else {
                    return -1;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }

    private static void detectProtocolVersion() {
        String value = System.getProperty(SERVICE_VERSION_PROPERTY_NAME);
        if (value == null) {
            propertyServiceProtocolVersion = PROTOCOL_VERSION_1;
        } else {
            int version = Integer.parseInt(value);
            if (version >= PROTOCOL_VERSION_2) {
                propertyServiceProtocolVersion = PROTOCOL_VERSION_2;
            } else {
                propertyServiceProtocolVersion = PROTOCOL_VERSION_1;
            }
        }
    }
}
import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PropertyService {
    private static final String PROPERTY_SERVICE_SOCKET = "/dev/socket/" + System.getProperty("PROP_SERVICE_NAME");
    private static final String SERVICE_VERSION_PROPERTY_NAME = "ro.property_service.version";

    private final Socket socket;
    private int lastError;

    public PropertyService() throws IOException {
        socket = new Socket(PROPERTY_SERVICE_SOCKET, 0);
    }

    public boolean isValid() {
        return socket != null && socket.isConnected();
    }

    public int getLastError() {
        return lastError;
    }

    public boolean recvInt32() {
        ByteBuffer buffer = ByteBuffer.allocate(Integer.BYTES);
        try {
            int bytesRead = socket.getInputStream().read(buffer.array());
            if (bytesRead == Integer.BYTES) {
                lastError = 0;
                return true;
            } else {
                lastError = -1;
                return false;
            }
        } catch (IOException e) {
            lastError = -1;
            return false;
        }
    }

    public void close() {
        if (socket != null) {
            try {
                socket.close();
            } catch (IOException e) {
                // Ignore exception during close
            }
        }
    }

    public static int sendPropertyMessage(String key, String value) {
        try (PropertyService connection = new PropertyService()) {
            if (!connection.isValid()) {
                return connection.getLastError();
            }

            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            DataOutputStream dataOutputStream = new DataOutputStream(byteArrayOutputStream);

            dataOutputStream.writeInt(PROP_MSG_SETPROP2);
            dataOutputStream.writeInt(key.length());
            dataOutputStream.write(key.getBytes(StandardCharsets.UTF_8));
            dataOutputStream.writeInt(value.length());
            dataOutputStream.write(value.getBytes(StandardCharsets.UTF_8));

            byte[] messageBytes = byteArrayOutputStream.toByteArray();
            connection.socket.getOutputStream().write(messageBytes);

            return connection.recvInt32() ? 0 : -1;
        } catch (IOException e) {
            return -1;
        }
    }
}
