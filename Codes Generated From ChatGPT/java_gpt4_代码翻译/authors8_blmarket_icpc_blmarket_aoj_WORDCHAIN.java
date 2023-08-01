import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(sc);
            solve(i);
        }
    }

    static List<String>[][] links = new ArrayList[30][30];
    static LinkedList<Pair> output = new LinkedList<>();

    private static int walk2(ListIterator<Pair> it, int s, int t) {
        if (s == t) return 0;
        for (int i = 0; i < 30; i++) {
            if (links[s][i].size() > 0) {
                output.add(it.nextIndex(), new Pair(links[s][i].remove(links[s][i].size() - 1), s));
                return walk2(it, i, t);
            }
        }
        return -1;
    }

    private static int pump(ListIterator<Pair> it) {
        int pos = it.next().second;
        it.previous();
        while (true) {
            for (int i = 0; i < 30; i++) {
                if (links[pos][i].size() > 0) {
                    output.add(it.nextIndex(), new Pair(links[pos][i].remove(links[pos][i].size() - 1), pos));
                    if (walk2(it, i, pos) == -1) return -1;
                } else {
                    return 0;
                }
            }
        }
    }

    private static void solve(int dataId) {
        int s = -1, t = -1, use = -1;
        for (int i = 0; i < 26; i++) {
            int outd = 0, ind = 0;
            for (int j = 0; j < 26; j++) {
                outd += links[i][j].size();
                ind += links[j][i].size();
            }
            if (outd != 0 || ind != 0) use = i;
            if (outd > ind + 1 || ind > outd + 1) {
                System.out.println("IMPOSSIBLE");
                return;
            }
            if (outd > ind) {
                if (s != -1) {
                    System.out.println("IMPOSSIBLE");
                    return;
                }
                s = i;
            }
            if (ind > outd) {
                if (t != -1) {
                    System.out.println("IMPOSSIBLE");
                    return;
                }
                t = i;
            }
        }
        if (s == -1) s = t = use;

        if (walk2(output.listIterator(output.size()), s, t) == -1) {
            System.out.println("IMPOSSIBLE");
            return;
        }
        output.addLast(new Pair("", t));
        ListIterator<Pair> it = output.listIterator();
        while (it.hasNext()) {
            if (pump(it) == -1) {
                System.out.println("IMPOSSIBLE");
                return;
            }
        }

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                if (links[i][j].size() > 0) {
                    System.out.println("IMPOSSIBLE");
                    return;
                }
            }
        }

        output.removeLast();
        it = output.listIterator();
        while (it.hasNext()) {
            System.out.print(it.next().first);
            if (it.hasNext())
                System.out.print(" ");
            }
        }
        System.out.println();
    

    private static void process(Scanner sc) {
        int n = sc.nextInt();
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                links[i][j] = new ArrayList<>();
            }
        }
        output.clear();
        for (int i = 0; i < n; i++) {
            String tmp = sc.next();
            int c1 = tmp.charAt(0) - 'a';
            int c2 = tmp.charAt(tmp.length() - 1) - 'a';
            links[c1][c2].add(tmp);
        }
    }

    static class Pair {
        String first;
        int second;

        public Pair(String first, int second) {
            this.first = first;
            this.second = second;
        }
    }
}
