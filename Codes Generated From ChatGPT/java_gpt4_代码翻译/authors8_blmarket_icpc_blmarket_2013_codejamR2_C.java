import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.function.BiConsumer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
            System.err.println(i);
        }
    }

    private static void process(Scanner scanner) {
        int N = scanner.nextInt();
        List<Pair> V = new ArrayList<>(N);
        for (int i = 0; i < N; i++) {
            V.add(new Pair(scanner.nextInt(), 0));
        }
        for (int i = 0; i < N; i++) {
            V.get(i).setSecond(scanner.nextInt());
        }

        List<Integer> ret = go(V);
        for (Integer value : ret) {
            System.out.print(value + " ");
        }
        System.out.println();
    }

    private static List<Integer> go(List<Pair> V) {
        int n = V.size();
        List<Integer> ret = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            ret.add(-1);
        }

        int cnt = 0;
        while (cnt < n) {
            for (int i = 0; i < n; i++) {
                if (V.get(i).getFirst() == 1 && V.get(i).getSecond() == 1) {
                    ret.set(i, ++cnt);
                    V.get(i).setFirst(-1);
                    V.get(i).setSecond(-1);

                    BiConsumer<Integer, Integer, Integer> setSecond = (s, e, tgt) -> {
                        for (int j = s; j < e; j++) {
                            if (ret.get(j) == -1) {
                                if (V.get(j).getSecond() == tgt) {
                                    V.get(j).setSecond(V.get(j).getSecond() - 1);
                                    setSecond.accept(s, j, tgt + 1);
                                    s = j;
                                }
                            }
                        }
                    };

                    BiConsumer<Integer, Integer, Integer> setFirst = (s, e, tgt) -> {
                        for (int j = e - 1; j > s; j--) {
                            if (ret.get(j) == -1) {
                                if (V.get(j).getFirst() == tgt) {
                                    V.get(j).setFirst(V.get(j).getFirst() - 1);
                                    setFirst.accept(j, e, tgt + 1);
                                    e = j;
                                }
                            }
                        }
                    };

                    setSecond.accept(0, i, 2);
                    setFirst.accept(i, n, 2);
                    break;
                }
            }
        }
        return ret;
    }

    private static class Pair {
        private int first;
        private int second;

        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        int getFirst() {
            return first;
        }

        void setFirst(int first) {
            this.first = first;
        }

        int getSecond() {
            return second;
        }

        void setSecond(int second) {
            this.second = second;
        }
    }
}
