import java.util.*;

public class AkariDaisukiDiv1 {
    private static final int mod = 1000000007;

    private int pow2(int a) {
        long ret = 1;
        long tt = 2;
        while (a > 0) {
            if ((a & 1) == 1) {
                ret = (ret * tt) % mod;
            }
            tt = (tt * tt) % mod;
            a /= 2;
        }
        return (int) ret;
    }

    private String build(String x, String Waai, String Akari, String Daisuki) {
        return Waai + x + Akari + x + Daisuki;
    }

    private int cnt(String x, String F) {
        int nn = x.length() - F.length() + 1;
        int ret = 0;
        for (int i = 0; i < nn; i++) {
            if (x.substring(i, i + F.length()).equals(F)) {
                ret++;
            }
        }
        return ret;
    }

    public int countF(String Waai, String Akari, String Daisuki, String S, String F, int k) {
        String c = S;
        while (c.length() < 1000 && k > 0) {
            c = build(c, Waai, Akari, Daisuki);
            k--;
        }

        if (k == 0) {
            return cnt(c, F);
        }

        String bs = c.substring(0, Math.min(50, c.length()));
        String es = c.substring(Math.max(0, c.length() - 50));
        long cc = cnt(c, F);

        int tmp;
        for (int i = 0; i < 55; i++) {
            cc = (cc * 2) % mod;

            String bbs = Waai + bs.substring(0, Math.min(F.length() - 1, bs.length()));
            String mid = es.substring(Math.max(0, es.length() - F.length() + 1)) + Akari + bs.substring(0, Math.min(F.length() - 1, bs.length()));
            String ees = es.substring(Math.max(0, es.length() - F.length() + 1)) + Daisuki;
            tmp = cnt(bbs, F) + cnt(mid, F) + cnt(ees, F);
            cc += tmp;
            cc %= mod;

            k--;
            if (k == 0) {
                return (int) cc;
            }

            bs = Waai + bs;
            bs = bs.substring(0, Math.min(50, bs.length()));
            es = es + Daisuki;
            es = es.substring(Math.max(0, es.length() - 50));
        }

        int p2 = pow2(k);
        cc += tmp;
        cc = (cc * p2) % mod;
        cc -= tmp;
        if (cc < 0) {
            cc += mod;
        }
        return (int) cc;
    }

    public static void main(String[] args) {
        AkariDaisukiDiv1 solver = new AkariDaisukiDiv1();
        String Waai = "a";
        String Akari = "b";
        String Daisuki = "c";
        String S = "x";
        String F = "axb";
        int k = 2;

        int result = solver.countF(Waai, Akari, Daisuki, S, F, k);
        System.out.println("Result: " + result);
    }
}

