import java.util.HashMap;

public class Exti {
    public interface Callback {
        void call(int nr);
    }

    private static HashMap<Integer, Callback> topCb = new HashMap<>();
    private static HashMap<Integer, Callback> bottomCb = new HashMap<>();

    private int chan;
    private Port port;

    public Exti(int c, Port p) {
        chan = c;
        port = p;
        setGpioPort(port.ordinal());
    }

    public Exti(Gpio p) {
        chan = p.getNumber();
        port = p.getPort();
        setGpioPort(port.ordinal());
    }

    public void extiHandler() {
        int i = 0;
        // Replace this with the actual register value for EXTI->PR
        int reg = 0;
        while (reg != 0) {
            if ((reg & 1) != 0) {
                callTopCb(i);
                // Replace this with the actual register value for EXTI->PR
                // EXTI->PR = 1 << i;
            }
            i++;
            reg >>= 1;
        }
    }

    public int irqN() {
        int irq = 40;
        switch (chan) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                irq = chan + 6;
                break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                irq = 23;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                irq = 40;
                break;
        }
        return irq;
    }

    public Exti enableIRQ() {
        // Enable the IRQ for this EXTI line
        return this;
    }

    public Exti disableIRQ() {
        // Disable the IRQ for this EXTI line
        return this;
    }

    public Exti enableRising() {
        // Enable the rising trigger for this EXTI line
        return this;
    }

    public Exti disableRising() {
        // Disable the rising trigger for this EXTI line
        return this;
    }

    public Exti enableFalling() {
        // Enable the falling trigger for this EXTI line
        return this;
    }

    public Exti disableFalling() {
        // Disable the falling trigger for this EXTI line
        return this;
    }

    public Exti setTopCb(Callback cb) {
        topCb.put(chan, cb);
        return this;
    }

    public Exti setBottomCb(Callback cb) {
        bottomCb.put(chan, cb);
        return this;
    }

    public void setGpioPort(int port) {
        // Set the GPIO port for this EXTI line
    }

    public static void callTopCb(int nr) {
        topCb.get(nr).call(nr);
    }

    // Define Port and Gpio classes used in the constructor
    public enum Port {
        PORTA,
        PORTB,
        PORTC,
        PORTD,
        PORTE,
        PORTF,
        PORTG,
        PORTH,
        PORTI
    }
    public static class Gpio {
        private int number;
        private Port port;
    
        public Gpio(int number, Port port) {
            this.number = number;
            this.port = port;
        }
    
        public int getNumber() {
            return number;
        }
    
        public Port getPort() {
            return port;
        }
    }
}    