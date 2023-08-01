import java.util.*;
import java.util.function.BiPredicate;

public class Main {
    private static final int XX = 131072;

    private static int n, q;
    private static int[] maxs = new int[300000];
    private static int[] mins = new int[300000];
    private static int s, e;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(i, sc);
        }
    }

    private static int get(int[] arr, int pos, int a, int b, BiPredicate<Integer, Integer> func) {
        int reala = a, realb = Math.min(b, n + XX);

        if (s <= reala && e >= realb) return arr[pos];

        int mid = (a + b) / 2;

        int v1 = -1, v2 = -1;
        if (s < mid)
            v1 = get(arr, pos * 2, a, mid, func);
        if (mid < e)
            v2 = get(arr, pos * 2 + 1, mid, b, func);
        if (v1 == -1) return v2;
        if (v2 == -1) return v1;

        if (func.test(v1, v2)) return v1;
        return v2;
    }

    private static void process(int dataId, Scanner sc) {
        n = sc.nextInt();
        q = sc.nextInt();
        Arrays.fill(maxs, 0);
        Arrays.fill(mins, Integer.MAX_VALUE);

        for (int i = 0; i < n; i++) {
            maxs[XX + i] = sc.nextInt();
            mins[XX + i] = maxs[XX + i];
        }

        for (int i = XX - 1; i >= 1; i--) {
            maxs[i] = Math.max(maxs[i * 2], maxs[i * 2 + 1]);
            mins[i] = Math.min(mins[i * 2], mins[i * 2 + 1]);
        }

        for (int i = 0; i < q; i++) {
            s = sc.nextInt() + XX;
            e = sc.nextInt() + XX + 1;

            int maxv = get(maxs, 1, XX, XX * 2, (a, b) -> a > b);
            int minv = get(mins, 1, XX, XX * 2, (a, b) -> a < b);

            System.out.println(maxv - minv);
        }
    }
}
