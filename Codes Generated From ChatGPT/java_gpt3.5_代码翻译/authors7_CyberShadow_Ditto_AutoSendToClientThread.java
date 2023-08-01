import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class AutoSendToClientThread extends Thread {
    private final BlockingQueue<ClipList> clipQueue;
    private final List<Client> clients;
    private final Object lock;
    private final int maxSendClients = 5;

    public AutoSendToClientThread() {
        clipQueue = new LinkedBlockingDeque<>();
        clients = new ArrayList<>();
        lock = new Object();
    }

    public void fireSendToClient(ClipList clipList) {
        if (!isAlive()) {
            start();
        }

        synchronized (lock) {
            if (isAlive()) {
                System.out.println("Adding clip to send to client in thread");

                clipQueue.offer(clipList);
                lock.notify();
            } else {
                System.out.println("Error creating thread to send to clients");
            }
        }
    }

    @Override
    public void run() {
        while (!isInterrupted()) {
            ClipList clipList = null;

            synchronized (lock) {
                while (clipQueue.isEmpty()) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        return;
                    }
                }
                clipList = clipQueue.poll();
            }

            if (clipList != null) {
                onSendToClient(clipList);
            }
        }
    }

    private void onSendToClient(ClipList clipList) {
        sendToClient(clipList);
    }

    private boolean sendToClient(ClipList clipList) {
        System.out.println("@@@@@@@@@@@@@@@ - START OF SendClientThread - @@@@@@@@@@@@@@@");

        if (clipList == null) {
            System.out.println("ERROR if(clipList == null)");
            return false;
        }

        int count = clipList.size();

        System.out.printf("Start of Send ClientThread Count - %d%n", count);

        for (int clientIndex = 0; clientIndex < maxSendClients; clientIndex++) {
            Client client = clients.get(clientIndex);

            if (client.isSendAll() && client.getIp().length() > 0) {
                if (!client.openConnection()) {
                    System.out.printf("ERROR opening connection to %s%n", client.getIp());

                    if (!client.isShownFirstError()) {
                        String message = String.format("Error opening connection to %s", client.getIp());
                        Main.sendReceiveError(message);

                        client.setShownFirstError(true);
                    }

                    continue;
                }

                client.setShownFirstError(false);

                for (Clip clip : clipList) {
                    System.out.printf("Sending clip to %s%n", client.getIp());

                    if (!client.sendItem(clip)) {
                        String message = String.format("Error sending clip to %s", client.getIp());
                        Main.sendReceiveError(message);
                        break;
                    }
                }

                client.closeConnection();
            }
        }

        System.out.println("@@@@@@@@@@@@@@@ - END OF SendClientThread - @@@@@@@@@@@@@@@");

        return true;
    }
}
