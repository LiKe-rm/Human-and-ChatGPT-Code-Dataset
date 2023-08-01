import java.util.*;

class Main {
    private static final int MAX_SIZE = 1000005;
    private static List<Integer> primes = new ArrayList<>();
    private static int nn;
    private static int[] nums = new int[MAX_SIZE];
    private static int[] cnts = new int[MAX_SIZE];

    public static void main(String[] args) {
        precalc();
        Scanner scanner = new Scanner(System.in);
        int testCases = scanner.nextInt();
        for (int i = 1; i <= testCases; i++) {
            process(scanner);
        }
    }

    private static void process(Scanner scanner) {
        int n, l, h;
        n = scanner.nextInt();
        l = scanner.nextInt();
        h = scanner.nextInt();
        nn = h - l + 1;

        for (int i = 0; i < nn; i++) {
            nums[i] = i + l;
            cnts[i] = 1;
        }

        for (int i = 0; i < primes.size(); i++) {
            if (primes.get(i) > h) {
                break;
            }
            int left = (l / primes.get(i)) * primes.get(i);
            if (left < l) {
                left += primes.get(i);
            }
            while (left <= h) {
                int tmp = left;
                int j = 0;
                while (tmp % primes.get(i) == 0) {
                    tmp /= primes.get(i);
                    j++;
                }
                cnts[left - l] *= (j + 1);
                left += primes.get(i);
            }
        }

        int ret = 0;
        for (int i = 0; i < nn; i++) {
            if (cnts[i] == n) {
                ret++;
            }
        }
        System.out.println(ret);
    }

    private static void precalc() {
        primes.add(2);
        for (int i = 3; i <= 10000000; i += 2) {
            boolean fail = false;
            for (int j = 0; j < primes.size(); j++) {
                if (primes.get(j) * primes.get(j) > i) {
                    break;
                }
                if (i % primes.get(j) == 0) {
                    fail = true;
                    break;
                }
            }
            if (!fail) {
                primes.add(i);
            }
        }
    }
}
