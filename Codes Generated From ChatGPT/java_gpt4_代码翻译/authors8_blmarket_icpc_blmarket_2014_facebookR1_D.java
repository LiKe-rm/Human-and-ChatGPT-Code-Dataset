import java.util.*;
import java.util.concurrent.*;

public class Main {
    static int N, K;
    static List<Integer> V = new ArrayList<>();
    static List<Integer> V2 = new ArrayList<>();
    static List<Integer> primes = new ArrayList<>();
    static int[] used;

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        generatePrimes();
        ExecutorService executor = Executors.newFixedThreadPool(3);
        List<Future<String>> futures = new ArrayList<>();

        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int dataId = 1; dataId <= T; dataId++) {
            process(dataId, sc);
            futures.add(executor.submit(() -> solve(dataId)));
        }
        sc.close();

        for (int i = 0; i < T; i++) {
            System.out.print(futures.get(i).get());
        }
        executor.shutdown();
    }

    public static void generatePrimes() {
        primes.add(2);
        for (int i = 3; i < 20000; i += 2) {
            boolean isPrime = true;
            for (int prime : primes) {
                if (i % prime == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.add(i);
            }
            if (primes.size() > 120) {
                break;
            }
        }
    }

    public static void process(int dataId, Scanner sc) {
        N = sc.nextInt();
        K = sc.nextInt();
        V.clear();
        for (int i = 0; i < N; i++) {
            int tmp = sc.nextInt();
            V.add(tmp);
        }
    }

    public static String solve(int dataId) {
        int base = 0;
        boolean hasZero = false;
        V2.clear();
        for (int i = 0; i < N; i++) {
            int t1 = (V.get(i) + (K - 1)) / K;
            if (t1 == 0) {
                if (hasZero) {
                    t1 = 1;
                }
                hasZero = true;
            }
            base += t1 * K - V.get(i);
            if (t1 <= 1) {
                continue;
            }
            V2.add((V.get(i) + (K - 1)) / K);
        }
        if (V2.size() > 0 && hasZero) {
            base += K;
        }

        V2.sort(Comparator.naturalOrder());

        used = new int[primes.size()];
        if (V2.size() > 0) {
            base += go(0, V2.get(0), 10000) * K;
        }

        return String.format("Case #%d: %d%n", dataId, base);
    }

    public static int go(int pos, int sv, int cut) {
        if (pos == V2.size()) {
            return 0;
        }
        if (sv < V2.get(pos)) {
            sv = V2.get(pos);
        }

        int ret = cut;
        for (int i = 0; i < Math.min(cut, 10); i++, sv++) {
            int tmp = sv;
            boolean go = true;
            for (int j = 0; j < primes.size(); j++) {
                if (tmp % primes.get(j) == 0 && used[j] != 0) {
                    go = false;
                    break
            }
            while (tmp % primes.get(j) == 0) {
                tmp /= primes.get(j);
            }
        }
        if (!go) {
            continue;
        }
        tmp = sv;
        for (int j = 0; j < primes.size(); j++) {
            if (tmp % primes.get(j) == 0) {
                used[j] = 1;
            }
        }

        int chk = go(pos + 1, sv + 1, ret) + sv - V2.get(pos);
        if (ret > chk) {
            ret = chk;
        }

        for (int j = 0; j < primes.size(); j++) {
            if (tmp % primes.get(j) == 0) {
                used[j] = 0;
            }
        }
    }
    return ret;
}
}