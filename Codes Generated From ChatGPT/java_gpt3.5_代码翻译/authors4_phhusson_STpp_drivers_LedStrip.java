public class LedStrip {
    private Spi spi;

    public LedStrip(Spi spi) {
        this.spi = spi;
        spi.master()
                .setLsbFirst(true)
                .setDivisorPow2(4)
                .enable();
    }

    private static void ledSetBit(byte[] buf, int offset, int b) {
        int o = (offset * 3) + 1;
        int index = o / 8;
        int bit = o % 8;

        if (b != 0) {
            buf[index] |= 1 << bit;
        } else {
            buf[index] &= ~(1 << bit);
        }
    }

    private static void ledSetByte(byte[] buf, int offset, int v) {
        v &= 0xff;
        for (int i = 0; i < 8; ++i) {
            ledSetBit(buf, offset + i, (v & (1 << (7 - i))) != 0 ? 1 : 0);
        }
    }

    private static void ledstripInit(byte[] buf) {
        for (int i = 0; i < 24; ++i) {
            int bit = (i * 3) % 8;
            int index = i * 3 / 8;
            buf[index] |= 1 << bit;

            bit += 2;
            if (bit >= 8) {
                bit -= 8;
                index++;
            }

            buf[index] &= ~(1 << bit);
        }
    }

    public LedStrip init(byte[] buf, int nleds, int len) {
        if (len < nleds * 9) throw new IllegalArgumentException("Length is too short.");
        for (int i = 0; i < nleds; ++i)
            ledstripInit(buf, 9 * i);

        return this;
    }

    public LedStrip prepare(byte[] buf, int id, int r, int g, int b) {
        ledSetByte(buf, id * 9, g);
        ledSetByte(buf, id * 9 + 8, r);
        ledSetByte(buf, id * 9 + 16, b);
        return this;
    }

    public LedStrip push(int r, int g, int b) {
        byte[] dmaBuf = new byte[9];
        ledstripInit(dmaBuf);
        ledSetByte(dmaBuf, 0, g);
        ledSetByte(dmaBuf, 8, r);
        ledSetByte(dmaBuf, 16, b);
        spi.send(dmaBuf, 9);
        return this;
    }

    public LedStrip reset() {
        byte[] dmaBuf = new byte[5];
        spi.send(dmaBuf, dmaBuf.length);
        return this;
    }

    public LedStrip push(byte[] buf, int nleds) {
        spi.send(buf, nleds * 9);
        reset();
        return this;
    }
}
