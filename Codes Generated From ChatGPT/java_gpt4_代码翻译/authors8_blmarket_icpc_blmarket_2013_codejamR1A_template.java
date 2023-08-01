import java.util.Scanner;

public class LCMCalculator {

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
        int r = scanner.nextInt();
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int k = scanner.nextInt();

        int[] kk = new int[k];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < k; j++) {
                kk[j] = scanner.nextInt();
            }
            go(k, kk);
        }
    }

    private static void go(int k, int[] kk) {
        int lcm = 1;
        for (int i = 0; i < k; i++) {
            lcm = lcm * kk[i] / gcd(lcm, kk[i]);
        }
        System.out.println(lcm);
    }

    private static int gcd(int a, int b) {
        if (b == 0) {
            return a;
        } else {
            return gcd(b, a % b);
        }
    }
}
