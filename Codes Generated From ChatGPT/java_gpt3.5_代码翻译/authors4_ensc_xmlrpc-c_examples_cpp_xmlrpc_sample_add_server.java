import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.server.PropertyHandlerMapping;
import org.apache.xmlrpc.server.XmlRpcServer;
import org.apache.xmlrpc.server.XmlRpcServerConfigImpl;
import org.apache.xmlrpc.webserver.WebServer;

public class SampleAddXmlRpcServer {

    public static class SampleAddHandler {

        public int add(int x, int y) throws InterruptedException {
            // Sometimes, make it look hard (so client can see what it's like
            // to do an RPC that takes a while).
            if (y == 1) {
                Thread.sleep(2000);
            }
            return x + y;
        }
    }

    public static void main(String[] args) {
        try {
            WebServer webServer = new WebServer(8080);
            XmlRpcServer xmlRpcServer = webServer.getXmlRpcServer();

            PropertyHandlerMapping phm = new PropertyHandlerMapping();
            phm.addHandler("SampleAddHandler", SampleAddXmlRpcServer.SampleAddHandler.class);
            xmlRpcServer.setHandlerMapping(phm);

		        XmlRpcServerConfigImpl serverConfig = (XmlRpcServerConfigImpl) xmlRpcServer.getConfig();
        serverConfig.setEnabledForExtensions(true);
        serverConfig.setContentLengthOptional(false);

        webServer.start();

        System.out.println("Started XML-RPC server on port 8080...");

    } catch (XmlRpcException e) {
        System.err.println("Error in XML-RPC server configuration: " + e.getMessage());
    } catch (Exception e) {
        System.err.println("Error starting XML-RPC server: " + e.getMessage());
    }
}
}