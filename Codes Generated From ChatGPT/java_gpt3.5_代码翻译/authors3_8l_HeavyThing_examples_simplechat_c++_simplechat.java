import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class SimpleChatServer {
    private static final int PORT = 8001;
    private static ConcurrentHashMap<Socket, ChatClient> clients = new ConcurrentHashMap<>();

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Simple chat server listening on port 8001.");
            while (true) {
                Socket clientSocket = serverSocket.accept();
                new ClientHandler(clientSocket).start();
            }
        } catch (IOException e) {
            System.err.println("Server socket error: " + e.getMessage());
        }
    }

    static class ChatClient {
        String handle;
        String remoteAddress;

        ChatClient(String handle, String remoteAddress) {
            this.handle = handle;
            this.remoteAddress = remoteAddress;
        }
    }

    static class ClientHandler extends Thread {
        private final Socket clientSocket;

        ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try (
                    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
            ) {
                // Send greeting and set client handle
                out.println("Greetings! Your desired handle?");
                String handle = in.readLine().trim();
                String remoteAddress = clientSocket.getRemoteSocketAddress().toString();
                ChatClient chatClient = new ChatClient(handle, remoteAddress);
                clients.put(clientSocket, chatClient);

                // Broadcast user join message
                broadcastMessage(handle + " has joined the circus.");

                // Process client messages
                String input;
                while ((input = in.readLine()) != null) {
                    if (input.equalsIgnoreCase("/who")) {
                        listClients(out);
                    } else if (input.equalsIgnoreCase("/exit")) {
                        break;
                    } else {
                        broadcastMessage(handle + ": " + input);
                    }
                }

            } catch (IOException e) {
                System.err.println("Client socket error: " + e.getMessage());
            } finally {
                clients.remove(clientSocket);
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    System.err.println("Failed to close client socket: " + e.getMessage());
                }
            }
        }

        private void listClients(PrintWriter out) {
            StringBuilder response = new StringBuilder("Smoke on the water: ");
            clients.values().forEach(client -> {
                response.append(client.handle);
                response.append(" (");
                response.append(client.remoteAddress);
                response.append("), ");
            });
            out.println(response.substring(0, response.length() - 2));
        }

        private void broadcastMessage(String message) {
            clients.values().forEach(client -> {
                try {
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                    out.println(message);
                } catch (IOException e) {
                    System.err.println("Failed to broadcast message: " + e.getMessage());
                }
            });
        }
    }
}
