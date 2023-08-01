import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class ForkSolver {
    private static final int MULTI = 3;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        ExecutorService executor = Executors.newFixedThreadPool(MULTI);
        List<Future<String>> results = new ArrayList<>();

        for (int i = 1; i <= N; i++) {
            process(i);
            Callable<String> solver = () -> solve(i);
            results.add(executor.submit(solver));
        }

        executor.shutdown();
        try {
            executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for (Future<String> future : results) {
            try {
                System.out.print(future.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
    }

    public static void process(int dataId) {
        // read data here
    }

    public static String solve(int dataId) {
        StringBuilder sb = new StringBuilder();
        sb.append(dataId).append('\n');
        sb.append("0\n");
        return sb.toString();
    }
}
