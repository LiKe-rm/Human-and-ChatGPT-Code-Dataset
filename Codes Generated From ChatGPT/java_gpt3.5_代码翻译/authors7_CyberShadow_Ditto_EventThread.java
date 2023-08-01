import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.*;

public class EventThread {
    private static final int EXIT_EVENT = -1;

    private final ConcurrentHashMap<Integer, CountDownLatch> eventMap = new ConcurrentHashMap<>();
    private ExecutorService executorService;
    private Runnable eventThreadFnc;
    private Object param;
    private volatile boolean threadRunning = false;
    private volatile boolean exitThread = false;
    private long waitTimeout = 1000;

    public EventThread() {
        addEvent(EXIT_EVENT);
    }

    public void addEvent(int eventId) {
        eventMap.put(eventId, new CountDownLatch(1));
    }

    public boolean fireEvent(int eventId) {
        CountDownLatch latch = eventMap.get(eventId);
        if (latch != null) {
            latch.countDown();
            return true;
        }
        return false;
    }

    public boolean undoFireEvent(int eventId) {
        CountDownLatch latch = eventMap.get(eventId);
        if (latch != null) {
            if (latch.getCount() == 0) {
                eventMap.put(eventId, new CountDownLatch(1));
                return true;
            }
        }
        return false;
    }

    public void start(Object param) {
        if (!threadRunning) {
            exitThread = false;
            this.param = param;
            executorService = Executors.newSingleThreadExecutor();
            eventThreadFnc = this::runThread;
            executorService.execute(eventThreadFnc);
        } else {
            undoFireEvent(EXIT_EVENT);
        }
    }

    public void stop(int waitTime) {
        if (threadRunning) {
            exitThread = true;
            fireEvent(EXIT_EVENT);

            if (waitTime > 0) {
                try {
                    if (!executorService.awaitTermination(waitTime, TimeUnit.MILLISECONDS)) {
                        executorService.shutdownNow();
                        threadRunning = false;
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private void onTimeout(Object param) {
        System.out.println("Timeout occurred");
    }

    private void onEvent(int eventId, Object param) {
        System.out.println("Event " + eventId + " occurred");
    }

    private void runThread() {
        threadRunning = true;

        while (!exitThread) {
            boolean anyFired = false;

            for (Map.Entry<Integer, CountDownLatch> entry : eventMap.entrySet()) {
                try {
                    if (entry.getValue().await(waitTimeout, TimeUnit.MILLISECONDS)) {
                        anyFired = true;
                        int eventId = entry.getKey();

                        if (eventId == EXIT_EVENT) {
                            break;
                        } else {
                            onEvent(eventId, param);
                        }
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            if (!anyFired) {
                onTimeout(param);
            }
        }

        threadRunning = false;
    }

    public static void main(String[] args) {
        EventThread eventThread = new EventThread();
        eventThread.addEvent(1);
        eventThread.addEvent(2);
        eventThread.start(null);

        try {
            TimeUnit.SECONDS.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        eventThread.fireEvent(1);
        eventThread.fireEvent(2);

        try {
            TimeUnit.SECONDS.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        eventThread.stop(1000);
    }
}
