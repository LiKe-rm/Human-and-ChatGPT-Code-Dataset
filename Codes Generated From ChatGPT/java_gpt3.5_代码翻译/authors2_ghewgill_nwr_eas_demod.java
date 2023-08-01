import java.util.Arrays;

public class EASDemod {

    private static final int CORRLEN = 11025;
    private static final int BPHASESTEP = 0x10000 / 1920;

    private final float[][][] ref = new float[2][2][CORRLEN];
    private float[] overlapBuf = new float[CORRLEN];
    private int overlap;
    private int bPhase;
    private int bitCount;
    private int lastBit;
    private int bits;
    private int sameBytes;
    private int hIndex;
    private int byte;

    public EASDemod() {
        double f0 = 2 * Math.PI * (3 / 1920e-6);
        double f1 = 2 * Math.PI * (4 / 1920e-6);
        for (int i = 0; i < CORRLEN; i++) {
            ref[0][0][i] = (float) Math.sin(i / 11025.0 * f0);
            ref[0][1][i] = (float) Math.cos(i / 11025.0 * f0);
            ref[1][0][i] = (float) Math.sin(i / 11025.0 * f1);
            ref[1][1][i] = (float) Math.cos(i / 11025.0 * f1);
        }
        overlap = 0;
        bPhase = 0;
        bitCount = 0;
        lastBit = 0;
        bits = 0;
        sameBytes = 0;
        hIndex = -5;
    }

    public void demod(float[] buf, int n) {
        if (overlap > 0) {
            if (n >= CORRLEN) {
                System.arraycopy(buf, 0, overlapBuf, overlap, (CORRLEN - 1));
                int r = gotSamples(overlapBuf, overlap + CORRLEN - 1);
                overlap = 0;
            } else {
                System.arraycopy(buf, 0, overlapBuf, overlap, n);
                overlap += n;
                if (overlap >= CORRLEN) {
                    int r = gotSamples(overlapBuf, overlap);
                    System.arraycopy(overlapBuf, r, overlapBuf, 0, (overlap - r));
                    overlap -= r;
                }
                return;
            }
        }
        int r = gotSamples(buf, n);
        buf = Arrays.copyOfRange(buf, r, buf.length);
        n -= r;
        if (n > 0) {
            System.arraycopy(buf, 0, overlapBuf, 0, n);
            overlap = n;
        }
    }

    private int gotSamples(float[] buf, int n) {
        int r = 0;
        while (n >= CORRLEN) {
            double c00 = corr(buf, ref[0][0], CORRLEN);
            double c01 = corr(buf, ref[0][1], CORRLEN);
            double c10 = corr(buf, ref[1][0], CORRLEN);
            double c11 = corr(buf, ref[1][1], CORRLEN);
            double d = (c10 * c10 + c11 * c11) - (c00 * c00 + c01 * c01);
            int bit = d > 0 ? 1 : 0;
            if (bitcount == 0) {
                if (bit == lastbit) {
                    bits++;
                    if (bits >= 9) {
                        bitcount = 1;
                        bits = 0;
                    }
                } else {
                    bits = 1;
                    lastbit = bit;
                }
            } else {
                if (bit != lastbit) {
                    samebytes++;
                } else {
                    samebytes = 0;
                }
    
                byte >>= 1;
                if (bit == 1) {
                    byte |= 0x80;
                }
    
                if (samebytes == 8) {
                    byte = 0;
                    bitcount = 0;
                    hindex = -5;
                } else {
                    bitcount++;
                    if (bitcount == 9) {
                        bitcount = 1;
                        if (hindex < 0) {
                            hindex++;
                            lastheader = "";
                        } else {
                            lastheader += String.format("%02X", byte);
                            hindex++;
    
                            if (hindex == 5) {
                                // 此处处理得到的5字节header，如解码数据或其他操作
                                System.out.println("Header: " + lastheader);
                                hindex = -5;
                            }
                        }
                    }
                }
            }
    
            lastbit = bit;
            bphase += BPHASESTEP;
            if (bphase >= 0x10000) {
                bphase -= 0x10000;
                r++;
                n--;
            }
    
            FloatBuffer buffer = FloatBuffer.wrap(buf);
            buffer.position(r);
            buffer.get(buf, 0, n);
        }
        return r;
    }
    
    private double corr(float[] buf, float[] ref, int n) {
        double s = 0;
        for (int i = 0; i < n; i++) {
            s += buf[i] * ref[i];
        }
        return s;
    }
}    
