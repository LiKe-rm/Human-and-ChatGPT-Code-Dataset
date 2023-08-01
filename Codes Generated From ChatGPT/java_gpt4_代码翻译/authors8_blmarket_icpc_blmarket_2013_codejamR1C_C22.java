import java.util.*;

public class WallAttack {
    static class Atk {
        int d, w, e, s;

        Atk(int d, int w, int e, int s) {
            this.d = d;
            this.w = w;
            this.e = e;
            this.s = s;
        }
    }

    static List<Atk> V = new ArrayList<>();
    static List<Integer> pts = new ArrayList<>();
    static int maxsz;
    static boolean[] leaf = new boolean[5000000];
    static int[] walls = new int[5000000];

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
        leaf[1] = true;
        walls[1] = 0;

        int ret = 0;
        int j = 0;
        for (int i = 0; i < V.size(); i++) {
            while (j < V.size() && V.get(j).d < V.get(i).d) {
                addWall(j++);
            }
            if (!blockWall(i)) {
                ret++;
            }
        }
        System.out.println(ret);
    }

    private static int getPts(int a) {
        return Collections.binarySearch(pts, a);
    }

    private static void addOne(int pos, int a, int b, int l, int r, int s) {
        if (l < a) l = a;
        if (r > b) r = b;

        if (l >= b || r <= a) return;

        if (leaf[pos] && l == a && r == b) {
            walls[pos] = Math.max(walls[pos], s);
            return;
        }

        if (leaf[pos]) {
            leaf[pos] = false;
            leaf[pos * 2] = leaf[pos * 2 + 1] = true;
            walls[pos * 2] = walls[pos * 2 + 1] = walls[pos];
        }
        int mid = (a + b) / 2;
        addOne(pos * 2, a, mid, l, r, s);
        addOne(pos * 2 + 1, mid, b, l, r, s);

        if (leaf[pos * 2] && leaf[pos * 2 + 1] && walls[pos * 2] == walls[pos * 2 + 1]) {
            leaf[pos] = true;
            walls[pos] = walls[pos * 2];
        }
    }

    private static int getOne(int pos, int a, int b, int l, int r) {
        if (l < a) l = a;
        if (r > b) r = b;

        if (l >= b || r <= a) return -1;
        if (leaf[pos]) return walls[pos];

        int mid = (a + b) / 2;
        int t1 = getOne(pos * 2, a, mid, l, r);
        int t2 = getOne(pos * 2 + 1, mid, b, l, r);
        if (t1 == -1 || t2 == -1) return t1 + t2 + 1;
        return Math.min(t1, t2);
    }

    private static int getMin(int l, int r) {
        return getOne(1, 0, maxsz, l, r);
    }

    private static void addWall(int a) {
        int l, r, s;
        l = getPts(V.get(a).w);
        r = getPts(V.get(a).e);
        s = V.get(a).s;

        addOne(1, 0, maxsz, l, r, s);
    }

    private static boolean blockWall(int a) {
        int l, r, s;
        l = getPts(V.get(a).w);
        r = getPts(V.get(a).e);
        s = V.get(a).s;

        return getMin(l, r) >= s;
    }
}

