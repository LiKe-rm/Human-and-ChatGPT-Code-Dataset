import com.illposed.osc.transport.udp.OSCPortIn;
import com.illposed.osc.OSCMessage;
import com.illposed.osc.OSCMessageEvent;
import com.illposed.osc.OSCMessageListener;

import java.net.SocketException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class OscReceiver {

    private OSCPortIn receiver;
    private BlockingQueue<OscMessage> messageQueue;

    public OscReceiver() {
        messageQueue = new LinkedBlockingQueue<>();
    }

    public void setup(int listenPort) throws SocketException {
        if (receiver != null) {
            shutdown();
        }

        receiver = new OSCPortIn(listenPort);
        receiver.addMessageListener(new OSCMessageListener() {
            @Override
            public void acceptMessage(OSCMessageEvent event) {
                OSCMessage oscMessage = event.getMessage();
                OscMessage message = new OscMessage();

                message.setAddress(oscMessage.getAddress());
                message.setRemoteEndpoint(event.getSource().getAddress().getHostAddress(), event.getSource().getPort());

                for (Object arg : oscMessage.getArguments()) {
                    if (arg instanceof Integer) {
                        message.addIntArg((Integer) arg);
                    } else if (arg instanceof Float) {
                        message.addFloatArg((Float) arg);
                    } else if (arg instanceof String) {
                        message.addStringArg((String) arg);
                    } else {
                        assert false : "Message argument is not int, float, or string";
                    }
                }

                messageQueue.offer(message);
            }
        });

        receiver.startListening();
    }

    public void shutdown() {
        if (receiver != null) {
            receiver.stopListening();
            receiver.close();
            receiver = null;
        }
    }

    public boolean hasWaitingMessages() {
        return !messageQueue.isEmpty();
    }

    public OscMessage getNextMessage() {
        return messageQueue.poll();
    }
}
