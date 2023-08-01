import java.util.HashMap;
import java.util.Map;

public class IRRemote {
    private Timer timer;
    private Gpio gpio;
    private int tmpWord;
    private int word;
    private static final Map<Integer, Integer> remoteCodes;

    static {
        remoteCodes = new HashMap<>();
        // Digits
        remoteCodes.put(0x00ff6897, 0);
        remoteCodes.put(0x00ff30cf, 1);
        // ...
        // Other codes
        remoteCodes.put(0x00ffa25d, 100);
        // ...
    }

    public IRRemote(Timer t, Gpio g) {
        timer = t;
        gpio = g;

        g.setDirection(Gpio.Direction.INPUT)
                .setSpeed(Gpio.Speed.SPEED_100MHz)
                .setResistor(Gpio.Resistor.PULL_UP)
                .setFunction(Gpio.Function.GPIO);

        t.setPrescaler(10 * 168 / 2)
                .setAutoReload(0xffff)
                .setOneShot(true);

        tmpWord = 0;
        word = 0;
        Exti exti = new Exti(g);
        exti.enableFalling()
                .enableRising()
                .setTopCallback(this::topCallback)
                .enableIRQ();

        // Initialize data synchronization primitives
    }

    private void topCallback(int value) {
        if (gpio.read()) {
            timer.disable();
            timer.setCounter(0);
            timer.enable();
            return;
        }

        int v = timer.getCounter();

        if (v < 0x25) {
            tmpWord = 0;
        } else if (v < 0x40) {
            tmpWord <<= 1;
        } else if (v < 0x80) {
            tmpWord = 0;
        } else if (v < 0xb0) {
            tmpWord <<= 1;
            tmpWord |= 1;
        } else {
            if ((tmpWord & 0x00ff0000) == 0x00ff0000) {
                // Data synchronization logic
                word = tmpWord;
                // Log the data
            }
            tmpWord = 0;
        }
    }

    public int nextRaw() {
        // Synchronize data access
        int v = word;
        return v;
    }

    public int next() {
        int v = nextRaw();
        return remoteCodes.getOrDefault(v, -1);
    }
}
