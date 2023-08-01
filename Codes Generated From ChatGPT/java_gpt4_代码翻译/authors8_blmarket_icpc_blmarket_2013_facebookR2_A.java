import java.util.Scanner;

public class Main {
    static int N;
    static int[] A = new int[105];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(sc);
        }
        sc.close();
    }

    static void process(Scanner sc) {
        long ret = 1;
        int prevLine = 0;
        N = sc.nextInt();

        for (int i = 0; i < N; i++) {
            int tmp = sc.nextInt();
            A[i] = tmp;
            ret++;

            for (int j = 0; j <= tmp; j++) {
                ret += prevLine;
                if (j > 0) {
                    prevLine++;
                }
            }
            prevLine++;
        }
        System.out.println(ret);
    }
}
