public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("startup");

        DmaStream uartDma = new DmaStream(1, 4, 7);
        Gpio ax12Pin = GpioB.get(10);
        Ax12 ax12Broadcast = new Ax12(ax12Pin, new Uart(3, uartDma), 0xfe);
        Ax12 ax12Left = new Ax12(ax12Pin, new Uart(3, uartDma), 0x83);
        Ax12 ax12Right = new Ax12(ax12Pin, new Uart(3, uartDma), 0x82);
        Ax12 ax12Under = new Ax12(ax12Pin, new Uart(3, uartDma), 0x81);

        ax12Broadcast.setSpeed(0x80);
        ax12Broadcast.enable();

        while (true) {
            // Closed
            {
                ax12Left.goTo(0xb0);
                Thread.sleep(10);
                ax12Right.goTo(0x90);
                Thread.sleep(10);
                Thread.sleep(300);
                ax12Under.goTo(0x330);
                Thread.sleep(10);
            }

            Thread.sleep(5000);

            // To go forward
            {
                ax12Under.goTo(0x280);
                Thread.sleep(10);
                Thread.sleep(300);

                int delta = 0x40;
                ax12Left.goTo(0x200 + delta);
                Thread.sleep(10);
                ax12Right.goTo(0x200 - delta);
                Thread.sleep(10);
            }

            Thread.sleep(5000);

            // To go backward
            {
                int delta = 0x15;
                ax12Left.goTo(0x200 - delta);
                Thread.sleep(10);
                ax12Right.goTo(0x200 + delta);
                Thread.sleep(10);
                ax12Under.goTo(0x280);
                Thread.sleep(10);
            }

            Thread.sleep(5000);
        }
    }
}
