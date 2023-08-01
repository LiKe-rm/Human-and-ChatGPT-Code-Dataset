import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AlwaysDefined {

    private int W;
    private List<Integer>[] nr;
    private Map<Pair, Long> memo;

    private static class Pair {
        long maxK;
        int r;

        public Pair(long maxK, int r) {
            this.maxK = maxK;
            this.r = r;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair pair = (Pair) o;
            return maxK == pair.maxK && r == pair.r;
        }

        @Override
        public int hashCode() {
            int result = (int) (maxK ^ (maxK >>> 32));
            result = 31 * result + r;
            return result;
        }
    }

    private long go2(long maxK, int r) {
        if (r == 1) return maxK + 1;

        Pair key = new Pair(maxK, r);
        if (memo.containsKey(key)) return memo.get(key);

        long ret = 0;
        for (int it : nr[r]) {
            if (maxK - it < 0) break;
            long maxW = (maxK - it) / r;
            int nrValue = (it * W + r) / r;
            ret += go2(maxW, nrValue);
        }

        memo.put(key, ret);
        return ret;
    }

    private long go(long A) {
        long ret = 0;
        for (int i = 1; i < W; i++) {
            if (A < i) break;
            long k = (A - i) / W;
            ret += go2(k, i);
        }
        return ret;
    }

    public long countIntegers(long L, long R, int W_) {
        memo = new HashMap<>();
        W = W_;
        nr = new ArrayList[W];
        for (int i = 1; i < W; i++) {
            nr[i] = new ArrayList<>();
            for (int j = 0; j < i; j++) {
                if ((j * W + i) % i != 0) continue;
                nr[i].add(j);
            }
        }
        return go(R) - go(L - 1);
    }

    public static void main(String[] args) {
        AlwaysDefined solver = new AlwaysDefined();
        long L = 52654107011850814L;
        long R = 744472477227325439L;
        int W_ = 2028;
        long result = solver.countIntegers(L, R, W_);
        System.out.println("Result: " + result);
    }
}
