import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Lcd {
    private Gpio RS, E, DB7, DB6, DB5, DB4;
    private boolean is_4bit;
    private LcdLine first, second;
    private Lock lock;

    public Lcd(Gpio RS, Gpio E, Gpio DB7, Gpio DB6, Gpio DB5, Gpio DB4) {
        this.RS = RS;
        this.E = E;
        this.DB7 = DB7;
        this.DB6 = DB6;
        this.DB5 = DB5;
        this.DB4 = DB4;
        is_4bit = true;
        lock = new ReentrantLock();

        init();
        clearDisplay();
        displaySet(true, true, true);
        setDirection(true, false);

        first = new LcdLine(this, 0);
        second = new LcdLine(this, 1);
    }

    private void setupGpio(Gpio a) {
        a.setSpeed(Gpio.Speed.SPEED_100MHz)
                .setPushPull()
                .setDirection(Gpio.Direction.OUTPUT);
    }

    // Other methods from the original C++ code should be converted
    // similarly to Java, with adjustments to syntax and semantics as needed.
}

public class LcdLine {
    private Lcd lcd;
    private int line;
    private boolean locked;
    private int position;

    public LcdLine() {
        lcd = null;
        line = -1;
        locked = false;
        position = 0;
    }

    public LcdLine(Lcd lcd, int line) {
        this.lcd = lcd;
        this.line = line;
        locked = false;
        position = 0;
    }

    public void set(Lcd lcd, int line) {
        this.lcd = lcd;
        this.line = line;
    }

    public LcdLine put(char c) {
        if (!locked) {
            lcd.lock.lock();
            lcd.setDDRAM(line * 40);
            position = 0;
            locked = true;
        }
        lcd.put(c);
        position++;
        return this;
    }

    public LcdLine endl() {
        if (locked) {
            for (int i = 0; i < (16 - position); ++i)
                lcd.put(' ');
            lcd.lock.unlock();
            locked = false;
        }
        return this;
    }
}
