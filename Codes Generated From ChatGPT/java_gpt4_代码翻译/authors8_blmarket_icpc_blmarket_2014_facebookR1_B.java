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
        Main.K = sc.nextInt();
        Main.C = sc.nextInt();
    }

    public int go(int n) {
        int kk = Main.K % n;
        int base = Main.K / n;
        if (base * n >= Main.C) {
            return Main.C;
        }
        return (n - kk) + Main.C;
    }

    public String solve(int dataId) {
        int ret = -1;
        for (int i = Main.N; i >= 1; i--) {
            int tmp = go(i) + (Main.N - i);
            if (ret == -1 || ret > tmp) ret = tmp;
        }
        return String.format("Case #%d: %d", dataId, ret);
    }

    public void runSolve(int dataId, Scanner sc) {
        process(dataId, sc);
        Callable<String> task = () -> solve(dataId);
        Future<String> future = executor.submit(task);
        futures.add(future);
        nchilds++;
    }

    public void shutdown() {
        executor.shutdown();
    }

    public List<Future<String>> getFutures() {
        return futures;
    }
}

public class Main {
    public static int N;
    public static int K;
    public static int C;

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        ForkSolver solver = new ForkSolver();
        for (int i = 1; i <= T; i++) {
            solver.runSolve(i, sc);
        }
        for (Future<String> future : solver.getFutures()) {
            System.out.println(future.get());
        }
        solver.shutdown();
    }
}
