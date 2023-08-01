import java.util.ArrayList;
import java.util.List;

public class CandyOnDisk {
    private int N;
    private List<Long> x, y, r;
    private double[] visit = new double[55];

    private void go(int a) {
        System.out.println(a + " " + visit[a]);
        if (visit[a] < -1e-3) return;
        for (int i = 0; i < N; i++) {
            if (x.get(i).equals(x.get(a)) || y.get(i).equals(y.get(a))) continue;
            long dxx = x.get(a) - x.get(i);
            long dyy = y.get(a) - y.get(i);
            long ddd = dxx * dxx + dyy * dyy;
            double d = Math.sqrt(ddd);
            double d2 = d - r.get(a);

            if (d2 > r.get(i)) continue;
            if (d2 > 0) {
                double d3 = r.get(i) - d2;
                if (visit[i] + 1e-3 < d3) {
                    visit[i] = d3;
                    go(i);
                }
                continue;
            }
            if (d2 > -r.get(i)) {
                double d3 = r.get(i) + d2;
                if (visit[i] + 1e-3 < d3) {
                    visit[i] = d3;
                    go(i);
                }
                continue;
            }
        }
    }

    public String ableToAchieve(List<Integer> x_, List<Integer> y_, List<Integer> r_, int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return "YES";
        N = x_.size();
        x = new ArrayList<>();
        y = new ArrayList<>();
        r = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            x.add((long) x_.get(i));
            y.add((long) y_.get(i));
            r.add((long) r_.get(i));
        }

        for (int i = 0; i < 55; i++) visit[i] = -1;

        for (int i = 0; i < N; i++) {
            long dx = x.get(i) - sx;
            long dy = y.get(i) - sy;
            long dd = dx * dx + dy * dy;
            long tt = r.get(i) * r.get(i);
            double d1 = Math.sqrt(dd);
            if (dd <= tt) { // on disk
                for (int j = 0; j < N; j++) {
                    if (x.get(i).equals(x.get(j)) || y.get(i).equals(y.get(j))) continue;
                    long dxx = x.get(i) - x.get(j);
                    long dyy = y.get(i) - y.get(j);
                    long ddd = dxx * dxx + dyy * dyy;
                    double d = Math.sqrt(ddd);
                    double d2 = d - d1 - r.get(j);
                    if (d2 > 1e-3) continue;
                    d2 = -d2;
                    if (d2 > r.get(j) + r.get(j)) continue;
                    if (d2 > r.get(j)) {
                        d2 = (double) r.get(j) + r.get(j) - d2;
                    }
                    visit[j] = d2;
                }
            }
        }

    }
}