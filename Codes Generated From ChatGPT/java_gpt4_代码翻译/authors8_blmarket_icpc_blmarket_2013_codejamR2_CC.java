import java.util.Arrays;
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
        int N = scanner.nextInt();
        int[] A = new int[2004];
        int[] B = new int[2004];
        int[][] flow = new int[2004][2004];
        int[] ret = new int[2004];

        for (int i = 0; i < N; i++) {
            A[i] = scanner.nextInt();
        }
        for (int i = 0; i < N; i++) {
            B[i] = scanner.nextInt();
        }

        for (int[] row : flow) {
            Arrays.fill(row, 0);
        }
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (A[i] >= A[j]) {
                    flow[j][i] = 1;
                }
                if (B[j] >= B[i]) {
                    flow[i][j] = 1;
                }
            }
        }

        for (int i = N - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (A[i] == A[j] + 1) {
                    flow[j][i] = 1;
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (B[i] == B[j] + 1) {
                    flow[j][i] = 1;
                    break;
                }
            }
        }

        boolean[] used = new boolean[2004];
        Arrays.fill(ret, 0);
        for (int pp = 1; pp <= N; pp++) {
            for (int i = 0; i < N; i++) {
                if (!used[i]) {
                    boolean fail = false;
                    for (int j = 0; j < N; j++) {
                        if (!used[j] && flow[j][i] != 0) {
                            fail = true;
                            break;
                        }
                    }
                    if (!fail) {
                        used[i] = true;
                        ret[i] = pp;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < N; i++) {
            System.out.print(ret[i] + " ");
        }
        System.out.println();
    }
}
