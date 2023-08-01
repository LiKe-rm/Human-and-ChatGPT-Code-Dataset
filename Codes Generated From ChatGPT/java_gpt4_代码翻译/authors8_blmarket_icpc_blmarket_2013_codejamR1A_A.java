import java.util.Scanner;

public class PaintRings {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        long r = scanner.nextLong();
        long t = scanner.nextLong();

        long X = r * 2 + 1;

        long s = 0;
        long e = 707106790;

        while (s + 1 < e) {
            long m = (s + e + 1) / 2;
            long tmp = m * (m - 1) * 2;
            long tmp2 = t - tmp;

            if (tmp2 < 0 || tmp2 / X < m) {
                e = m;
            } else {
                s = m;
            }
        }

        System.out.println(s);
    }
}
