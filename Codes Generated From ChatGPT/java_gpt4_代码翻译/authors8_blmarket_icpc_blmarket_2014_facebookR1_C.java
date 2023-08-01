import java.io.*;
import java.util.*;
import java.util.concurrent.*;

class ForkSolver {
    private int nchilds;
    private ExecutorService executor;
    private List<Future<String>> futures;

    public ForkSolver() {
        this.nchilds = 0;
        this.executor = Executors.newFixedThreadPool(2);
        this.futures = new ArrayList<>();
    }

    public void process(int dataId, Scanner sc) {
        Main.N = sc.nextInt();
        Main.M = sc.nextInt();
        for (int i = 0; i < Main.N; i++) {
            Main.data[i] = sc.next().toCharArray();
        }
    }

    public int go(int a, int b) {
        if (a >= Main.N || b >= Main.M || Main.data[a][b] == '#') return -1;
        if (Main.maxr[a][b] != 0) return Main.maxr[a][b];
        return Main.maxr[a][b] = Math.max(0, Math.max(go(a + 1, b), go(a, b + 1))) + 1;
    }

    public int go2(int a, int b) {
        if (Main.memo[a][b] != -1) return Main.memo[a][b];

        int ret = 1;
        if (b + 1 < Main.M && Main.data[a][b + 1] != '#') {
            ret = Math.max(ret, go2(a, b + 1) + 1);
            int aa = a;
            int bb = b + 1;
            int mr = Main.maxr[a][bb];
            for (int i = 0;; i++) {
                if (bb + 1 < Main.M && Main.data[aa][bb + 1] != '#') {
                    mr = Math.max(mr, Main.maxr[aa][bb + 1] + i + 2);
                }
                if (aa == 0 || Main.data[aa - 1][bb] == '#') {
                    break;
                }
                aa--;
            }
            ret = Math.max(ret, mr);
        }

        if (a + 1 < Main.N && Main.data[a + 1][b] != '#') {
            ret = Math.max(ret, go2(a + 1, b) + 1);
            int aa = a + 1;
            int bb = b;
            int mr = Main.maxr[aa][b];
            for (int i = 0;; i++) {
                if (aa + 1 < Main.N && Main.data[aa + 1][bb] != '#') {
                    mr = Math.max(mr, Main.maxr[aa + 1][bb] + i + 2);
                }
                if (bb == 0 || Main.data[aa][bb - 1] == '#') break;
                bb--;
            }
            ret = Math.max(ret, mr);
        }

        return Main.memo[a][b] = ret;
    }

    public String solve(int dataId) {
        for (int i = 0; i < Main.N; i++) {
            Arrays.fill(Main.maxr[i], 0);
            Arrays.fill(Main.memo[i], -1);
        }
        for (int i = 0; i < Main.N; i++) {
            for (int j = 0; j < Main.M; j++) {
                go(i, j);
            }
        }

        return String.format("Case #%d: %d", dataId, go2(0, 0));
    }

    public void _solve(int dataId, Scanner sc) {
        process(dataId, sc);
        futures.add(executor.submit(() -> solve(dataId)));
    }

    public void shutdown() {
        executor.shutdown();
    }
}

public class Main {
    public static int N, M;
    public static char[][] data = new char[510][510];
    public static int[][] maxr = new int[510][510];
    public static int[][] memo = new int[510][510];

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        ForkSolver solver = new ForkSolver();
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            solver._solve(i, sc);
        }
        sc.close();

        for (int i = 0; i < T; i++) {
            System.out.println(solver.futures.get(i).get());
        }
        solver.shutdown();
    }
}

