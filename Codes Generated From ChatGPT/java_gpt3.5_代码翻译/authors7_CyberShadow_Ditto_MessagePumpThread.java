import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class MessagePumpThread {

    private ExecutorService executor;
    private AtomicBoolean running;

    public MessagePumpThread() {
        running = new AtomicBoolean(false);
    }

    public void start() {
        if (executor == null || executor.isShutdown()) {
            executor = Executors.newSingleThreadExecutor();
        }

        executor.submit(this::runMessagePump);
        running.set(true);
    }

    public void stop() {
        if (executor != null) {
            executor.shutdown();
            try {
                if (!executor.awaitTermination(10, TimeUnit.SECONDS)) {
                    executor.shutdownNow();
                }
            } catch (InterruptedException e) {
                executor.shutdownNow();
            }
            running.set(false);
        }
    }

    public void postMsg(Message msg) {
        if (running.get()) {
            executor.submit(() -> takeMsg(msg));
        }
    }

    private void runMessagePump() {
        // Replace this with actual message pump logic
        // In Java, there isn't a direct equivalent to a Windows message pump
        // You would have to implement your own message queue for processing
    }

    private void takeMsg(Message msg) {
        // Handle the message here
    }

    public static class Message {
        public int id;
        public Object wParam;
        public Object lParam;

        public Message(int id, Object wParam, Object lParam) {
            this.id = id;
            this.wParam = wParam;
            this.lParam = lParam;
        }
    }
}
