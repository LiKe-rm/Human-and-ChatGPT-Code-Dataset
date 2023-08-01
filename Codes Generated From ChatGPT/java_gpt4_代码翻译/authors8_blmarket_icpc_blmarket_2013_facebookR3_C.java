import java.util.*;
import java.util.function.BiFunction;

public class Main {
    static int N, K, C;
    static int[][] R = new int[1120][1120];
    static long[] f1 = new long[1120 * 1120], f2 = new long[1120 * 1120];
    static List<Integer> values = new ArrayList<>();

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(sc);
        }
    }

    static void input(Scanner sc) {
        int x1, a1, b1, m1;
        int x2, a2, b2, m2;

        N = sc.nextInt();
        K = sc.nextInt();
        C = sc.nextInt();
        x1 = sc.nextInt();
        a1 = sc.nextInt();
        b1 = sc.nextInt();
        m1 = sc.nextInt();
        x2 = sc.nextInt();
        a2 = sc.nextInt();
        b2 = sc.nextInt();
        m2 = sc.nextInt();

        f1[0] = x1;
        f2[0] = x2;

        for (int i = 1; i < N * (N + 1); i++) {
            f1[i] = (f1[i - 1] * a1 + b1) % m1;
            f2[i] = (f2[i - 1] * a2 + b2) % m2;
        }

        values.clear();
        values.add(0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    if (i > j) R[i][j] = (int) f1[i * (i - 1) / 2 + j];
                    if (j > i) R[i][j] = (int) f2[j * (j - 1) / 2 + i];
                    values.add(R[i][j]);
                }
            }
        }
    }

    static void tarjan(int N, List<Integer> cnts, BiFunction<Integer, Integer, Boolean> chk) {
        cnts.clear();
        int[] index = new int[N];
        int[] lowlink = new int[N];
        Arrays.fill(index, -1);
        Arrays.fill(lowlink, -1);

        int idx = 0;
        List<Integer> S = new ArrayList<>();

        class DFS {
            boolean strongconnect(int a) {
                index[a] = lowlink[a] = idx++;
                S.add(a);

                boolean ret = true;
                for (int i = 0; i < N; i++) {
                    if (chk.apply(a, i)) {
                        if (index[i] == -1) {
                            if (strongconnect(i)) {
                                ret = false;
                            }
                            lowlink[a] = Math.min(lowlink[a], lowlink[i]);
                        } else {
                            boolean found = false;
                            for (int j = 0; j < S.size(); j++) {
                                if (S.get(j) == i) {
                                    lowlink[a] = Math.min(lowlink[a], index[i]);
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) ret = false;
                        }
                    }
                }

                if (index[a] == lowlink[a]) {
int cnt = 0;
while (true) {
int b = S.get(S.size() - 1);
cnt++;
S.remove(S.size() - 1);
if (b == a) break;
}
if (ret) {
cnts.add(cnt);
}
return ret;
}
return false;
}
}
    DFS dfs = new DFS();
    for (int i = 0; i < N; i++) {
        if (index[i] == -1) {
            dfs.strongconnect(i);
        }
    }
}

static boolean[] chk = new boolean[1120];

static void visit(int cut, int a, Set<Integer> res) {
    if (chk[a]) return;
    chk[a] = true;
    res.add(a);

    for (int i = 0; i < N; i++) {
        if (i != a && !chk[i]) {
            if (R[a][i] > cut) {
                visit(cut, i, res);
            }
        }
    }
}

static long sol;

static int go(int cut) {
    if (sol != -1 && cut > sol) return N + 1;
    Set<Integer>[] S = new HashSet[1120];
    for (int i = 0; i < N; i++) S[i] = new HashSet<>();

    List<Integer> cnts = new ArrayList<>();
    tarjan(N, cnts, (a, b) -> R[a][b] > cut);

    cnts.sort(Comparator.naturalOrder());
    if (cnts.size() < K) return cnts.size();

    int tsum = 0;
    long ret = cut;
    for (int i = 0; i < K; i++) {
        ret += (long) cnts.get(i) * C;
        tsum += cnts.get(i);
    }

    if (sol == -1 || sol > ret) sol = ret;

    if (tsum == K) {
        return N;
    }

    return cnts.size();
}

static void go2(int s, int e, int si, int ei) {
    if (si == ei) return;
    if (s + 1 == e) return;
    int m = (s + e) / 2;
    int mi = go(values.get(m));

    if (mi >= K) {
        go2(s, m, si, mi);
    }
    go2(m, e, mi, ei);
}

static void process(Scanner sc) {
    input(sc);
    sol = -1;

    Collections.sort(values);
    values = new ArrayList<>(new HashSet<>(values));

    int s = 0;
    int e = values.size() - 1;
    int si = go(values.get(s));
    int ei = go(values.get(e));
    go2(s, e, si, ei);
    System.out.println(sol);
}
}