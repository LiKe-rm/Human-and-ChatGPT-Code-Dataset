package cryptopp;

public class GF2_32 {

    private int m_modulus;

    public GF2_32(int modulus) {
        this.m_modulus = modulus;
    }

    public int multiply(int a, int b) {
        int[] table = new int[4];
        table[0] = 0;
        table[1] = m_modulus;
        if ((a & 0x80000000) != 0) {
            table[2] = m_modulus ^ (a << 1);
            table[3] = a << 1;
        } else {
            table[2] = a << 1;
            table[3] = m_modulus ^ (a << 1);
        }

        b = Integer.rotateRight(b, 30);
        int result = table[b & 2];

        for (int i = 29; i >= 0; --i) {
            b = Integer.rotateLeft(b, 1);
            result = (result << 1) ^ table[(b & 2) + (result >>> 31)];
        }

        return (b & 1) != 0 ? result ^ a : result;
    }

    public int multiplicativeInverse(int a) {
        if (a <= 1) {
            return a;
        }

        int g0 = m_modulus, g1 = a, g2 = a;
        int v0 = 0, v1 = 1, v2 = 1;

        while ((g2 & 0x80000000) == 0) {
            g2 <<= 1;
            v2 <<= 1;
        }

        g2 <<= 1;
        v2 <<= 1;

        g0 ^= g2;
        v0 ^= v2;

        while (g0 != 1) {
            if (g1 < g0 || ((g0 ^ g1) < g0 && (g0 ^ g1) < g1)) {
                g2 = g1;
                v2 = v1;
            } else {
                g2 = g0;
                g0 = g1;
                g1 = g2;
                v2 = v0;
                v0 = v1;
                v1 = v2;
            }

            while ((g0 ^ g2) >= g2) {
                g2 <<= 1;
                v2 <<= 1;
            }

            g0 ^= g2;
            v0 ^= v2;
        }

        return v0;
    }

    private int bitPrecision(int value) {
        return 32 - Integer.numberOfLeadingZeros(value);
    }

    public static void main(String[] args) {
        GF2_32 gf2_32 = new GF2_32(0x25);
        int a = 0x12;
        int b = 0x15;
        System.out.println("Multiplication: " + Integer.toHexString(gf2_32.multiply(a, b)));
        System.out.println("Multiplicative Inverse: " + Integer.toHexString(gf2_32.multiplicativeInverse(a)));
    }
}
