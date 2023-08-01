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

    public String solve(int dataId) {
        return String.format("Case #%d: ", dataId);
    }

    public void process(int dataId) {
    }

    public void runSolve(int dataId) {
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
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        ForkSolver solver = new ForkSolver();
        for (int i = 1; i <= N; i++) {
            solver.process(i);
            solver.runSolve(i);
        }
        for (Future<String> future : solver.getFutures()) {
            System.out.print(future.get());
        }
        solver.shutdown();
    }
}
