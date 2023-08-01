import org.apache.xmlrpc.XmlRpcClient;
import org.apache.xmlrpc.XmlRpcClientConfigImpl;
import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.XmlRpcRequest;
import org.apache.xmlrpc.XmlRpcRequestConfig;
import org.apache.xmlrpc.common.XmlRpcStreamRequestConfig;
import org.apache.xmlrpc.serializer.XmlRpcWriter;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.URL;
import java.util.List;
import java.util.Vector;

public class XmlRpcUtil {

    public static String generateCall(String methodName, List<Object> paramList) throws IOException {
        XmlRpcRequest request = new XmlRpcRequest() {
            @Override
            public XmlRpcRequestConfig getConfig() {
                XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
                config.setEnabledForExtensions(true);
                return config;
            }

            @Override
            public String getMethodName() {
                return methodName;
            }

            @Override
            public int getParameterCount() {
                return paramList.size();
            }

            @Override
            public Object getParameter(int index) {
                return paramList.get(index);
            }
        };

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        XmlRpcWriter writer = new XmlRpcWriter();
        writer.write(baos, request);

        return baos.toString("UTF-8");
    }

    public static Object parseCall(String callXml) throws XmlRpcException {
        XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
        XmlRpcClient client = new XmlRpcClient() {
            @Override
            protected XmlRpcStreamRequestConfig getRequestConfig(Object pRequest) {
                return config;
            }
        };

        return client.execute(new ByteArrayInputStream(callXml.getBytes(StandardCharsets.UTF_8)));
    }

    public static void main(String[] args) {
        try {
            // Generate an XML-RPC call
            List<Object> params = new Vector<>();
            params.add("Hello");
            params.add("World");
            String callXml = generateCall("testMethod", params);
            System.out.println("Generated call XML: " + callXml);
            // Parse an XML-RPC call
            Object result = parseCall(callXml);
            System.out.println("Parsed call result: " + result);
        } catch (IOException | XmlRpcException e) {
            e.printStackTrace();
        }
    }
}