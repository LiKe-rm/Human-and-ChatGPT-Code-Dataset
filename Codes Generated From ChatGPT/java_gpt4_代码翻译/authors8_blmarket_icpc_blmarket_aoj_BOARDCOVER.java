import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    static int n, m;

    static int mmm(String str) {
        int ret = 0;
        for (int i = 0; i < str.length(); i++) {
            ret <<= 1;
            if (str.charAt(i) == '#')
                ret |= 1;
        }
        return ret;
    }

    static boolean chk(int mask, int pos) {
        if (pos < 0 || pos >= m) return true;
        return (mask & (1 << pos)) != 0;
    }

    static void set(int[] mask, int pos) {
        mask[0] ^= (1 << pos);
    }

    static void iterate(int pos, int mask, int cnt, int[] nmask, Map<Integer, Integer> ret) {
        if (pos == m) {
            ret.put(nmask[0], ret.getOrDefault(nmask[0], 0) + cnt);
            return;
        }
        if (chk(mask, pos)) return;
        iterate(pos + 1, mask, cnt, nmask, ret);
        if (!chk(nmask[0], pos)) {
            set(nmask, pos);
            iterate(pos + 1, mask, cnt, nmask, ret);
            set(nmask, pos);
        }
    }

    static void process(Scanner sc) {
        n = sc.nextInt();
        m = sc.nextInt();
        String str = sc.next();
        int mask = mmm(str);

        Map<Integer, Integer>[] step = new HashMap[2];
        step[0] = new HashMap<>();
        step[1] = new HashMap<>();
        step[1].put(mask, 1);

        for (int i = 1; i < n; i++) {
            Map<Integer, Integer> cur = step[i % 2];
            Map<Integer, Integer> next = step[(i + 1) % 2];
            next.clear();

            str = sc.next();
            int nmask = mmm(str);

            for (Map.Entry<Integer, Integer> entry : cur.entrySet()) {
                iterate(0, entry.getKey(), entry.getValue(), new int[]{nmask}, next);
            }
        }

        System.out.println(step[n % 2].getOrDefault((1 << m) - 1, 0));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(sc);
        }
    }
}
