import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MurmurHash3 {

    public static int rotl32(int x, byte r) {
        return (x << r) | (x >>> (32 - r));
    }

    public static long rotl64(long x, byte r) {
        return (x << r) | (x >>> (64 - r));
    }

    public static int fmix32(int h) {
        h ^= h >>> 16;
        h *= 0x85ebca6b;
        h ^= h >>> 13;
        h *= 0xc2b2ae35;
        h ^= h >>> 16;
        return h;
    }

    public static long fmix64(long k) {
        k ^= k >>> 33;
        k *= 0xff51afd7ed558ccdL;
        k ^= k >>> 33;
        k *= 0xc4ceb9fe1a85ec53L;
        k ^= k >>> 33;
        return k;
    }

    public static int murmurHash3_x86_32(byte[] data, int seed) {
        int len = data.length;
        int nblocks = len / 4;

        int h1 = seed;

        int c1 = 0xcc9e2d51;
        int c2 = 0x1b873593;

        ByteBuffer buf = ByteBuffer.wrap(data);
        buf.order(ByteOrder.LITTLE_ENDIAN);

        for (int i = 0; i < nblocks; i++) {
            int k1 = buf.getInt(i * 4);

            k1 *= c1;
            k1 = rotl32(k1, 15);
            k1 *= c2;

            h1 ^= k1;
            h1 = rotl32(h1, 13);
            h1 = h1 * 5 + 0xe6546b64;
        }

        int k1 = 0;
        int tailStart = nblocks * 4;
        switch (len & 3) {
            case 3:
                k1 ^= (data[tailStart + 2] & 0xff) << 16;
            case 2:
                k1 ^= (data[tailStart + 1] & 0xff) << 8;
            case 1:
                k1 ^= (data[tailStart] & 0xff);
                k1 *= c1;
                k1 = rotl32(k1, 15);
                k1 *= c2;
                h1 ^= k1;
        }

        h1 ^= len;
        h1 = fmix32(h1);

        return h1;
    }

    // murmurHash3_x86_128 and murmurHash3_x64_128 are not included in this example due to space limitations.
    // You can implement them following the same structure as murmurHash3_x86_32.
}
