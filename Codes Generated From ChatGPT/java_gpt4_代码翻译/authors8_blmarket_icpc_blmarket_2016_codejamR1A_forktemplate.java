import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class ForkSolver {

    private static final int MULTI = 2;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        List<Future<String>> results = new ArrayList<>();

        ExecutorService executor = Executors.newFixedThreadPool(MULTI);

        for (int i = 1; i <= N; i++) {
            int dataId = i;
            process(dataId);
            Callable<String> callable = () -> solve(dataId);
            Future<String> future = executor.submit(callable);
            results.add(future);
        }

        for (Future<String> result : results) {
            try {
                System.out.print(result.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();
    }

    private static void process(int dataId) {
        // Add your data processing logic here
        System.out.println("Processing dataId " + dataId);
    }

    private static String solve(int dataId) {
        // Add your data solving logic here
        System.out.println("Solving dataId " + dataId);
        return "Result for dataId " + dataId + "\n";
    }
}
