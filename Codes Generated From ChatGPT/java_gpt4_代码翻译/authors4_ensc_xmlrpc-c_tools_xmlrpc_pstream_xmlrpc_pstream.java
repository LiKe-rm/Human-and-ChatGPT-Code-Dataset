import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        try {
            XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
            config.setServerURL(new URL("http://localhost:8080/xmlrpc"));

            XmlRpcClient client = new XmlRpcClient();
            client.setConfig(config);

            boolean quitRequested = false;
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            while (!quitRequested) {
                System.out.print("> ");
                String input = reader.readLine();

                if (input == null || input.trim().equalsIgnoreCase("exit")) {
                    quitRequested = true;
                } else {
                    try {
                        String[] inputParts = input.trim().split(" ");
                        String methodName = inputParts[0];
                        List<String> paramArgs = new ArrayList<>();

                        for (int i = 1; i < inputParts.length; i++) {
                            paramArgs.add(input                            .add(inputParts[i]);
                        }

                        Object[] params = paramArgs.toArray();
                        Object result = client.execute(methodName, params);
                        System.out.println("Result:");
                        System.out.println(result);
                    } catch (XmlRpcException e) {
                        System.out.println("Command failed: " + e.getMessage());
                    } catch (Exception e) {
                        System.out.println("Error: " + e.getMessage());
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Failed: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Code threw unrecognized exception");
            e.printStackTrace();
        }
    }
}

