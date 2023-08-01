import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int testCases = scanner.nextInt();
        for (int i = 1; i <= testCases; i++) {
            process(scanner);
            solve();
        }
    }

    static int MOD = 1000000007;
    static String str;
    static List<Integer> vals;
    static int[] nn = new int[10];
    static int n, m;

    static class MemoKey {
        List<Integer> elasp;
        int cur;

        public MemoKey(List<Integer> elasp, int cur) {
            this.elasp = new ArrayList<>(elasp);
            this.cur = cur;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            MemoKey memoKey = (MemoKey) o;
            return cur == memoKey.cur && elasp.equals(memoKey.elasp);
        }

        @Override
        public int hashCode() {
            return Objects.hash(elasp, cur);
        }
    }

    static Map<MemoKey, Integer> memo = new HashMap<>();

    static int go(int cur, int pos, List<Integer> elasp, boolean chk) {
        if (pos == n) {
            return !chk && (cur == 0) ? 1 : 0;
        }
        if (!chk) {
            MemoKey key = new MemoKey(elasp, cur);
            if (memo.containsKey(key)) {
                return memo.get(key);
            }
        }

        int ret = 0;
        for (int i = 0; i < 10; i++) {
            if (elasp.get(i) > 0) {
                if (chk && vals.get(pos) < i) continue;
                elasp.set(i, elasp.get(i) - 1);
                ret += go((cur * 10 + i) % m, pos + 1, elasp, chk && vals.get(pos) == i);
                ret %= MOD;
                elasp.set(i, elasp.get(i) + 1);
            }
        }
        if (chk) return ret;
        memo.put(new MemoKey(elasp, cur), ret);
        return ret;
    }

    static void solve() {
        List<Integer> tmp = new ArrayList<>();
        for (int i = 0; i < 10; i++) tmp.add(nn[i]);
        System.out.println(go(0, 0, tmp, true));
    }

    static void process(Scanner scanner) {
        str = scanner.next();
        m = scanner.nextInt();
        n = str.length();
        vals = new ArrayList<>();
        Arrays.fill(nn, 0);
        for (int i = 0; i < n; i++) {
            vals.add(str.charAt(i) - '0');
            nn[vals.get(i)]++;
        }
        memo.clear();
    }
}
