import java.util.Arrays;

public class KernelMemory {

    private static final int INDEX_FROM_BIT(int x) {
        return x / (8 * 4);
    }

    private static final int OFFSET_FROM_BIT(int x) {
        return x % (8 * 4);
    }

    public static class Paging {
        public static class Frame {
            private static int[] frames = null;
            private static int frameNumber = 0;

            public static void alloc(Page page, boolean isKernel, boolean isWriteable) {
                if (page.frame != 0) {
                    return;
                }

                int index = findFirst();

                if (index == -1) {
                    throw new RuntimeException("OH GOD WHERE ARE ALL MY MEMORIES?!?!?!?");
                }

                set(index * 0x1000);
                page.present = true;
                page.rw = isWriteable;
                page.user = !isKernel;
                page.frame = index;
            }

            public static void free(Page page) {
                int frame = page.frame;

                if (frame == 0) {
                    return;
                }

                clear(frame);
                page.frame = 0;
            }

            public static void set(int address) {
                int frame = address / 0x1000;
                int index = INDEX_FROM_BIT(frame);
                int offset = OFFSET_FROM_BIT(frame);

                frames[index] |= (0x1 << offset);
            }

            public static void clear(int address) {
                int frame = address / 0x1000;
                int index = INDEX_FROM_BIT(frame);
                int offset = OFFSET_FROM_BIT(frame);

                frames[index] &= ~(0x1 << offset);
            }

            public static boolean test(int address) {
                int frame = address / 0x1000;
                int index = INDEX_FROM_BIT(frame);
                int offset = OFFSET_FROM_BIT(frame);

                return (frames[index] & (0x1 << offset)) != 0;
            }

            public static int findFirst() {
                for (int i = 0; i < INDEX_FROM_BIT(frameNumber); i++) {
                    if (frames[i] == 0xFFFFFFFF) {
                        continue;
                    }

                    for (int h = 0; h < 32; h++) {
                        if ((frames[i] & (0x1 << h)) == 0) {
                            return h + (i * 4 * 8);
                        }
                    }
                }

                return -1;
            }

            public static void initFrames(int frameCount) {
                frameNumber = frameCount;
                frames = new int[INDEX_FROM_BIT(frameNumber)];
                Arrays.fill(frames, 0);
            }
        }

        public static class Page {
            public boolean present;
            public boolean rw;
            public boolean user;
            public int frame;
        }
    }
}
