import java.nio.ByteBuffer;

public class Ax12 {
    private Gpio gpio;
    private Uart uart;
    private int id;
    private boolean deferred;
    private byte[] buf;
    private int bufPos;
    private int checksum;

    public Ax12(Gpio g, Uart u, int i) {
        uart = u;
        id = i;
        gpio = g;

        u.configGpio(g);
        g.setDirection(Gpio.Direction.OUTPUT)
                .setResistor(Gpio.Resistor.PULL_UP);

        uart.enable()
                .setFraction(0x6)
                .setHalfDuplex(true)
                .enableReceive()
                .enableTransmitter();

        deferred = false;
        buf = new byte[16];
        bufPos = 0;
    }

    public Ax12(Uart u, int i, Gpio g, Gpio rx, Gpio tx) {
        uart = u;
        id = i;
        gpio = g;

        u.configGpio(rx, tx);
        g.setPushPull()
                .setDirection(Gpio.Direction.OUTPUT)
                .setSpeed(Gpio.Speed.SPEED_100MHz)
                .setResistor(Gpio.Resistor.PULL_UP);

        uart.enable()
                .setMantissa(0x16)
                .setFraction(0x6)
                .enableReceive()
                .enableTransmitter();

        deferred = false;
        buf = new byte[16];
        bufPos = 0;
        gpio.set(false);
    }

    // ... (省略其他方法以保持代码简洁)

    private void prelude() {
        buf[bufPos++] = (byte) 0xff;
        buf[bufPos++] = (byte) 0xff;
        buf[bufPos++] = (byte) id;
        checksum = id;
    }

    private void put(byte v) {
        buf[bufPos++] = v;
        if (bufPos >= buf.length) {
            throw new RuntimeException("Buffer overflow");
        }
        checksum += v;
    }

    private void putChecksum() {
        buf[bufPos++] = (byte) ~checksum;
        flush();
        bufPos = 0;
    }

    // ... (省略其他方法以保持代码简洁)
}
