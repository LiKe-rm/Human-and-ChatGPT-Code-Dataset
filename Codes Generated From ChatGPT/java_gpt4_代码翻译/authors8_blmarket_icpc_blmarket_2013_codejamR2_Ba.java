import java.util.Scanner;

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
        int n = scanner.nextInt();
        long p = scanner.nextLong();
        long nn = 1L << n;

        if (p == nn) {
            System.out.println((nn - 1) + " " + (nn - 1));
            return;
        }

        long s = 0, e = nn;
        while (s < e) {
            long m = (s + e) / 2;
            if (getWorst(nn, m) >= p) {
                e = m;
            } else {
                s = m + 1;
            }
        }

        System.out.print((e - 1) + " ");

        s = 0;
        e = nn;

        while (s < e) {
            long m = (s + e) / 2;
            if (getBest(nn, m) >= p) {
                e = m;
            } else {
                s = m + 1;
            }
        }
        System.out.println(e - 1);
    }

    private static long getWorst(long nn, long a) {
        if (a == 0) return 0;
        if ((a & 1) != 0) {
            return (nn / 2) + getWorst(nn / 2, a / 2);
        } else {
            return (nn / 2) + getWorst(nn / 2, (a - 1) / 2);
        }
    }

    private static long getBest(long nn, long a) {
        if (a == nn - 1) return nn - 1;

        if ((a & 1) != 0) {
            return getBest(nn / 2, (a + 1) / 2);
        } else {
            return getBest(nn / 2, a / 2);
        }
    }
}
