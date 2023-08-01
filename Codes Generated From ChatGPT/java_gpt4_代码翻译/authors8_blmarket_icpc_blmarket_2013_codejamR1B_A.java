import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Arrays;

public class ProblemSolver {

    private static int A, N;
    private static int[] V = new int[105];
    private static Map<Pair, Integer> memo = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        memo.clear();
        A = scanner.nextInt();
        N = scanner.nextInt();
        for (int i = 0; i < N; i++) {
            V[i] = scanner.nextInt();
        }
        Arrays.sort(V, 0, N);

        if (A == 1) {
            System.out.println(N);
            return;
        }

        System.out.println(go(0, A));
    }

    private static int go(int pos, int cur) {
        if (pos == N) {
            return 0;
        }

        Pair key = new Pair(pos, cur);
        if (cur > V[pos]) {
            return go(pos + 1, cur + V[pos]);
        }

        if (memo.containsKey(key)) {
            return memo.get(key);
        }

        int ret = N - pos;

        for (int i = 1; i < N - pos; i++) {
            cur += (cur - 1);
            if (cur > V[pos]) {
                int tmp = i + go(pos + 1, cur + V[pos]);
                if (tmp < ret) {
                    ret = tmp;
                }
            }
        }

        memo.put(key, ret);
        return ret;
    }

    private static class Pair {
        int pos, cur;

        public Pair(int pos, int cur) {
            this.pos = pos;
            this.cur = cur;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj instanceof Pair) {
                Pair other = (Pair) obj;
                return this.pos == other.pos && this.cur == other.cur;
            }
            return false;
        }

        @Override
        public int hashCode() {
            return 31 * pos + cur;
        }
    }
}
