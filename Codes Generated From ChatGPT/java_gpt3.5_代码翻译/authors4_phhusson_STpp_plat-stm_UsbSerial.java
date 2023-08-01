import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class UsbSerial {
    private final BlockingQueue<Character> rxQueue;
    private final Object lock = new Object();

    public UsbSerial() {
        // Initialize USB-related hardware and callbacks.
        // In Java, you cannot directly access hardware registers as in C++.
        // You might need to use a native library or JNI to achieve this.
        rxQueue = new LinkedBlockingQueue<>(128);
    }

    public UsbSerial put(char c) {
        synchronized (lock) {
            try {
                rxQueue.put(c);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            return this;
        }
    }

    public UsbSerial endl() {
        put('\r');
        put('\n');
        return this;
    }

    public int get() {
        try {
            return rxQueue.take();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return -1;
        }
    }

    public boolean available() {
        return !rxQueue.isEmpty();
    }

    public void waitData() {
        try {
            rxQueue.peek();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
