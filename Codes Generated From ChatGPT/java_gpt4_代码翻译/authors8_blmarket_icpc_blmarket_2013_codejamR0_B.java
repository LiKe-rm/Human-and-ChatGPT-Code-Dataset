import java.util.ArrayList;
import java.util.Scanner;

public class FairAndSquare {
    public static void main(String[] args) {
        ArrayList<String> bigV = new ArrayList<>();
        precalc(bigV);

        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        scanner.nextLine();

        for (int i = 1; i <= T; i++) {
            String A = scanner.next();
            String B = scanner.next();
            System.out.printf("Case #%d: ", i);
            process(A, B, bigV);
        }
    }

    private static void precalc(ArrayList<String> bigV) {
        chkgood("1", bigV);
        chkgood("2", bigV);
        chkgood("3", bigV);
        go("1", bigV);
        go("2", bigV);
        bigV.sort((a, b) -> comp(a, b) ? -1 : 1);
    }

    private static void process(String A, String B, ArrayList<String> bigV) {
        int ret = 0;
        for (String num : bigV) {
            if (comp(A, num) && comp(num, B)) {
                ret++;
            }
        }
        System.out.println(ret);
    }

    private static void go(String tmp, ArrayList<String> bigV) {
        if (tmp.length() > 52) return;
        for (int i = 0; i < 3; i++) {
            tmp += (char) (i + '0');
            if (chkgood(tmp, bigV)) {
                go(tmp, bigV);
            }
            tmp = tmp.substring(0, tmp.length() - 1);
        }
    }

    private static boolean chkgood(String a, ArrayList<String> bigV) {
        boolean ret = false;
        int sum = 0, mid = 0;
        for (int i = 0; i < a.length(); i++) {
            sum += sqr(a.charAt(i) - '0') * 2;
        }
        mid = sqr(a.charAt(a.length() - 1) - '0');

        String tmp = new StringBuilder(a).reverse().toString();
        if (sum < 10) {
            ret = true;
            candidate(a + tmp, bigV);
        }
        sum -= mid;
        if (sum < 10) {
            ret = true;
            candidate(a + tmp.substring(1), bigV);
        }
        return ret;
    }

    private static void candidate(String candi, ArrayList<String> bigV) {
        StringBuilder tmp = new StringBuilder();
        for (int i = 0; i < candi.length() * 2 - 1; i++) {
            tmp.append('0');
        }

        for (int i = 0; i < candi.length(); i++) {
            candi = candi.substring(0, i) + (char) (candi.charAt(i) - '0') + candi.substring(i + 1);
        }

        for (int i = 0; i < candi.length(); i++) {
            for (int j = 0; j < candi.length(); j++) {
                tmp.setCharAt(i + j, (char) (tmp.charAt(i + j) + (candi.charAt(i) - '0') * (candi.charAt(j) - '0')));
            }
        }
        bigV.add(tmp.toString());
    }

    private static boolean comp(String a, String b) {
        int sz1 = a.length(), sz2 = b.length();
        if (sz1 != sz2) return sz1 < sz2;
        for (int i = 0; i < sz1; i++) {
            if (a.charAt(i) != b.charAt(i)) return a.charAt(i) < b.charAt(i);
        }
        return false;
    }

    private static int sqr(int x) {
        return x * x;
    }
}

