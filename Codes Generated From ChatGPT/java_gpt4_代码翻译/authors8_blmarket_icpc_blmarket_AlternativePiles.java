import java.util.Arrays;

public class AlternativePiles {

    private static final int mod = 1000000007;

    private void addmod(int[] a, int index, int b) {
        a[index] += b;
        if (a[index] >= mod) a[index] -= mod;
    }

    public int count(String C, int M) {
        int[][][] memo = new int[2][55][55];
        memo[0][0][0] = 1;

        int n = C.length();
        for (int i = 0; i < n; i++) {
            int cur = i % 2;
            int nex = 1 - cur;

            if (C.charAt(i) == 'B' || C.charAt(i) == 'W') {
                System.arraycopy(memo[cur], 0, memo[nex], 0, memo[0].length);
            } else {
                for (int j = 0; j < memo[nex].length; j++) {
                    Arrays.fill(memo[nex][j], 0);
                }
            }

            if (C.charAt(i) == 'B') continue;

            for (int j = 0; j <= M; j++) {
                for (int k = 0; k < M; k++) {
                    if (memo[cur][j][k] > 0) {
                        int cc = memo[cur][j][k];
                        if (C.charAt(i) != 'G' && j < M) {
                            addmod(memo[nex][j + 1], (k + 1) % M, cc);
                        }
                        if (C.charAt(i) != 'R' && j > 0) {
                            addmod(memo[nex][j - 1], k, cc);
                        }
                    }
                }
            }
        }

        int cur = n % 2;
        return memo[cur][0][0];
    }

    public static void main(String[] args) {
        AlternativePiles solver = new AlternativePiles();
        String C = "WRGWWRGW";
        int M = 2;
        int result = solver.count(C, M);
        System.out.println("Result: " + result);
    }
}
