import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server {
    private ServerSocket serverSocket;
    private volatile boolean running = true;

    public static void main(String[] args) {
        Server server = new Server();
        server.startServer(8080);
    }

    public void startServer(int port) {
        try {
            serverSocket = new ServerSocket(port);
            System.out.println("Server started on port: " + port);

            while (running) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected: " + clientSocket.getInetAddress());
                new Thread(() -> handleClient(clientSocket)).start();
            }
        } catch (IOException e) {
            System.err.println("Error starting server: " + e.getMessage());
        } finally {
            if (serverSocket != null) {
                try {
                    serverSocket.close();
                } catch (IOException e) {
                    System.err.println("Error closing server socket: " + e.getMessage());
                }
            }
        }
    }

    private void handleClient(Socket clientSocket) {
        try {
            // Process the received data here

            // In this example, we'll just read the data as a string
            byte[] buffer = new byte[1024];
            int bytesRead = clientSocket.getInputStream().read(buffer);
            String receivedData = new String(buffer, 0, bytesRead);
            System.out.println("Received data from client: " + receivedData);

            // Send a response to the client
            clientSocket.getOutputStream().write("Data received".getBytes());

        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                System.err.println("Error closing client socket: " + e.getMessage());
            }
        }
    }

    public void stopServer() {
        running = false;
        if (serverSocket != null) {
            try {
                serverSocket.close();
            } catch (IOException e) {
                System.err.println("Error closing server socket: " + e.getMessage());
            }
        }
    }
}

class Data {
    private String ipAddress;
    private String computerName;
    private List<DataItem> dataItems = new ArrayList<>();

    public String getIpAddress() {
        return ipAddress;
    }

    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public String getComputerName() {
        return computerName;
    }

    public void setComputerName(String computerName) {
        this.computerName = computerName;
    }

    public List<DataItem> getDataItems() {
        return dataItems;
    }

    public void setDataItems(List<DataItem> dataItems) {
        this.dataItems = dataItems;
    }
}

class DataItem {
    private String description;
    private String content;

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
