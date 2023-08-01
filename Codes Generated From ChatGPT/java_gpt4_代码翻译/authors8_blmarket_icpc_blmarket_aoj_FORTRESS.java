import java.util.*;

public class Main {
    private static int n;
    private static int[] x = new int[105];
    private static int[] y = new int[105];
    private static int[] r = new int[105];
    private static int[][] way = new int[105][105];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(i, sc);
        }
    }

    public static void process(int dataId, Scanner sc) {
        n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
            r[i] = sc.nextInt();
        }

        for (int i = 0; i < n; i++) {
            Arrays.fill(way[i], 0);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (r[i] > r[j]) {
                    int xd = x[i] - x[j];
                    int yd = y[i] - y[j];
                    if (xd * xd + yd * yd < r[i] * r[i]) {
                        way[i][j] = 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (way[i][j] == 1) {
                    for (int k = 0; k < n; k++) {
                        if (way[i][k] == 1 && way[k][j] == 1) {
                            way[i][j] = 0;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (way[j][i] == 1) {
                    way[i][j] = 1;
                }
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (way[i][k] == 1) {
                    for (int j = 0; j < n; j++) {
                        if (way[k][j] == 1) {
                            if (way[i][j] == 0 || way[i][j] > way[i][k] + way[k][j]) {
                                way[i][j] = way[i][k] + way[k][j];
                            }
                        }
                    }
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    ret = Math.max(ret, way[i][j]);
                }
            }
        }

        System.out.println(ret);
    }
}
