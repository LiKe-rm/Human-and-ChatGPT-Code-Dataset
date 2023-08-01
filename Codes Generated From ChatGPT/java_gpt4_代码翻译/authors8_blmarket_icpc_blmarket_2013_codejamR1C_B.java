import java.util.Scanner;

public class CoordinateMove {

    private static final int[] dx = {-1, 0, 1, 0};
    private static final int[] dy = {0, -1, 0, 1};
    private static final char[] dd = {'E', 'N', 'W', 'S'};

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
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        for (int i = 1; ; i++) {
            if (move(i, x, y) != -1) {
                System.out.println();
                return;
            }
        }
    }

    private static int move(int a, int x, int y) {
        int tt = Math.abs(x) + Math.abs(y);
        int maxx = a * (a + 1) / 2;

        if ((tt & 1) != (maxx & 1) || maxx < tt) return -1;
        if (a == 0) return 0;

        for (int i = 0; i < 4; i++) {
            int nx = x + a * dx[i];
            int ny = y + a * dy[i];

            if (move(a - 1, nx, ny) != -1) {
                System.out.print(dd[i]);
                return i;
            }
        }
        return -1;
    }
}
