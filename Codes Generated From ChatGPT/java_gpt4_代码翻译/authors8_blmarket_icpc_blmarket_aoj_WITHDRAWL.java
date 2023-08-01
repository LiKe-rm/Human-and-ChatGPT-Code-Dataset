import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(sc);
        }
    }

    private static void process(Scanner sc) {
        int n = sc.nextInt();
        int k = sc.nextInt();
        List<Pair> data = new ArrayList<>();
        Map<Integer, Integer> memo[] = new HashMap[1002];

        for (int i = 0; i < 1002; i++) {
            memo[i] = new HashMap<>();
        }
        
        long s1 = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            int second = sc.nextInt();
            int first = sc.nextInt();
            data.add(new Pair(second, first));
            s1 += second;
            s2 += first;
        }

        while (data.size() > k) {
            long t1 = s1 - data.get(data.size() - 1).second;
            long t2 = s2 - data.get(data.size() - 1).first;

            for (int i = 0; i < data.size() - 1; i++) {
                long tt1 = s1 - data.get(i).second;
                long tt2 = s2 - data.get(i).first;

                if (t1 * tt2 > tt1 * t2) {
                    t1 = tt1;
                    t2 = tt2;
                    Collections.swap(data, i, data.size() - 1);
                }
            }
            data.remove(data.size() - 1);
            s1 = t1;
            s2 = t2;
        }

        double rate = (double) s1 / s2;

        System.out.printf("%.12f%n", rate);
    }

    private static class Pair {
        int first;
        int second;

        Pair(int second, int first) {
            this.first = first;
            this.second = second;
        }
    }
}
