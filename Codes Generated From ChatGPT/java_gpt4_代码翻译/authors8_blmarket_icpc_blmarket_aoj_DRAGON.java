import java.util.Scanner;

public class Main {
    static long[] boom = new long[55];

    static void xgo(int n, long s, long e) {
        if (e == 0) return;
        if (n == 0) {
            System.out.print("X");
            return;
        }

        if (boom[n - 1] > s) {
            xgo(n - 1, s, Math.min(boom[n - 1], e));
            if (boom[n - 1] >= e) return;
            s = boom[n - 1];
        }
        s -= boom[n - 1];
        e -= boom[n - 1];
        if (s == 0) {
            System.out.print("+");
            s = 1;
        }
        s--;
        e--;
        if (boom[n - 1] > s) {
            ygo(n - 1, s, Math.min(boom[n - 1], e));
            if (boom[n - 1] >= e) return;
            s = boom[n - 1];
        }
        s -= boom[n - 1];
        e -= boom[n - 1];
        if (e != 0) {
            System.out.print("F");
        }
    }

    static void ygo(int n, long s, long e) {
        if (e == 0) return;
        if (n == 0) {
            System.out.print("Y");
            return;
        }
        if (s == 0) {
            System.out.print("F");
            s++;
        }
        s--;
        e--;
        if (boom[n - 1] > s) {
            xgo(n - 1, s, Math.min(boom[n - 1], e));
            if (boom[n - 1] >= e) return;
            s = boom[n - 1];
        }
        s -= boom[n - 1];
        e -= boom[n - 1];
        if (s == 0) {
            System.out.print("-");
            s = 1;
        }
        s--;
        e--;
        ygo(n - 1, s, e);
    }

    static void go(int n, long s, long e) {
        if (e == s) {
            return;
        }
        if (s == 0) {
            System.out.print("F");
            s++;
        }
        xgo(n, s - 1, e - 1);
    }

    static void process(Scanner sc) {
        int n = sc.nextInt();
        long p = sc.nextLong();
        long l = sc.nextLong();

        p--;
        go(n, p, p + l);
        System.out.println();
    }

    static void precalc() {
        boom[0] = 1;
        for (int i = 1; i <= 50; i++) {
            boom[i] = boom[i - 1] + boom[i - 1] + 2;
        }
    }

    public static void main(String[] args) {
        precalc();
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(sc);
        }
    }
}
