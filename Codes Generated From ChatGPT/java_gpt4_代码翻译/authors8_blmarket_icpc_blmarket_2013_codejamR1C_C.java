import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class WallAttack {

    static class Atk {
        int d;
        int w, e;
        int s;

        public Atk(int d, int w, int e, int s) {
            this.d = d;
            this.w = w;
            this.e = e;
            this.s = s;
        }
    }

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
        int N = scanner.nextInt();
        List<Atk> V = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            int d = scanner.nextInt();
            int n = scanner.nextInt();
            int w = scanner.nextInt();
            int e = scanner.nextInt();
            int s = scanner.nextInt();
            int dd = scanner.nextInt();
            int dm = scanner.nextInt();
            int ds = scanner.nextInt();

            for (int j = 0; j < n; j++) {
                Atk tmp = new Atk(d, w, e, s);
                V.add(tmp);
                d += dd;
                w += dm;
                e += dm;
                s += ds;
            }
        }
        V.sort(Comparator.comparingInt(a -> a.d));

        int ret = 0;
        for (int i = 0; i < V.size(); i++) {
            boolean failed = false;
            for (int j = V.get(i).w; j < V.get(i).e; j++) {
                boolean blocked = false;
                for (int k = 0; k < i; k++) {
                    if (V.get(k).d < V.get(i).d) {
                        if (V.get(k).w <= j && j < V.get(k).e && V.get(k).s >= V.get(i).s) {
                            blocked = true;
                            break;
                        }
                    }
                }
                if (!blocked) {
                    failed = true;
                    break;
                }
            }
            if (failed) {
                ret++;
            }
        }
        System.out.println(ret);
    }
}
