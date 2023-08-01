import java.io.*;
import java.net.*;
import java.nio.channels.*;
import java.util.*;
import java.util.concurrent.*;

public class Streamer {
    private static final int BUFSIZE = 65536;

    private static class Config {
        String configFileName = "";
        String server = "localhost";
        int port = 8001;
        String log = "streamer.log";
        String encoder = "lame -r -m m -s 11.025 -x -b 16 -q 9 - -";
        String contentType = "audio/mpeg";
        int maxClients = 10;
        String name = "";
        String genre = "";
        String url = "";
        String irc = "";
        String aim = "";
        String icq = "";
    }

    private static Config config = new Config();

    public static void main(String[] args) {
        // Load configurations from file
        loadConfig("streamer.conf");

        // Set up the server
        try (ServerSocketChannel serverSocketChannel = ServerSocketChannel.open()) {
            serverSocketChannel.socket().bind(new InetSocketAddress(config.port));
            serverSocketChannel.configureBlocking(false);

            Selector selector = Selector.open();
            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

            ByteBuffer buffer = ByteBuffer.allocateDirect(BUFSIZE);

            while (true) {
                selector.select();

                Iterator<SelectionKey> keys = selector.selectedKeys().iterator();
                while (keys.hasNext()) {
                    SelectionKey key = keys.next();
                    keys.remove();

                    if (!key.isValid()) {
                        continue;
                    }

                    if (key.isAcceptable()) {
                        handleAccept(serverSocketChannel, selector);
                    } else if (key.isReadable()) {
                        handleRead(key, buffer);
                    } else if (key.isWritable()) {
                        handleWrite(key, buffer);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadConfig(String fileName) {
        // Load configurations from file
        // This is just a placeholder
    }

    private static void handleAccept(ServerSocketChannel serverSocketChannel, Selector selector) throws IOException {
        SocketChannel clientChannel = serverSocketChannel.accept();
        clientChannel.configureBlocking(false);
        clientChannel.register(selector, SelectionKey.OP_READ);
    }

    private static void handleRead(SelectionKey key, ByteBuffer buffer) throws IOException {
        SocketChannel clientChannel = (SocketChannel) key.channel();
        buffer.clear();
        int bytesRead = clientChannel.read(buffer);

        if (bytesRead == -1) {
            key.cancel();
            clientChannel.close();
        } else {
            buffer.flip();
            key.interestOps(SelectionKey.OP_WRITE);
        }
    }

    private static void handleWrite(SelectionKey key, ByteBuffer buffer) throws IOException {
        SocketChannel clientChannel = (SocketChannel) key.channel();
        buffer.rewind();
        clientChannel.write(buffer);
        key.interestOps(SelectionKey.OP_READ);
    }
}
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class Streamer {

    private static final int PORT = 8001;
    private static final String CONTENT_TYPE = "audio/mpeg";
    private static final String STREAM_NAME = "My Stream";
    private static final String STREAM_GENRE = "Music";
    private static final String STREAM_URL = "http://example.com";

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(PORT);
        System.out.println("Server started on port " + PORT);

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(new ClientHandler(clientSocket)).start();
        }
    }

    private static class ClientHandler implements Runnable {

        private final Socket clientSocket;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try {
                BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                OutputStream writer = clientSocket.getOutputStream();

                String request = reader.readLine();
                if (request != null) {
                    System.out.println("Request: " + request);

                    String response = "ICY 200 OK\r\n" +
                            "Content-Type: " + CONTENT_TYPE + "\r\n" +
                            "icy-name: " + STREAM_NAME + "\r\n" +
                            "icy-genre: " + STREAM_GENRE + "\r\n" +
                            "icy-url: " + STREAM_URL + "\r\n" +
                            "icy-pub: 1\r\n" +
                            "icy-br: 16\r\n" +
                            "\r\n";

                    writer.write(response.getBytes(StandardCharsets.UTF_8));
                    writer.flush();
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
