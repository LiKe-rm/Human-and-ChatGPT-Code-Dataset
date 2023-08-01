import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;

public class Main {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java Main <host> <port>");
            return;
        }

        String host = args[0];
        int port = Integer.parseInt(args[1]);

        try {
            Socket socket = new Socket();
            InetSocketAddress address = new InetSocketAddress(InetAddress.getByName(host), port);
            socket.connect(address);

            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            char[] buffer = new char[10];
            int bytesRead = reader.read(buffer, 0, 10);
            String receivedString = new String(buffer, 0, bytesRead);
            System.out.println(receivedString);

            socket.close();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
