import java.util.Arrays;

public class KKrunchyDepacker {

    private static final int CodeModel = 0;
    private static final int PrevMatchModel = 2;
    private static final int MatchLowModel = 3;
    private static final int LiteralModel = 35;
    private static final int Gamma0Model = 291;
    private static final int Gamma1Model = 547;
    private static final int SizeModels = 803;

    private static class DepackState {
        byte[] src;
        int code, range;
        int[] model = new int[SizeModels];
    }

    private static DepackState st = new DepackState();

    private static boolean decodeBit(int index, int move) {
        int bound;
        boolean result;

        bound = (st.range >>> 11) * st.model[index];
        if (st.code < bound) {
            st.range = bound;
            st.model[index] += (2048 - st.model[index]) >>> move;
            result = false;
        } else {
            st.code -= bound;
            st.range -= bound;
            st.model[index] -= st.model[index] >>> move;
            result = true;
        }

        if (st.range < 0x01000000) {
            st.code = (st.code << 8) | (st.src[0] & 0xFF);
            st.src = Arrays.copyOfRange(st.src, 1, st.src.length);
            st.range <<= 8;
        }

        return result;
    }

    private static int decodeTree(int model, int maxb, int move) {
        int ctx = 1;
        while (ctx < maxb)
            ctx = (ctx * 2) + (decodeBit(model + ctx, move) ? 1 : 0);

        return ctx - maxb;
    }

    private static int decodeGamma(int model) {
        int value = 1;
        int ctx = 1;

        do {
            ctx = ctx * 2 + (decodeBit(model + ctx, 5) ? 1 : 0);
            value = (value * 2) + (decodeBit(model + ctx, 5) ? 1 : 0);
            ctx = ctx * 2 + (value & 1);
        } while ((ctx & 2) != 0);

        return value;
    }

    public static int kKrunchyDepacker(byte[] dst, byte[] src) {
        int i, code, offs, len, R0, LWM;

        st.code = 0;
        for (i = 0; i < 4; i++) {
            st.code = (st.code << 8) | (src[i] & 0xFF);
        }

        st.src = Arrays.copyOfRange(src, 4, src.length);
        st.range = ~0;
        Arrays.fill(st.model, 1024);

        code = 0;
        LWM = 0;
        int dstIndex = 0;

        while (true) {
            switch (code) {
                case 0:
                    dst[dstIndex++] = (byte) decodeTree(LiteralModel, 256, 4);
                    LWM = 0;
                    break;

                case 1:
                    len = 0;

                    if (LWM == 0 && decodeBit(PrevMatchModel, 5)) {
                        offs = R0;
                    } else {
                        offs = decodeGamma(Gamma0Model);
                        if (offs == 0) {
                            return dstIndex;
                        }

                        offs -= 2;
                        offs = (offs << 4) + decodeTree(MatchLowModel + (offs != 0 ? 16 : 0), 16, 5) + 1;

                        if (offs >= 2048) len++;
                        if (offs >= 96) len++;
                    }

                    R0 = offs;
                    LWM = 1;
                    len += decodeGamma(Gamma1Model);

                    while (len-- > 0) {
                        dst[dstIndex] = dst[dstIndex - offs];
                        dstIndex++;
                    }
                    break;
            }

            code = decodeBit(CodeModel + LWM, 5) ? 1 : 0;
        }
    }

    public static void main(String[] args) {
        byte[] src = new byte[]{...}; // Fill with compressed data
        byte[] dst = new byte[1024]; // Allocate enough space for decompressed data

        int decompressedSize = kKrunchyDepacker(dst, src);
        System.out.println("Decompressed size: " + decompressedSize);
    }
}
                           
