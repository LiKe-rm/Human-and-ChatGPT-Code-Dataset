import org.bouncycastle.crypto.BufferedBlockCipher;
import org.bouncycastle.util.Arrays;
import org.bouncycastle.util.encoders.Hex;

import java.util.ArrayDeque;
import java.util.Deque;

public class MessageQueue {
    private ByteQueue queue;
    private Deque<Long> lengths;
    private Deque<Long> messageCounts;

    public MessageQueue(int nodeSize) {
        this.queue = new ByteQueue(nodeSize);
        this.lengths = new ArrayDeque<>();
        this.messageCounts = new ArrayDeque<>();
        this.lengths.add(0L);
        this.messageCounts.add(0L);
    }

    public long maxRetrievable() {
        return this.queue.size();
    }

    public long transferTo(BufferedBlockCipher target, long transferBytes) {
        transferBytes = Math.min(maxRetrievable(), transferBytes);
        long transferredBytes = queue.transferTo(target, transferBytes);
        lengths.set(0, lengths.peek() - transferredBytes);
        return transferredBytes;
    }

    public boolean getNextMessage() {
        if (numberOfMessages() > 0 && !anyRetrievable()) {
            lengths.poll();
            if (messageCounts.peek() == 0 && messageCounts.size() > 1) {
                messageCounts.poll();
            }
            return true;
        } else {
            return false;
        }
    }

    public int numberOfMessages() {
        return lengths.size() - 1;
    }

    public boolean anyRetrievable() {
        return maxRetrievable() > 0;
    }

    public int copyMessagesTo(BufferedBlockCipher target, int count) {
        ByteQueue.Walker walker = queue.walker();
        int i;
        for (i = 0; i < count && !lengths.isEmpty(); i++) {
            walker.transferTo(target, lengths.poll());
        }
        return i;
    }

    public void swap(MessageQueue other) {
        ByteQueue tempQueue = this.queue;
        this.queue = other.queue;
        other.queue = tempQueue;

        Deque<Long> tempLengths = this.lengths;
        this.lengths = other.lengths;
        other.lengths = tempLengths;
    }

    public byte[] spy(int[] contiguousSize) {
        byte[] result = queue.spy(contiguousSize);
        contiguousSize[0] = (int) Math.min(contiguousSize[0], maxRetrievable());
        return result;
    }

    // ... Implement remaining methods as needed.
}
