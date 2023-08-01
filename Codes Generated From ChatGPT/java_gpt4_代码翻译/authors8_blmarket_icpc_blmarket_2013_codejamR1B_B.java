import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

public class ProblemSolver {

    private static int N, X, Y;
    private static int[][] combi = new int[505][505];

    public static void main(String[] args) {
        precalc();
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void precalc() {
        for (int[] row : combi) {
            Arrays.fill(row, 0);
        }
        for (int i = 1; i <= 500; i++) {
            combi[i][0] = combi[i][i] = 1;
            for (int j = 1; j < i; j++) {
                combi[i][j] = combi[i - 1][j - 1] + combi[i - 1][j];
            }
        }
    }

    private static void process(Scanner scanner) {
        N = scanner.nextInt();
        X = scanner.nextInt();
        Y = scanner.nextInt();

        int layer = (Math.abs(X) + Math.abs(Y)) / 2;
        if (layer == 0) {
            System.out.println("1.0");
            return;
        }
        layer--;
        int minRange = (2 * layer + 1) * (layer + 1);
        layer++;
        int maxRange = (2 * layer + 1) * (layer + 1);

        if (N <= minRange) {
            System.out.println("0.0");
            return;
        }
        if (N >= maxRange) {
            System.out.println("1.0");
            return;
        }

        if (X == 0) {
            System.out.println("0.0");
            return;
        }

        int given = N - minRange;

        Vector<Double> cur = new Vector<>(2);
        cur.add(0.5);
        cur.add(0.5);

        for (int i = 2; i <= given; i++) {
            Vector<Double> nex = new Vector<>(i + 1);
            nex.setSize(i + 1);

            for (int j = 0; j < i; j++) {
                int right = i - 1 - j;
                if (j > layer * 2 || right > layer * 2) {
                    continue;
                }
                if (j == layer * 2) {
                    nex.set(j, nex.get(j) + cur.get(j));
                    continue;
                }
                if (right == layer * 2) {
                    nex.set(j + 1, nex.get(j + 1) + cur.get(j));
                    continue;
                }
                nex.set(j, nex.get(j) + cur.get(j) * 0.5);
                nex.set(j + 1, nex.get(j + 1) + cur.get(j) * 0.5);
            }
            cur = nex;
        }

        double ret = 0;
        for (int i = Y + 1; i < cur.size(); i++) {
            ret += cur.get(i);
        }

        System.out.printf("%.12f%n", ret);
    }
}
