import java.io.*;
import java.util.*;
import java.util.concurrent.*;

class Main {
    static class ForkSolver {
        private static final int MULTI = 2;
        private final ExecutorService executor;
        private final List<Future<String>> results;

        public ForkSolver() {
            this.executor = Executors.newFixedThreadPool(MULTI);
            this.results = new ArrayList<>();
        }

        public void solve(int dataId) {
            results.add(executor.submit(() -> process(dataId)));
        }

        public void waitForResults() throws InterruptedException, ExecutionException {
            executor.shutdown();
            for (int i = 1; i < results.size() + 1; i++) {
                String output = results.get(i - 1).get();
                System.out.printf("Case #%d: %s", i, output);
            }
        }

        private String process(int dataId) {
            // Replace this with your specific processing logic
            StringBuilder sb = new StringBuilder();
            for (int i = 1; i <= dataId; i++) {
                sb.append(i).append(" ");
            }
            return sb.append("\n").toString();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        ForkSolver solver = new ForkSolver();

        for (int i = 1; i <= N; i++) {
            solver.solve(i);
        }

        try {
            solver.waitForResults();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
