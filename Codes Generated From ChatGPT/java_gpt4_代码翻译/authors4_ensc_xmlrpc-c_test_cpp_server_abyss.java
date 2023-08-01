import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class ServerAbyss {

    public static void main(String[] args) throws IOException {
        Registry registry = new Registry();
        registry.addMethod("sample.add", new SampleAddMethod());

        ServerAbyss server = new ServerAbyss(8080, registry);
        server.start();
    }

    private final int port;
    private final Registry registry;

    public ServerAbyss(int port, Registry registry) {
        this.port = port;
        this.registry = registry;
    }

    public void start() throws IOException {
        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Server started on port " + port);

        while (true) {
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected");

            // 这里我们仅模拟了一个简化的版本，实际上你需要处理来自客户端的请求并返回响应。
            // 在实际应用中，你可以使用Apache XML-RPC库来处理XML-RPC请求和响应。

            clientSocket.close();
            System.out.println("Client disconnected");
        }
    }
}

interface Method {
    Object execute(Object[] params);
}

class Registry {
    private final Map<String, Method> methods = new HashMap<>();

    public void addMethod(String methodName, Method method) {
        methods.put(methodName, method);
    }

    public Method getMethod(String methodName) {
        return methods.get(methodName);
    }
}

class SampleAddMethod implements Method {
    @Override
    public Object execute(Object[] params) {
        if (params.length != 2) {
            throw new IllegalArgumentException("Expected 2 parameters");
        }
        if (!(params[0] instanceof Integer) || !(params[1] instanceof Integer)) {
            throw new IllegalArgumentException("Both parameters must be integers");
        }
        return (Integer) params[0] + (Integer) params[1];
    }
}