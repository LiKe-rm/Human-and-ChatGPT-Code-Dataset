import java.util.HashMap;

public class Gpio {
    public enum Direction {
        INPUT,
        OUTPUT,
        ANALOG,
        ALTERNATE
    }

    public enum Function {
        GPIO,
        TIMER,
        SPI,
        I2C,
        USART,
        UART,
        CAN,
        USB,
        ETHERNET
    }

    public enum Resistor {
        NONE,
        PULL_UP,
        PULL_DOWN
    }

    public enum Speed {
        SPEED_2MHZ,
        SPEED_25MHZ,
        SPEED_50MHZ,
        SPEED_100MHZ
    }

    public enum AF {
        AF0,
        AF1,
        AF2,
        AF3,
        AF4,
        AF5,
        AF6,
        AF7,
        AF8,
        AF9,
        AF10,
        AF11,
        AF12,
        AF13,
        AF14,
        AF15
    }

    private static HashMap<Integer, GpioPort> portMap = new HashMap<>();

    private int number;
    private GpioPort port;
    private Direction direction;
    private Function function;

    public Gpio(GpioPort p, int n) {
        port = p;
        number = n;
        function = Function.GPIO;
        direction = Direction.INPUT;
    }

    public Gpio& setState(boolean v) {
        if (v) {
            // Set pin
            me.BSRRL = 1 << number;
        } else {
            // Reset pin
            me.BSRRH = 1 << number;
        }
        return this;
    }

    public boolean operator=(boolean v) {
        setState(v);
        return v;
    }

    public Gpio& setSpeed(Speed s) {
        int v = 0;
        switch (s) {
            case SPEED_2MHZ:
                v = 0;
                break;
            case SPEED_25MHZ:
                v = 1;
                break;
            case SPEED_50MHZ:
                v = 2;
                break;
            case SPEED_100MHZ:
                v = 3;
                break;
        }
        me.OSPEEDR = (me.OSPEEDR & ~(3 << (2 * number))) | v << (2 * number);
        return this;
    }

    public Gpio& setPushPull() {
        me.OTYPER &= ~(1 << number);
        return this;
    }

    public Gpio& setOpenDrain() {
        me.OTYPER |= 1 << number;
        return this;
    }

    public void updateModeR() {
        if (direction == Direction.ANALOG)
            me.MODER = me.MODER | 3 << (2 * number);
        else if (function != Function.GPIO)
            me.MODER = (me.MODER & ~(3 << (2 * number))) | 2 << (2 * number);
        else if (direction == Direction.INPUT)
            me.MODER = me.MODER & ~(3 << (2 * number));
        else
            me.MODER = (me.MODER & ~(3 << (2 * number))) | 1 << (2 * number);
    }

    public Gpio& setDirection(Direction d) {
        direction = d;
        updateModeR();
        return this;
    }

    public Gpio& setFunction(Function f) {
        function = f;
        updateModeR();
        return this;
    }

    public Gpio& setResistor(Resistor r) {
        int v = 0;
        switch (r) {
            case NONE:
                v = 0;
                break;
            case PULL_UP:
                v = 1;
                break;
            case PULL_DOWN:
                v = 2;
                break;
        }
        me.PUPDR = (me.PUPDR & ~(3 << (2 * number))) | (v << (2 * number));
        return this;
    }
    
    public Gpio& setAlternate(int af) {
        setFunction(Function.ALTERNATE);
        int n = number;
        if (n >= 8) {
            n -= 8;
            me.AFR[1] = (me.AFR[1] & ~(0xf << (4 * n))) |
                    af << (4 * n);
        } else {
            me.AFR[0] = (me.AFR[0] & ~(0xf << (4 * n))) |
                    af << (4 * n);
        }
        return this;
    }
    
    public Gpio& setAlternate(AF a) {
        setAlternate(a.ordinal());
        return this;
    }
    
    public static class GpioPort {
        private volatile GPIO_TypeDef base;
    
        public GpioPort(GPIO_TypeDef base) {
            this.base = base;
            // Get the number of the GPIO port based on base
            int n = getPortNumber();
            RCC.AHB1ENR |= 1 << n;
        }
    
        public int getPortNumber() {
            int n = (((int) base) >> 10) & 0xf;
            return n;
        }
    }
}    
