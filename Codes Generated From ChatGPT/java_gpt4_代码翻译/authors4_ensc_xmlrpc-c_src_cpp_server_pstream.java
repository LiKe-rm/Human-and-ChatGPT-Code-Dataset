import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketAddress;

public class ServerPStream {
    private final Registry registry;
    private final ServerSocket serverSocket;
    private volatile boolean terminateRequested;

    public ServerPStream(Registry registry, ServerSocket serverSocket) {
        this.registry = registry;
        this.serverSocket = serverSocket;
        this.terminateRequested = false;
    }

    public void runSerial() {
        while (!terminateRequested) {
            try {
                Socket clientSocket = serverSocket.accept();
                SocketAddress clientAddress = clientSocket.getRemoteSocketAddress();

                ServerPStreamConnection connectionServer = new ServerPStreamConnection(registry, clientSocket);
                CallInfoServerPStream callInfo = new CallInfoServerPStream(this, clientAddress);
                connectionServer.run(callInfo);

            } catch (IOException e) {
                if (!terminateRequested) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void terminate() {
        this.terminateRequested = true;
        try {
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static class CallInfoServerPStream {
        private final ServerPStream serverPStream;
        private final SocketAddress clientAddress;

        public CallInfoServerPStream(ServerPStream serverPStream, SocketAddress clientAddress) {
            this.serverPStream = serverPStream;
            this.clientAddress = clientAddress;
            }
            public ServerPStream getServerPStream() {
                return serverPStream;
            }
        
            public SocketAddress getClientAddress() {
                return clientAddress;
            }
        }
        
        public static class Registry {
            // Implement your registry here, including any methods for handling
            // requests and managing the registered functions.
            private final Map<String, SumHandler> handlers;
    
            public Registry() {
                handlers = new HashMap<>();
                handlers.put("sum", new SumHandler());
            }
    
            public String executeRequest(String methodName, String params) {
                SumHandler handler = handlers.get(methodName);
                if (handler != null) {
                    return handler.handle(params);
                } else {
                    return "Method not found";
                }
            }
        }
        
        public static class SumHandler {
            public String handle(String params) {
                String[] operands = params.split(",");
                int sum = 0;
                for (String operand : operands) {
                    sum += Integer.parseInt(operand.trim());
                }
                return "Sum: " + sum;
            }
        }

        public static class ServerPStreamConnection {
            private final Registry registry;
            private final Socket clientSocket;
        
            public ServerPStreamConnection(Registry registry, Socket clientSocket) {
                this.registry = registry;
                this.clientSocket = clientSocket;
            }
        
            public void run(CallInfoServerPStream callInfo) {
                // Implement your connection handling here, including reading
                // requests from the client, processing them using the registry,
                // and sending responses back to the client.
                Registry registry = new Registry();
                try (ServerSocket serverSocket = new ServerSocket(this.socketFd)) {
                    while (!this.terminateRequested) {
                        try (Socket clientSocket = serverSocket.accept()) {
                            SocketAddress clientAddress = clientSocket.getRemoteSocketAddress();
            
                            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            
                            String methodName = in.readLine();
                            String params = in.readLine();
                            if (methodName != null && params != null) {
                                String result = registry.executeRequest(methodName, params);
                                out.println(result);
                            }
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        
        public static void main(String[] args) {
            // Example usage:
            try {
                Registry registry = new Registry();
                ServerSocket serverSocket = new ServerSocket(8080);
                ServerPStream serverPStream = new ServerPStream(registry, serverSocket);
                serverPStream.runSerial();
                ServerPStream server = new ServerPStream(8080);
                server.run();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
}        