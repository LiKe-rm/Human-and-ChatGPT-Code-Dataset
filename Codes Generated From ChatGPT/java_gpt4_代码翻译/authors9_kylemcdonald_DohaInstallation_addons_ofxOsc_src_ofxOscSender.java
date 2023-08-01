import com.illposed.osc.OSCSerializeException;
import com.illposed.osc.OSCMessage;
import com.illposed.osc.OSCBundle;
import com.illposed.osc.OSCPacket;
import com.illposed.osc.transport.udp.OSCPortOut;

import java.io.IOException;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Date;

public class OscSender {

    private OSCPortOut sender;

    public OscSender() {
    }

    public void setup(String hostname, int port) throws SocketException, UnknownHostException {
        if (sender != null) {
            shutdown();
        }

        sender = new OSCPortOut(InetAddress.getByName(hostname), port);
    }

    public void shutdown() {
        if (sender != null) {
            sender.close();
            sender = null;
        }
    }

    public void sendBundle(OscBundle bundle) throws IOException {
        OSCBundle oscBundle = convertToOscBundle(bundle);
        sender.send(oscBundle);
    }

    public void sendMessage(OscMessage message) throws IOException {
        OSCMessage oscMessage = convertToOscMessage(message);
        sender.send(oscMessage);
    }

    private OSCBundle convertToOscBundle(OscBundle bundle) {
        OSCBundle oscBundle = new OSCBundle(new Date(bundle.getTimestamp()));
        for (OscBundle subBundle : bundle.getBundles()) {
            oscBundle.addPacket(convertToOscBundle(subBundle));
        }
        for (OscMessage message : bundle.getMessages()) {
            oscBundle.addPacket(convertToOscMessage(message));
        }
        return oscBundle;
    }

    private OSCMessage convertToOscMessage(OscMessage message) {
        OSCMessage oscMessage = new OSCMessage(message.getAddress());
        for (Object arg : message.getArguments()) {
            oscMessage.addArgument(arg);
        }
        return oscMessage;
    }
}
