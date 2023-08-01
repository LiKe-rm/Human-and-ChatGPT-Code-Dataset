import org.zeromq.SocketType;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Receiver {

    public static void main(String[] args) {
        int maxMessages = 100;
        String filter = args.length > 1 ? args[1] : "10001";

        try (ZContext context = new ZContext()) {
            Socket subscriber = context.createSocket(SocketType.SUB);

            showInfo();

            System.out.println("Collecting updates from server");
            subscriber.connect("tcp://localhost:5556");

            subscriber.subscribe(filter.getBytes(ZMQ.CHARSET));

            processMessages(maxMessages, subscriber);
        }
    }

    private static void showInfo() {
        String version = ZMQ.getVersionString();
        System.out.println("Using 0MQ version " + version);
    }

    private static void processMessages(int maxMessages, Socket subscriber) {
        int updateNbr;
        long totalTemp = 0;

        for (updateNbr = 0; updateNbr < maxMessages; updateNbr++) {
            String message = subscriber.recvStr();
            List<Integer> data = Arrays.stream(message.split("\\s"))
                    .map(Integer::parseInt)
                    .collect(Collectors.toList());

            int zip = data.get(0);
            int temp = data.get(1);
            int hum = data.get(2);

            System.out.println("ZIP: " + zip + " TEMP: " + temp + " HUM: " + hum);
            totalTemp += temp;
        }

        System.out.println("TOTAL TEMP: " + totalTemp);
        System.out.println("AVG. TEMP: " + (int) (totalTemp / updateNbr));
    }
}
