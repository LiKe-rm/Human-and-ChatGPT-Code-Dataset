import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.function.Consumer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            process(scanner);
        }
    }

    private static void process(Scanner scanner) {
        int n = scanner.nextInt();
        int q = scanner.nextInt();
        List<List<Integer>> childs = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            childs.add(new ArrayList<>());
        }

        for (int i = 0; i < n - 2; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            childs.get(a).add(b);
        }
        childs.get(1).add(2);

        int[] idx = new int[50005];
        int[] last = new int[50005];
        boolean[] colors = new boolean[65536 * 2];
        boolean[] finalState = new boolean[65536 * 2];

        Consumer<Integer> buildPrefix = (x) -> {
            int[] tmp = {0};
            Consumer<Integer> go = new Consumer<Integer>() {
                @Override
                public void accept(Integer pos) {
                    idx[pos] = tmp[0]++;
                    for (int c : childs.get(pos)) {
                        this.accept(c);
                    }
                    last[pos] = tmp[0];
                }
            };
            go.accept(1);
        };
        buildPrefix.accept(0);

        finalState[1] = true;

        Consumer<Integer> xoxo = (Integer pos) -> {
            int a = idx[pos], b = last[pos];
            Consumer<int[]> go = new Consumer<int[]>() {
                @Override
                public void accept(int[] params) {
                    int pos = params[0], left = params[1], right = params[2];
                    if (right <= a || left >= b) return;
                    if (finalState[pos] && left >= a && right <= b) {
                        colors[pos] = !colors[pos];
                        return;
                    }

                    if (finalState[pos]) {
                        finalState[pos * 2] = finalState[pos * 2 + 1] = true;
                        colors[pos * 2] = colors[pos * 2 + 1] = colors[pos];
                        finalState[pos] = false;
                    }

                    this.accept(new int[]{pos * 2, left, (left + right) / 2});
                    this.accept(new int[]{pos * 2 + 1, (left + right) / 2, right});

                    if (finalState[pos * 2] && finalState[pos * 2 + 1] && colors[pos * 2] == colors[pos * 2 + 1]) {
                        finalState[pos] = true;
                        colors[pos] = colors[pos * 2];
                    }
                }
            };
            go.accept(new int[]{1, 0, 65536});
        };
        xoxo.accept(2);

        for (int i = 0; i < q; i++) {
            char cmd = scanner.next().charAt(0);
            int a = scanner.nextInt();
            if (cmd == 'T') {
                xoxo.accept(a);
            } else {
                int b = scanner.nextInt();
                System.out.println(get(idx[a], colors, finalState) == get(idx[b], colors, finalState) ? "Ally" : "Enemy");
            }
        }
    }

    private static int get(int hehe, boolean[] colors, boolean[] finalState) {
        return go(1, 0, 65536, hehe, colors, finalState);
    }

    private static int go(int pos, int left, int right, int hehe, boolean[] colors, boolean[] finalState) {
        if (finalState[pos]) {
            return colors[pos] ? 1 : 0;
        }
        if (hehe < (left + right) / 2) {
            return go(pos * 2, left, (left + right) / 2, hehe, colors, finalState);
        }
        return go(pos * 2 + 1, (left + right) / 2, right, hehe, colors, finalState);
    }
}

