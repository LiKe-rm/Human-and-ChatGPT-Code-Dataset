import java.util.Arrays;

public class MD2 {
    private static final int[] S = {
            41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
            19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
            76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
            138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
            245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
            148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
            39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
            181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
            150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
            112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
            96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
            85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
            234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
            129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
            8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
            203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
            166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
            31, 26, 219, 153, 141, 51, 159, 17, 131, 20
        };
        private byte[] X = new byte[48];
        private byte[] C = new byte[16];
        private byte[] buf = new byte[16];
        private int count = 0;
        
        public MD2() {
            init();
        }
        
        private void init() {
            Arrays.fill(X, (byte) 0);
            Arrays.fill(C, (byte) 0);
            Arrays.fill(buf, (byte) 0);
            count = 0;
        }
        
        public void update(byte[] input, int len) {
            int L;
        
            while (len > 0) {
                L = Math.min(16 - count, len);
                System.arraycopy(input, 0, buf, count, L);
                count += L;
                input = Arrays.copyOfRange(input, L, input.length);
                len -= L;
        
                if (count == 16) {
                    byte t;
                    int i, j;
        
                    count = 0;
                    System.arraycopy(buf, 0, X, 16, 16);
                    t = C[15];
        
                    for (i = 0; i < 16; i++) {
                        X[32 + i] = (byte) (X[16 + i] ^ X[i]);
                        t = (byte) (C[i] ^ S[(buf[i] ^ t) & 0xFF]);
                    }
        
                    t = 0;
                    for (i = 0; i < 18; i++) {
                        for (j = 0; j < 48; j += 8) {
                            t = (byte) (X[j + 0] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 1] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 2] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 3] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 4] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 5] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 6] ^= S[t & 0xFF]);
                            t = (byte) (X[j + 7] ^= S[t & 0xFF]);
                        }
                        t = (byte) ((t + i) & 0xFF);
                    }
                }
            }
        }
        
        public byte[] truncatedFinal(int size) {
            byte[] padding = new byte[16];
            int padlen;
            int i;
        
            padlen = 16 - count;
            for (i = 0; i < padlen; i++) {
                padding[i] = (byte) padlen;
            }
        
            update(padding, padlen);
            update(C, 16);
        
            byte[] hash = Arrays.copyOf(X, size);
            init();
            return hash;
        }
}