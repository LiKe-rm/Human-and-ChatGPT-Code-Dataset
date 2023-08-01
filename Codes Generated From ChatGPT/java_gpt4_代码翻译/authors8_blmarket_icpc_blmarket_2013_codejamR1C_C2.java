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

    static List<Atk> V = new ArrayList<>();
    static List<Integer> pts = new ArrayList<>();
    static int maxsz = 1;
    static Pair<Boolean, Integer>[] arr = new Pair[5000000];

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
        V.clear();
        pts.clear();
        int N = scanner.nextInt();
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
                pts.add(w);
                pts.add(e);

                d += dd;
                w += dm;
                e += dm;
                s += ds;
            }
        }
        V.sort(Comparator.comparingInt(a -> a.d));
        pts.sort(Integer::compareTo);
        pts = new ArrayList<>(new HashSet<>(pts));

        maxsz = 1;
        while (maxsz <= pts.size()) maxsz *= 2;
        arr[1] = new Pair<>(true, 0);

        int ret = 0;
        int j = 0;
        for (int i = 0; i < V.size(); i++) {
            if (V.get(i).d > V.get(j).d) {
                insertWall(j++);
            }
            if (!checkWall(i)) {
                ret++;
            }
        }
        System.out.println(ret);
    }

    // Implement the missing methods: setMax, put, check, insertWall, and checkWall.
}
