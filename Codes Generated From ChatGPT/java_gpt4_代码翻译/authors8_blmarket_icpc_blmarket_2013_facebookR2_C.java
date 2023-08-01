import java.util.*;
import java.math.BigInteger;

public class Main {
    static int N;
    static int[][] rela = new int[1005][2];
    static int[][] combi = new int[1005][1005];
    static Map<BitSet, Integer> memo = new HashMap<>();

    public static void main(String[] args) {
        precalc();
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(sc);
        }
        sc.close();
    }

    static void precalc() {
        for (int i = 0; i <= 1000; i++) {
            combi[i][0] = combi[i][i] = 1;
            for (int j = 1; j < i; j++) {
                combi[i][j] = combi[i - 1][j - 1] + combi[i - 1][j];
                combi[i][j] %= 1000000007;
            }
        }
    }

    static void take2(int pos, BitSet ret) {
        ret.set(pos);
        for (int i = 0; i < N - 1; i++) {
            if (rela[i][0] == pos && !ret.get(rela[i][1])) {
                take2(rela[i][1], ret);
            }
            if (rela[i][1] == pos && !ret.get(rela[i][0])) {
                take2(rela[i][0], ret);
            }
        }
    }

    static void take(int pos, int no, BitSet ret) {
        ret.set(pos);
        for (int i = 0; i < N - 1; i++) {
            if (rela[i][0] == pos && rela[i][1] != no) {
                take2(rela[i][1], ret);
            }
            if (rela[i][1] == pos && rela[i][0] != no) {
                take2(rela[i][0], ret);
            }
        }
        ret.clear(pos);
    }

    static int go(BitSet st) {
        if (memo.containsKey(st)) {
            return memo.get(st);
        }
        BitSet candi = (BitSet) st.clone();

        int cnt = candi.cardinality();
        if (cnt == 0) return 1;

        for (int i = 0; i < N - 1; i++) {
            int p1 = rela[i][0];
            int p2 = rela[i][1];
            if (!st.get(p1) || !st.get(p2)) continue;
            candi.clear(p2);
        }

        long rett = 0;
        for (int i = 0; i < N; i++) {
            if (candi.get(i)) {
                long ret = 1;
                int cnt2 = cnt - 1;
                for (int j = 0; j < N - 1; j++) {
                    if (rela[j][0] == i) {
                        BitSet tmp = new BitSet();
                        take(rela[j][1], i, tmp);
                        tmp.set(rela[j][1]);
                        tmp.and(st);

                        int tmp2 = tmp.cardinality();

                        ret *= combi[cnt2][tmp2];
                        cnt2 -= tmp2;
                        ret %= 1000000007;

                        ret *= go(tmp);
                        ret %= 1000000007;
                    }
                }
                rett += ret;
                rett %= 1000000007;
            }
        }
        int result = (int) rett;
        memo.put(st, result);
        return result;
    }

    static void process(Scanner sc) {
        memo.clear();
        N = sc.nextInt();
        for (int i = 0; i + 1 < N; i++) {
            rela[i][0] = sc.nextInt();
            String flag = sc.next();
            rela[i][1] = sc.nextInt();
            if (flag.equals(">")) {
                int temp = rela[i][0];
                rela[i][0] = rela[i][1];
                rela[i][1] = temp;
            }
        }

        BitSet candi = new BitSet(N);
        for (int i = 0; i < N; i++) {
            candi.set(i);
        }
        int ret = go(candi);
        System.out.println(ret);
    }
}                       
