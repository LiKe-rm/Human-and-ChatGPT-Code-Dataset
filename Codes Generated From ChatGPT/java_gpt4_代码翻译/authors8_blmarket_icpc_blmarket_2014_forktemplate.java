import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class ForkSolver {

    private static final int MULTI = 2;

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();

        ForkSolver solver = new ForkSolver();
        solver.solveAll(N);
    }

    private final ExecutorService executor;

    public ForkSolver() {
        executor = Executors.newFixedThreadPool(MULTI);
    }

    private void solveAll(int numTasks) throws IOException {
        List<Future<String>> futures = new ArrayList<>();
        for (int i = 1; i <= numTasks; i++) {
            int taskId = i;
            Callable<String> task = () -> {
                ProcessBuilder pb = new ProcessBuilder("java", "SolveTask", String.valueOf(taskId));
                Process process = pb.start();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                    return reader.readLine();
                }
            };
            futures.add(executor.submit(task));
        }

        for (Future<String> future : futures) {
            try {
                System.out.println(future.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
        executor.shutdown();
    }
}

public class SolveTask {

    public static void main(String[] args) {
        int dataId = Integer.parseInt(args[0]);
        process(dataId);
        solve(dataId);
    }

    private static void process(int dataId) {
        // Perform data input here. Don't use scanner methods in the solve method.
    }

    private static void solve(int dataId) {
        // Perform time-consuming job here.
        System.out.println("Output from task " + dataId);
    }
}

