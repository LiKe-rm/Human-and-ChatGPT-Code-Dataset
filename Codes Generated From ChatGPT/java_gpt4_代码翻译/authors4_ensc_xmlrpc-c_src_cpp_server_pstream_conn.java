import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class XMLRPCServer {

    private final int port;
    private final Map<String, Function<String, String>> registry;

    public XMLRPCServer(int port) {
        this.port = port;
        this.registry = new HashMap<>();
    }

    public void registerMethod(String methodName, Function<String, String> method) {
        registry.put(methodName, method);
    }

    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            while (true) {
                try {
                    Socket clientSocket = serverSocket.accept();
                    processClient(clientSocket);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void processClient(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()))) {

            String methodName = in.readLine();
            String params = in.readLine();

            String response;
            if (registry.containsKey(methodName)) {
                Function<String, String> method = registry.get(methodName);
                response = method.apply(params);
            } else {
                response = "Method not found: " + methodName;
            }
            out.write(response);
            out.newLine();
            out.flush();
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

    public static void main(String[] args) {
        XMLRPCServer server = new XMLRPCServer(8080);
        server.registerMethod("echo", input -> "You said: " + input);
        server.run();
    }
}