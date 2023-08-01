import java.util.Scanner;

public class Main {
    private static int x1, y1, x2, y2, n;
    private static int[][] data = new int[105][2];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int testCases = scanner.nextInt();

        for (int i = 1; i <= testCases; i++) {
            process(scanner);
        }
    }

    private static void process(Scanner scanner) {
        x1 = scanner.nextInt();
        y1 = scanner.nextInt();
        x2 = scanner.nextInt();
        y2 = scanner.nextInt();
        n = scanner.nextInt();

        double ret = 0;
        y2 -= y1;

        for (int i = 0; i < n; i++) {
            data[i][0] = scanner.nextInt();
            data[i][1] = scanner.nextInt() - y1;
        }
        data[n][0] = data[0][0];
        data[n][1] = data[0][1];
        y1 = 0;

        int px = data[0][0];
        int py = data[0][1];
        int x, y;

        for (int i = 1; i <= n; i++) {
            x = data[i][0];
            y = data[i][1];

            if (px == x) {
                px = x;
                py = y;
                continue;
            }

            double t1 = getr(x, px, x1), t2 = getr(x, px, x2);
            if (t1 > t2) {
                double temp = t1;
                t1 = t2;
                t2 = temp;
            }
            if (t1 >= 1) {
                px = x;
                py = y;
                continue;
            }
            if (t2 <= 0) {
                px = x;
                py = y;
                continue;
            }

            if (t1 < 0) t1 = 0;
            if (t2 > 1) t2 = 1;
            if (t1 > t2) {
                px = x;
                py = y;
                continue;
            }

            double xx1 = rr(x, px, t1);
            double yy1 = rr(y, py, t1);
            double xx2 = rr(x, px, t2);
            double yy2 = rr(y, py, t2);
            double dxx = xx2 - xx1;

            if (py != y) {
                double tt1 = getr(yy2, yy1, y1), tt2 = getr(yy2, yy1, y2);

                if (tt1 > tt2) {
                    double temp = tt1;
                    tt1 = tt2;
                    tt2 = temp;
                }
                if (tt1 < 0) tt1 = 0;
                if (tt1 > 1) tt1 = 1;
                if (tt2 < 0) tt2 = 0;
                if (tt2 > 1) tt2 = 1;

                double ty1 = rr(yy2, yy1, tt1);

                if (yy1 >= y1) {
                    ret += (Math.min(ty1, (double) y2) + Math.min(yy1, (double) y2)) * dxx * tt1;
                }

                double ty2 = rr(yy2, yy1, tt2);
                ret += (Math.min(ty1, (double) y2) + Math.min(ty2, (double) y2)) * dxx * (tt2 - tt1);
                            if (yy2 >= y1) {
                ret += (Math.min(ty2, (double) y2) + Math.min(yy2, (double) y2)) * dxx * (1 - tt2);
            }
        } else {
            if (py <= y1) {
                px = x;
                py = y;
                continue;
            }
            ret += (double) ((Math.min(y2, py) - y1) * 2) * (x - px) * (t2 - t1);
        }

        px = x;
        py = y;
    }

    if (ret < 0) ret = -ret;
    System.out.printf("%.12f%n", ret / 2);
}

private static double getr(double x, double px, double tx) {
    double a = x - px;
    double b = tx - px;
    return b / a;
}

private static double rr(double x, double px, double r) {
    return r * x + (1.0 - r) * px;
}
}
