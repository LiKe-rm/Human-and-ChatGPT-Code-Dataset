import java.nio.ByteBuffer;

public class LulzKey {

    public static void main(String[] args) {
        init();
    }

    public static void init() {
        int interruptNumber = 0x42;
        int ring = 1;

        if (ring <= 1) {
            switch (interruptNumber) {
                case 1:
                    disablePaging();
                    break;
                case 2:
                    enablePaging();
                    break;
                case 3:
                    setPagingDirectory(null);
                    break;
                case 4:
                    flushTLB();
                    break;
            }
        }
    }

    private static void disablePaging() {
        System.out.println("Disabling paging");
    }

    private static void enablePaging() {
        System.out.println("Enabling paging");
    }

    private static void setPagingDirectory(ByteBuffer pagingDirectory) {
        System.out.println("Setting paging directory to " + pagingDirectory);
    }

    private static void flushTLB() {
        System.out.println("Flushing TLB");
    }
}
