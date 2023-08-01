import java.io.*;
import java.net.*;
import java.util.regex.Pattern;

public class SocketWrapper {

    private Socket socket;
    private ServerSocket serverSocket;

    public SocketWrapper(String address, int port, int maxConnections) throws IOException {
        serverSocket = new ServerSocket();
        serverSocket.setReuseAddress(true);
        serverSocket.bind(new InetSocketAddress(address, port), maxConnections);
    }

    private SocketWrapper(Socket socket) {
        this.socket = socket;
    }

    public SocketWrapper accept() throws IOException {
        return new SocketWrapper(serverSocket.accept());
    }

    public String recv(int length) throws IOException {
        byte[] buffer = new byte[length];
        int bytesRead = socket.getInputStream().read(buffer);
        if (bytesRead < 0) {
            throw new IOException("Failed to read from socket");
        }
        return new String(buffer, 0, bytesRead);
    }

    public String readLine() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        return reader.readLine();
    }

    public int send(String string) throws IOException {
        byte[] bytes = string.getBytes();
        socket.getOutputStream().write(bytes);
        return bytes.length;
    }

    public void close() throws IOException {
        if (socket != null) {
            socket.close();
        }
        if (serverSocket != null) {
            serverSocket.close();
        }
    }

    public void setBlocking(boolean blocking) throws IOException {
        socket.setSoTimeout(blocking ? 0 : Integer.MAX_VALUE);
    }

    private boolean isValidIPv4(String addr) {
        String regex = "^(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)$";
        Pattern pattern = Pattern.compile(regex);
        if (pattern.matcher(addr).matches()) {
            String[] parts = addr.split("\\.");
            for (String part : parts) {
                if (Integer.parseInt(part) > 255) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
}
