import org.apache.xmlrpc.XmlRpcClient;
import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.XmlRpcRequest;
import org.apache.xmlrpc.XmlRpcResponse;
import org.apache.xmlrpc.serializer.XmlRpcWriter;

import java.io.StringReader;
import java.io.StringWriter;
import java.util.Arrays;
import java.util.List;
import java.util.Vector;

public class XmlTest {

    public abstract static class TestSuite {
        public abstract String suiteName();

        public abstract void runTests(int indentation);
    }

    public static class CallTestSuite extends TestSuite {
        @Override
        public String suiteName() {
            return "callTestSuite";
        }

        @Override
        public void runTests(int indentation) {
            String methodName0 = "myMethod";
            List<Object> paramList0 = new Vector<>();

            String callXml;
            try {
                callXml = generateCall(methodName0, paramList0);
            } catch (XmlRpcException e) {
                throw new RuntimeException(e);
            }

            XmlRpcRequest request;
            try {
                request = parseCall(callXml);
            } catch (XmlRpcException e) {
                throw new RuntimeException(e);
            }

            assert request.getMethodName().equals(methodName0);
            assert request.getParameters().size() == paramList0.size();
        }
    }

    public static class ResponseTestSuite extends TestSuite {
        @Override
        public String suiteName() {
            return "responseTest"
        }

        @Override
        public void runTests(int indentation) {
            XmlRpcResponse outcome0 = new XmlRpcResponse(new Integer(7));

            String respXml;
            try {
                respXml = generateResponse(outcome0);
            } catch (XmlRpcException e) {
                throw new RuntimeException(e);
            }

            XmlRpcResponse outcome;
            try {
                outcome = parseResponse(respXml);
            } catch (XmlRpcException e) {
                throw new RuntimeException(e);
            }

            assert outcome.getValue().equals(outcome0.getValue());

            Object result;
            try {
                result = parseSuccessfulResponse(respXml);
            } catch (XmlRpcException e) {
                throw new RuntimeException(e);
            }

            assert result.equals(outcome0.getValue());
        }
    }

    public static void main(String[] args) {
        new CallTestSuite().runTests(1);
        new ResponseTestSuite().runTests(1);
    }

    private static String generateCall(String methodName, List<Object> params) throws XmlRpcException {
        XmlRpcRequest request = new XmlRpcRequest(methodName, params);
        StringWriter writer = new StringWriter();
        XmlRpcWriter xmlWriter = new XmlRpcWriter();
        xmlWriter.write(writer, request);
        return writer.toString();
    }

    private static XmlRpcRequest parseCall(String callXml) throws XmlRpcException {
        XmlRpcClient client = new XmlRpcClient();
        StringReader reader = new StringReader(callXml);
        return client.parse(reader);
    }

    private static String generateResponse(XmlRpcResponse response) throws XmlRpcException {
        StringWriter writer = new StringWriter();
        XmlRpcWriter xmlWriter = new XmlRpcWriter();
        xmlWriter.write(writer, response);
        return writer.toString();
    }

    private static XmlRpcResponse parseResponse(String responseXml) throws XmlRpcException {
        XmlRpcClient client = new XmlRpcClient();
        StringReader reader = new StringReader(responseXml);
        return client.parseResponse(reader);
    }

    private static Object parseSuccessfulResponse(String responseXml) throws XmlRpcException {
        XmlRpcResponse response = parseResponse(responseXml);
        if (response.isFault()) {
            throw new XmlRpcException("Response is a fault");
        }
        return response.getValue();
    }
}
