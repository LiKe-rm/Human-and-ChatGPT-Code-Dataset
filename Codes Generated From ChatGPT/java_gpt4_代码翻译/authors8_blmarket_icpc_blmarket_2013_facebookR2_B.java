import java.util.Scanner;

public class Main {
    static long N, K, P;

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
        N = sc.nextLong();
        K = sc.nextLong();
        P = sc.nextLong();

        if (K >= N) {
            System.out.println(1);
            return;
        }

        long tmp = ((N - 1) % K) + 1;
        long round = (N + K - 1) / K;
        long votes = 0;
        long winRound = round;

        if (P == 100) {
            System.out.println(winRound);
            return;
        }

        while (true) {
            long go = P * tmp - 100 * votes;
            long go2 = (100 - P) * K;

            go /= go2;
            round -= go;
            tmp += go * K;
            votes += go * K;
            if (round < 1) break;

            if (votes * 100 >= tmp * P) {
                winRound = round;
                votes = 0;
                continue;
            }

            round--;
            tmp += K;
            votes += K;
            if (round < 1) break;

            if (votes * 100 >= tmp * P) {
                winRound = round;
                votes = 0;
            }
        }
        System.out.println(winRound);
    }
}
