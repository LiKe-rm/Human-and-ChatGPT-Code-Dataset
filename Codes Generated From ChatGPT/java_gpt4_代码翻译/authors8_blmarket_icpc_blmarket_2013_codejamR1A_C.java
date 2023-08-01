import java.util.Scanner;

public class NumberGuessing {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d:%n", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        int r = scanner.nextInt();
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int k = scanner.nextInt();

        int[] kk = new int[k];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < k; j++) {
                kk[j] = scanner.nextInt();
            }
            go(n, m, k, kk);
        }
    }

    private static void go(int n, int m, int k, int[] kk) {
        int lcm = 1;
        for (int i = 0; i < k; i++) {
            lcm = lcm * kk[i] / gcd(lcm, kk[i]);
        }

        StringBuilder sol = new StringBuilder();

        int life = n;
        while (lcm % 7 == 0) {
            lcm /= 7;
            sol.append("7");
            life--;
        }
        while (lcm % 5 == 0) {
            lcm /= 5;
            sol.append("5");
            life--;
        }
        while (lcm % 3 == 0) {
            lcm /= 3;
            sol.append("3");
            life--;
        }
        if (life == 1) {
            System.out.println(sol.toString() + lcm);
            return;
        }

        System.out.print(sol.toString());
        int p2 = 0;
        while (lcm % 2 == 0) {
            p2++;
            lcm /= 2;
        }

        guess(life, p2);
        System.out.println();
    }

    private static void guess(int life, int p2) {
        if (life == 0) return;
        if (p2 == life * 2) {
            System.out.print("4");
            guess(life - 1, p2 - 2);
            return;
        }
        System.out.print("2");
        guess(life - 1, p2 - 1);
    }

    private static int gcd(int a, int b) {
        if (b == 0) {
            return a;
        } else {
            return gcd(b, a % b);
        }
    }
}
