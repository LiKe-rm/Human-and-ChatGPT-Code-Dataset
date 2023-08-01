import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class ForkSolver {
    private static final int MULTI = 2;

    static class Pair<A, B> {
        A first;
        B second;

        Pair(A first, B second) {
            this.first = first;
            this.second = second;
        }
    }

    static class Data {
        int id;
        String content;

        Data(int id, String content) {
            this.id = id;
            this.content = content;
        }
    }

    static class SolverTask implements Callable<Data> {
        private int dataId;

        SolverTask(int dataId) {
            this.dataId = dataId;
        }

        @Override
        public Data call() throws Exception {
            return solve(dataId);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        List<Future<Data>> results = new ArrayList<>();

        ExecutorService executor = Executors.newFixedThreadPool(MULTI);

        for (int i = 1; i <= N; i++) {
            int dataId = i;
            process(dataId);
            Callable<Data> callable = new SolverTask(dataId);
            Future<Data> future = executor.submit(callable);
            results.add(future);
        }

        for (Future<Data> result : results) {
            try {
                Data data = result.get();
                System.out.println("Result for dataId " + data.id + ": " + data.content);
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();
    }

    private static void process(int dataId) {
        System.out.println("Processing dataId " + dataId);
    }

    private static Data solve(int dataId) {
        System.out.println("Solving dataId " + dataId);
        return new Data(dataId, processData(dataId));
    }

    private static String processData(int dataId) {
        // Add your data processing logic here
        return "Processed data for dataId " + dataId;
    }
}
