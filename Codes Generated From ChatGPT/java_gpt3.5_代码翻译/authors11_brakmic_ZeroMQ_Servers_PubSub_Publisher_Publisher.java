import org.zeromq.SocketType;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;

import java.util.Random;

public class Publisher {

    public static void main(String[] args) {
        try (ZContext context = new ZContext()) {
            ZMQ.Socket publisher = context.createSocket(SocketType.PUB);

            showInfo();

            publisher.bind("tcp://*:5556");

            sendUpdates(publisher);
        }
    }

    private static void showInfo() {
        String version = ZMQ.getVersionString();
        System.out.println("Using 0MQ version " + version);
    }

    private static void sendUpdates(ZMQ.Socket publisher) {
        Random random = new Random();

        while (true) {
            int zipcode = 10001;
            int temperature = random.nextInt(215) - 80;
            int relhumidity = random.nextInt(50) + 10;

            String update = String.format("%d %d %d", zipcode, temperature, relhumidity);
            System.out.println("Sending: " + update);

            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            publisher.send(update);
        }
    }
}
