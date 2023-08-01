import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class SocketPair {

    public static boolean createSocketPair(int[] sockets) {
        boolean error = false;
        ServerSocket serverSocket = null;
        Socket socket1 = null;
        Socket socket2 = null;

        try {
            serverSocket = new ServerSocket(0, 1, InetAddress.getByName("127.0.0.1"));
            socket1 = new Socket(serverSocket.getInetAddress(), serverSocket.getLocalPort());
            socket2 = serverSocket.accept();

            sockets[0] = socket1.getPort();
            sockets[1] = socket2.getPort();
        } catch (IOException e) {
            error = true;
        } finally {
            if (serverSocket != null) {
                try {
                    serverSocket.close();
                } catch (IOException ignored) {
                }
            }
            if (socket1 != null && error) {
                try {
                    socket1.close();
                } catch (IOException ignored) {
                }
            }
        }

        return !error;
    }

    public static void main(String[] args) {
        int[] sockets = new int[2];
        if (createSocketPair(sockets)) {
            System.out.println("Socket pair created:");
            System.out.println("Socket1: " + sockets[0]);
            System.out.println("Socket 2: " + sockets[1]);
        } else {
            System.out.println("Error creating socket pair.");
        }
    }
}
