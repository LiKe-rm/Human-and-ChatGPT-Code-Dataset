import java.util.*;

public class Main {
    private static Deque<Integer> lllll = new ArrayDeque<>();
    private static int k, n;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(i, sc);
        }
    }

    public static void process(int dataId, Scanner sc) {
        k = sc.nextInt();
        n = sc.nextInt();
        long cur = 1983;
        long sum = 0;
        int ret = 0;
        lllll.clear();

        for (int i = 0; i < n; i++) {
            int tmp = (int) (cur % 10000) + 1;

            lllll.addLast(tmp);
            sum += tmp;

            while (sum > k) {
                sum -= lllll.pollFirst();
            }

            if (sum == k) {
                ret++;
            }

            cur = (cur * 214013L + 2531011L) % (1L << 32);
        }
        System.out.println(ret);
    }
}
