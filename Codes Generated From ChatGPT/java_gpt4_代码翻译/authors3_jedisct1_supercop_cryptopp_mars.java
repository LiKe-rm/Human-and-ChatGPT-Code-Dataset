// Mars.java

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Mars {
    private static final int[] Sbox = new int[512];
    // Initialize Sbox here

    private static int rotlConstant(int value, int shift) {
        return (value << shift) | (value >>> (32 - shift));
    }

    private static int rotrConstant(int value, int shift) {
        return (value >>> shift) | (value << (32 - shift));
    }

    private static int rotlMod(int value, int shift) {
        shift &= 31;
        return (value << shift) | (value >>> (32 - shift));
    }

    private static int S(int a) {
        return Sbox[a & 0x1FF];
    }

    private static int S0(int a) {
        return Sbox[a & 0xFF];
    }

    private static int S1(int a) {
        return Sbox[(a & 0xFF) + 256];
    }

    private int[] m_k;

    public Mars(byte[] userKey) {
        m_k = new int[40];
        uncheckedSetKey(userKey);
    }

    private void uncheckedSetKey(byte[] userKey) {
        int length = userKey.length;
        if (length < 1 || length > 56) {
            throw new IllegalArgumentException("Invalid key length");
        }

        int[] T = new int[15];
        ByteBuffer bb = ByteBuffer.wrap(userKey).order(ByteOrder.LITTLE_ENDIAN);
        for (int i = 0; i < length / 4; i++) {
            T[i] = bb.getInt();
        }
        T[length / 4] = length / 4;

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 15; i++) {
                T[i] = T[i] ^ rotlConstant(T[(i + 8) % 15] ^ T[(i + 13) % 15], 3) ^ (4 * i + j);
            }

            for (int k = 0; k < 4; k++) {
                for (int i = 0; i < 15; i++) {
                    T[i] = rotlConstant(T[i] + Sbox[T[(i + 14) % 15] % 512], 9);
                }
            }

            for (int i = 0; i < 10; i++) {
                m_k[10 * j + i] = T[4 * i % 15];
            }
        }

        for (int i = 5; i < 37; i += 2) {
            int m, w = m_k[i] | 3;
            m = (~w ^ (w << 1)) & (~w ^ (w >>> 1)) & 0x7FFFFFFE;
            m &= m >>> 1;
            m &= m >>> 2;
            m &= m >>> 4;
            m |= m << 1;
            m |= m << 2;
            m |= m << 4;
            m &= 0x7FFFFFFC;
            w ^= rotlMod(Sbox[265 + (m_k[i] & 3)], m_k[i - 1]) & m;
            m_k[i] = w;
        }
    }

    public byte[] encrypt(byte[] inBlock) {
        int a, b, c, d, t;
        ByteBuffer bb = ByteBuffer.wrap(inBlock).order(ByteOrder.LITTLE_ENDIAN);
        a = bb.getInt();
        b = bb.getInt();
        c = bb.getInt();
        d = bb.getInt();
        a += m_k[0];
        b += m_k[1];
        c += m_k[2];
        d += m_k[3];
    
        for (int i = 0; i < 8; i++) {
            b = (b ^ S0(a)) + S1(a >> 8);
            c += S0(a >> 16);
            a = rotrConstant(a, 24);
            d ^= S1(a);
            a += (i % 4 == 0) ? d : 0;
            a += (i % 4 == 1) ? b : 0;
            t = a;
            a = b;
            b = c;
            c = d;
            d = t;
        }
    
        for (int i = 0; i < 16; i++) {
            t = rotlConstant(a, 13);
            int r = rotlConstant(t * m_k[2 * i + 5], 10);
            int m = a + m_k[2 * i + 4];
            int l = rotlMod((S(m) ^ rotrConstant(r, 5) ^ r), r);
            c += rotlMod(m, rotrConstant(r, 5));
            if (i < 8) {
                b += l;
                d ^= r;
            } else {
                d += l;
                b ^= r;
            }
            a = b;
            b = c;
            c = d;
            d = t;
        }
    
        for (int i = 0; i < 8; i++) {
            a -= (i % 4 == 2) ? d : 0;
            a -= (i % 4 == 3) ? b : 0;
            b ^= S1(a);
            c -= S0(a >> 24);
            t = rotlConstant(a, 24);
            d = (d - S1(a >> 16)) ^ S0(t);
            a = b;
            b = c;
            c = d;
            d = t;
        }
    
        a -= m_k[36];
        b -= m_k[37];
        c -= m_k[38];
        d -= m_k[39];
    
        ByteBuffer outBuffer = ByteBuffer.allocate(16).order(ByteOrder.LITTLE_ENDIAN);
        outBuffer.putInt(a).putInt(b).putInt(c).putInt(d);
        return outBuffer.array();
    }
    
    public byte[] decrypt(byte[] inBlock) {
        int a, b, c, d, t;
        ByteBuffer bb = ByteBuffer.wrap(inBlock).order(ByteOrder.LITTLE_ENDIAN);
        d = bb.getInt();
        c = bb.getInt();
        b = bb.getInt();
        a = bb.getInt();
    
        d += m_k[36];
        c += m_k[37];
        b += m_k[38];
        a += m_k[39];
    
        for (int i = 0; i < 8; i++) {
            b = (b ^ S0(a)) + S1(a >> 8);
            c += S0(a >> 16);
            a = rotrConstant(a, 24);
            d ^= S1(a);
            a += (i % 4 == 0) ? d : 0;
            a += (i % 4 == 1) ? b : 0;
            t = a;
            a = b;
            b = c;
            c = d;
            d = t;
        }           
        for (int i = 0; i < 16; i++) {
            t = rotrConstant(a, 13);
            int r = rotlConstant(a * m_k[35 - 2 * i], 10);
            int m = t + m_k[34 - 2 * i];
            int l = rotlMod((S(m) ^ rotrConstant(r, 5) ^ r), r);
            c -= rotlMod(m, rotrConstant(r, 5));
            if (i < 8) {
                b -= l;
                d ^= r;
            } else {
                d -= l;
                b ^= r;
            }
            a = b;
            b = c;
            c = d;
            d = t;
        }
    
        for (int i = 0; i < 8; i++) {
            a -= (i % 4 == 2) ? d : 0;
            a -= (i % 4 == 3) ? b : 0;
            b ^= S1(a);
            c -= S0(a >> 24);
            t = rotlConstant(a, 24);
            d = (d - S1(a >> 16)) ^ S0(t);
            a = b;
            b = c;
            c = d;
            d = t;
        }
    
        d -= m_k[0];
        c -= m_k[1];
        b -= m_k[2];
        a -= m_k[3];
    
        ByteBuffer outBuffer = ByteBuffer.allocate(16).order(ByteOrder.LITTLE_ENDIAN);
        outBuffer.putInt(d).putInt(c).putInt(b).putInt(a);
        return outBuffer.array();
    }
}        