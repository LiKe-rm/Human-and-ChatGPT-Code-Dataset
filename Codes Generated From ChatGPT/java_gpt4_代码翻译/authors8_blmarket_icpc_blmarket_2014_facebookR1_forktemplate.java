import java.io.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.*;

public class ForkSolver {

    private static final int MULTI = 2;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();

        ForkSolver solver = new ForkSolver();
        solver.solveAll(N);
    }

    private final ExecutorService executor;

    public ForkSolver() {
        executor = Executors.newFixedThreadPool(MULTI);
    }

    private void solveAll(int numTasks) {
        List<Future<String>> futures = new ArrayList<>();
        for (int i = 1; i <= numTasks; i++) {
            int taskId = i;
            Callable<String> task = () -> {
                solve(taskId);
                return "Output from task " + taskId + "\n";
            };
            futures.add(executor.submit(task));
        }

        for (Future<String> future : futures) {
            try {
                System.out.print(future.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
        executor.shutdown();
    }

    private void process(int dataId) {
        // Perform data input here. Don't use scanner methods in the solve method.
    }

    private void solve(int dataId) {
        // Perform time-consuming job here.
    }
}
