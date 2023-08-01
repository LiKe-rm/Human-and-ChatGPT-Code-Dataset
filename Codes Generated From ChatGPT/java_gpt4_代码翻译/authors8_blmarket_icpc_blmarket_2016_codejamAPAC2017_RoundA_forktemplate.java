import java.io.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.stream.*;

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

class SolveTask {

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

class Utils {
    public static <T> int size(Collection<T> collection) {
        return collection.size();
    }

    public static <T> List<List<T>> createMatrix(int numRows, int numCols) {
        return Stream.generate(() -> new ArrayList<T>(Collections.nCopies(numCols, null)))
                .limit(numRows)
                .collect(Collectors.toList());
    }

    public static <K, V> Map<K, V> createMap() {
        return new HashMap<>();
    }

    public static <T> Set<T> createSet() {
        return new HashSet<>();
    }

    public static <T> List<T> createList() {
        return new ArrayList<>();
    }

    public static <T> Queue<T> createQueue() {
        return new LinkedList<>();
    }

    public static <T> void forEach(Iterable<T> iterable, Consumer<? super T> action) {
        for (T t : iterable) {
            action.accept(t);
        }
    }

    public static long sqr(long x) {
        return x * x;
    }

    public static Pair<Long, Long> makePair(long first, long second) {
        return new Pair<>(first, second);
    }

    public static <T> void pushBack(List<T> list, T element) {
        list.add(element);
    }
}

class Pair<F, S> {
    private F first;
    private S second;

    public Pair(F first, S second) {
        this.first = first;
        this.second = second;
    }

    public F getFirst() {
        return first;
    }

    public S getSecond() {
        return second;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass())         return false;
        Pair<?, ?> pair = (Pair<?, ?>) o;
        return Objects.equals(first, pair.first) &&
                Objects.equals(second, pair.second);
    }

    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }

    @Override
    public String toString() {
        return "Pair{" +
                "first=" + first +
                ", second=" + second +
                '}';
    }
}

class Vector<T> extends ArrayList<T> {
    public Vector() {
        super();
    }

    public Vector(int initialCapacity) {
        super(initialCapacity);
    }

    public Vector(Collection<? extends T> c) {
        super(c);
    }
}

class VectorVector<T> extends ArrayList<Vector<T>> {
    public VectorVector() {
        super();
    }

    public VectorVector(int initialCapacity) {
        super(initialCapacity);
    }

    public VectorVector(Collection<? extends Vector<T>> c) {
        super(c);
    }
}

