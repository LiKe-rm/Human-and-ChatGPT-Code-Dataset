import java.util.HashSet;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class AmebaDiv1 {

    public int count(int[] X) {
        Set<Integer> S = new HashSet<>();

        Function<Integer, Integer> go = s -> {
            for (int x : X) {
                if (s.equals(x)) {
                    s *= 2;
                }
            }
            return s;
        };

        for (int x : X) {
            S.add(go.apply(x));
        }

        Set<Integer> SS = IntStream.of(X).boxed().collect(Collectors.toSet());
        for (int it : S) {
            SS.remove(it);
        }

        return SS.size();
    }

    public static void main(String[] args) {
        AmebaDiv1 amebaDiv1 = new AmebaDiv1();

        int[] test0 = {3, 2, 1};
        System.out.println("Test 0: " + amebaDiv1.count(test0));

        int[] test1 = {2, 2, 2, 2, 2, 2, 4, 2, 2, 2};
        System.out.println("Test 1: " + amebaDiv1.count(test1));

        int[] test2 = {1, 2, 4, 8, 16, 32, 64, 128, 256, 1024, 2048};
        System.out.println("Test 2: " + amebaDiv1.count(test2));

        int[] test3 = {854, 250, 934, 1000, 281, 250, 281, 467, 854, 562, 934, 1000, 854, 500, 562};
        System.out.println("Test 3: " + amebaDiv1.count(test3));
    }
}
