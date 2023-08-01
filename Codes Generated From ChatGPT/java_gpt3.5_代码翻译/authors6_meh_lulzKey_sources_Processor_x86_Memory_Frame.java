import java.util.BitSet;

public class FrameManager {
    private static final int FRAME_SIZE = 0x1000;
    private BitSet frames;
    private int frameNumber;

    public FrameManager(int frameNumber) {
        this.frameNumber = frameNumber;
        this.frames = new BitSet(frameNumber);
    }

    public void alloc(Page page, boolean isKernel, boolean isWriteable) {
        if (page.getFrame() != 0) {
            return;
        }

        int index = findFirst();

        if (index == -1) {
            throw new RuntimeException("OH GOD WHERE ARE ALL MY MEMORIES?!?!?!?");
        }

        set(index * FRAME_SIZE);
        page.setPresent(true);
        page.setReadWrite(isWriteable);
        page.setUserMode(!isKernel);
        page.setFrame(index);
    }

    public void free(Page page) {
        int frame = page.getFrame();

        if (frame == 0) {
            return;
        }

        clear(frame);
        page.setFrame(0);
    }

    public void set(int address) {
        int frame = address / FRAME_SIZE;
        frames.set(frame);
    }

    public void clear(int address) {
        int frame = address / FRAME_SIZE;
        frames.clear(frame);
    }

    public boolean test(int address) {
        int frame = address / FRAME_SIZE;
        return frames.get(frame);
    }

    public int findFirst() {
        for (int i = 0; i < frameNumber; i++) {
            if (!frames.get(i)) {
                return i;
            }
        }
        return -1;
    }
}

class Page {
    private boolean present;
    private boolean readWrite;
    private boolean userMode;
    private int frame;

    // getters and setters

    public boolean isPresent() {
        return present;
    }

    public void setPresent(boolean present) {
        this.present = present;
    }

    public boolean isReadWrite() {
        return readWrite;
    }

    public void setReadWrite(boolean readWrite) {
        this.readWrite = readWrite;
    }

    public boolean isUserMode() {
        return userMode;
    }

    public void setUserMode(boolean userMode) {
        this.userMode = userMode;
    }

    public int getFrame() {
        return frame;
    }

    public void setFrame(int frame) {
        this.frame = frame;
    }
}
