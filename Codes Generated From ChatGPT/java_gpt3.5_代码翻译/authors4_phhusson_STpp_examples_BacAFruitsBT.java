import java.io.IOException;

public class Main {
    public static void main(String[] args) throws InterruptedException, IOException {
        System.out.println("startup");

        ZigbeeUart.getInstance()
                .enable()
                .setMantissa(0x10e)
                .setFraction(0xc)
                .enableReceive()
                .enableTransmitter();

        ZigbeeTx.getInstance()
                .setPushPull()
                .setAlternate(Gpio.USART4_6)
                .setDirection(Gpio.OUTPUT)
                .setSpeed(Gpio.SPEED_100MHz);

        ZigbeeRx.getInstance()
                .setAlternate(Gpio.USART4_6)
                .setDirection(Gpio.INPUT)
                .setSpeed(Gpio.SPEED_100MHz)
                .setResistor(Gpio.PULL_UP);

        DmaStream uartDma = new DmaStream(1, 4, 7);
        Gpio ax12Pin = GpioB.get(10);
        Ax12 ax12Broadcast = new Ax12(ax12Pin, new Uart(3, uartDma), 0xfe);
        Ax12 ax12Left = new Ax12(ax12Pin, new Uart(3, uartDma), 0x83);
        Ax12 ax12Right = new Ax12(ax12Pin, new Uart(3, uartDma), 0x82);
        Ax12 ax12Under = new Ax12(ax12Pin, new Uart(3, uartDma), 0x81);

        ax12Broadcast.setSpeed(0x80);
        ax12Broadcast.enable();

        while (true) {
            char c;
            ZigbeeUart.getInstance().write("Going to startup position...");
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

            ZigbeeUart.getInstance().write("done.\n");
            c = (char) ZigbeeUart.getInstance().read();

            ZigbeeUart.getInstance().write("Going to open position...");
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
            ZigbeeUart.getInstance().write("done.\n");

            c = (char) ZigbeeUart.getInstance().read();

            ZigbeeUart.getInstance().write("Going to closed position...");
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
            ZigbeeUart.getInstance().write("done.\n");

            c = (char) ZigbeeUart.getInstance().read();
        }
        /*
         * while(1) { ax12_broadcast.goTo(0x200); time.msleep(5000);
         * ax12_broadcast.goTo(0x330); time.msleep(5000); }
         */

        /*
         * while(1) { ax12_broadcast.goTo(0x200); time.msleep(5000);
         * ax12_broadcast.goTo(0xb0); time.msleep(5000); }
         */ // bac plus eleve
        /*
         * Ouvre en cone ferme symetrique // recule while (1) { ax12_left.goTo(0x200);
         * time.msleep(10); ax12_right.goTo(0x200); time.msleep(10);
         * ax12_under.goTo(0x200); time.msleep(10);
         * 
         * time.msleep(5000);
         * 
         * ax12_left.goTo(0xb0); time.msleep(10); ax12_right.goTo(0x90);
         * time.msleep(10); ax12_under.goTo(0x330); time.msleep(10);
         * time.msleep(5000); }
         */
    }
}