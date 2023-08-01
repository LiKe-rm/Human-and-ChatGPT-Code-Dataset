import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import java.net.URL;
import java.net.MalformedURLException;

public class ClientSimple {

    private XmlRpcClient client;

    public ClientSimple() {
        client = new XmlRpcClient();
    }

    public Object call(String serverUrl, String methodName) throws MalformedURLException, XmlRpcException {
        XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
        config.setServerURL(new URL(serverUrl));
        client.setConfig(config);
        return client.execute(methodName, new ArrayList<>());
    }

    public Object call(String serverUrl, String methodName, List<Object> parameters) throws MalformedURLException, XmlRpcException {
        XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
        config.setServerURL(new URL(serverUrl));
        client.setConfig(config);
        return client.execute(methodName, parameters);
    }

    public static void main(String[] args) {
        ClientSimple clientSimple = new ClientSimple();
        try {
            Object result = clientSimple.call("http://localhost:8080/xmlrpc", "sample.add", Arrays.asList(1, 2));
            System.out.println("Result: " + result);
        } catch (MalformedURLException | XmlRpcException e) {
            e.printStackTrace();
        }
    }
}
