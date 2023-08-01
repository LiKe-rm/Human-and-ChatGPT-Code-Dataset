import java.util.Scanner;

public class Main {
    static int n, l;
    static int[][] sums = new int[1005][1005];

    static void process(Scanner sc) {
        double minimalist = 999;

        n = sc.nextInt();
        l = sc.nextInt();
        for (int i = 0; i < n; i++) {
            sums[i][i + 1] = sc.nextInt();
        }

        for (int i = 2; i <= n; i++) {
            int minsum = 9990000;
            for (int j = 0; j + i <= n; j++) {
                sums[j][j + i] = sums[j][j + i - 1] + sums[j + i - 1][j + i];
                if (minsum > sums[j][j + i]) minsum = sums[j][j + i];
            }
            if (i >= l) {
                double tmp = (double) minsum / i;
                if (tmp < minimalist) minimalist = tmp;
            }
        }

        System.out.printf("%.12f%n", minimalist);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(sc);
        }
    }
}
