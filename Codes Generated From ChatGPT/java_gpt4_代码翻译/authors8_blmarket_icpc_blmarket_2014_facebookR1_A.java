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
        Main.str = sc.next();
        Main.num = sc.nextLong();
    }

    public String solve(int dataId) {
        StringBuilder ret = new StringBuilder();
        Main.num--;
        long pow = 1;
        int i;
        for (i = 1;; i++) {
            if (Main.num / Main.str.length() < pow) break;
            pow *= Main.str.length();
            Main.num -= pow;
        }

        while (i-- > 0) {
            ret.append(Main.str.charAt((int) (Main.num % Main.str.length())));
            Main.num /= Main.str.length();
        }

        ret.reverse();
        return String.format("Case #%d: %s", dataId, ret.toString());
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
    public static String str;
    public static long num;

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        ForkSolver solver = new ForkSolver();
        for (int i = 1; i <= N; i++) {
            solver.runSolve(i, sc);
        }
        for (Future<String> future : solver.getFutures()) {
            System.out.println(future.get());
        }
        solver.shutdown();
    }
}
