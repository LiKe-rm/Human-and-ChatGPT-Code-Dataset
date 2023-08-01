import java.util.Arrays;

public class Keccak {

    private static final long[] KECCAK_F1600_CONSTANTS = new long[]{
            0x0000000000000001L, 0x0000000000008082L,
            0x800000000000808aL, 0x8000000080008000L,
            0x000000000000808bL, 0x0000000080000001L,
            0x8000000080008081L, 0x8000000000008009L,
            0x000000000000008aL, 0x0000000000000088L,
            0x0000000080008009L, 0x000000008000000aL,
            0x000000008000808bL, 0x800000000000008bL,
            0x8000000000008089L, 0x8000000000008003L,
            0x8000000000008002L, 0x8000000000000080L,
            0x000000000000800aL, 0x800000008000000aL,
            0x8000000080008081L, 0x8000000000008080L,
            0x0000000080000001L, 0x8000000080008008L
    };

    public static void keccakF1600(long[] state) {
        long[] tempState = new long[25];
        System.arraycopy(state, 0, tempState, 0, state.length);

        for (int round = 0; round < 24; round += 2) {
            KeccakRound.round(tempState, round);
            KeccakRound.round(tempState, round + 1);
        }

        System.arraycopy(tempState, 0, state, 0, state.length);
    }
}
public class KeccakRound {

    public static void round(long[] state, int round) {
        long[] b = new long[5];
        long[] t = new long[5];

        // Theta step
        for (int i = 0; i < 5; i++) {
            b[i] = state[i] ^ state[i + 5] ^ state[i + 10] ^ state[i + 15] ^ state[i + 20];
        }

        for (int i = 0; i < 5; i++) {
            t[i] = b[(i + 4) % 5] ^ Long.rotateLeft(b[(i + 1) % 5], 1);
            for (int j = 0; j < 25; j += 5) {
                state[j + i] ^= t[i];
            }
        }

        // Rho and Pi steps
        long last = state[1];
        int x = 1, y = 0;
        for (int t = 0; t < 24; t++) {
            int newX = y;
            int newY = (2 * x + 3 * y) % 5;
            x = newX;
            y = newY;

            long current = state[5 * y + x];
            state[5 * y + x] = Long.rotateLeft(last, (t + 1) * (t + 2) / 2);
            last = current;
        }
    }
}

