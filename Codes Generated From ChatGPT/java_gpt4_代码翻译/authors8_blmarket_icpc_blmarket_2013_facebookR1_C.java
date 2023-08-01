import java.util.*;
import java.awt.Point;

public class Main {
    static int W, H, P, Q, N, X, Y, A, B, C, D;
    static List<Point> data = new ArrayList<>();

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(sc, i);
        }
    }

    static void process(Scanner sc, int ID) {
        data.clear();
        W = sc.nextInt();
        H = sc.nextInt();
        P = sc.nextInt();
        Q = sc.nextInt();
        N = sc.nextInt();
        X = sc.nextInt();
        Y = sc.nextInt();
        A = sc.nextInt();
        B = sc.nextInt();
        C = sc.nextInt();
        D = sc.nextInt();

        data.add(new Point(X, Y));
        for (int i = 1; i < N; i++) {
            int x = data.get(i - 1).x;
            int y = data.get(i - 1).y;
            int xx = (x * A + y * B + 1) % W;
            int yy = (x * C + y * D + 1) % H;
            data.add(new Point(xx, yy));
        }

        data.sort(Comparator.comparingInt(p -> p.x));
        data = new ArrayList<>(new HashSet<>(data));

        long ret = 0;
        TreeMap<Integer, Integer> M = new TreeMap<>();
        M.put(H, 1);

        int j = 0, jj = 0;
        for (int i = 0; i <= W - P; i++) {
            while (j < data.size() && data.get(j).x < i + P) {
                M.put(data.get(j).y, M.getOrDefault(data.get(j).y, 0) + 1);
                j++;
            }
            while (jj < data.size() && data.get(jj).x < i) {
                M.put(data.get(jj).y, M.get(data.get(jj).y) - 1);
                jj++;
            }

            int prev = -1;
            for (Iterator<Map.Entry<Integer, Integer>> it = M.entrySet().iterator(); it.hasNext(); ) {
                Map.Entry<Integer, Integer> entry = it.next();
                if (entry.getValue() == 0) {
                    it.remove();
                    continue;
                }
                int range = entry.getKey() - (prev + 1);
                prev = entry.getKey();
                if (range < Q) continue;
                ret += range - Q + 1;
            }
        }
        System.out.println(ret);
    }
}
