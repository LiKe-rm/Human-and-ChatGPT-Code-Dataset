import java.io.IOException;
import java.net.InetSocketAddress;

import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.server.PropertyHandlerMapping;
import org.apache.xmlrpc.server.XmlRpcServer;
import org.apache.xmlrpc.server.XmlRpcServerConfigImpl;
import org.apache.xmlrpc.webserver.WebServer;

public class CallInfoXmlRpcServer {
    public static class CallInfoHandler {
        public String getCallInfo(String remoteAddress, int remotePort) {
            return "RPC is from IP address " + remoteAddress + ", Port " + remotePort;
        }
    }

    public static void main(String[] args) {
        try {
            WebServer webServer = new WebServer(8080) {
                @Override
                protected XmlRpcServer newXmlRpcServer() {
                    XmlRpcServer server = super.newXmlRpcServer();
                    server.setConfig(new XmlRpcServerConfigImpl() {
                        @Override
                        public boolean isEnabledForExtensions() {
                            return true;
                        }
                    });
                    return server;
                }
            };

            XmlRpcServer xmlRpcServer = webServer.getXmlRpcServer();
            PropertyHandlerMapping phm = new PropertyHandlerMapping() {
                @Override
                public Object getHandler(String pHandlerName) throws XmlRpcException {
                    InetSocketAddress remoteSocketAddress = webServer.getXmlRpcServer().getWorkerFactory().getRemoteSocketAddress();
                    CallInfoHandler handler = new CallInfoHandler();
                    handler.getCallInfo(remoteSocketAddress.getAddress().getHostAddress(), remoteSocketAddress.getPort());
                    return handler;
                }
            };

            phm.addHandler("CallInfo", CallInfoHandler.class);
            xmlRpcServer.setHandlerMapping(phm);
        System.out.println("Starting the CallInfo XML-RPC server on port 8080...");
        webServer.start();

    } catch (IOException e) {
        System.err.println("Error starting the CallInfo XML-RPC server: " + e.getMessage());
        e.printStackTrace();
    } catch (XmlRpcException e) {
        System.err.println("Error configuring the CallInfo XML-RPC server: " + e.getMessage());
        e.printStackTrace();
    }
}
}