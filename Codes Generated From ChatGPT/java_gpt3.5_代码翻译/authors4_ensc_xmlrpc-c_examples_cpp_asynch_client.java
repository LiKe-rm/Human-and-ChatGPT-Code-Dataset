import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import org.apache.xmlrpc.client.XmlRpcHttpClientConfig;

import java.net.URL;
import java.util.Arrays;
import java.util.concurrent.*;

public class AsynchClient {
    public static void main(String[] args) {
        if (args.length > 0) {
            System.err.println("This program has no arguments");
            System.exit(1);
        }

        try {
            XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
            config.setServerURL(new URL("http://localhost:8080/RPC2"));
            XmlRpcClient client = new XmlRpcClient();
            client.setConfig(config);

            ExecutorService executor = Executors.newFixedThreadPool(2);

            Future<Integer> sum1Future = executor.submit(() -> {
                Object[] params1 = new Object[]{3, 1};
                Integer sum1 = (Integer) client.execute("sample.add", Arrays.asList(params1));
                return sum1;
            });

            Future<Integer> sum2Future = executor.submit(() -> {
                Object[] params2 = new Object[]{5, 7};
                Integer sum2 = (Integer) client.execute("sample.add", Arrays.asList(params2));
                return sum2;
            });

            System.out.println("Two RPCs started. Waiting for them to finish.");

            int sum1 = sum1Future.get();
            int sum2 = sum2Future.get();

            System.out.println("Result of RPC 1 (sum of 3 and 1): " + sum1);
            System.out.println("Result of RPC 2 (sum of 5 and 7): " + sum2);

            executor.shutdown();

        } catch (Exception e) {
            System.err.println("Client threw error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
