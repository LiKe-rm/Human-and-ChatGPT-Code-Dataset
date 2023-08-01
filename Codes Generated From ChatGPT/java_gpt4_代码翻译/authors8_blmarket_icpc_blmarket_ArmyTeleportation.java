import java.util.*;

public class ArmyTeleportation {

    private static class Pair {
        long first;
        long second;

        Pair(long first, long second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair pair = (Pair) o;
            return first == pair.first && second == pair.second;
        }
    }

    private static long abs(long a) {
        return a >= 0 ? a : -a;
    }

    private static long gcd(long a, long b) {
        a = abs(a);
        b = abs(b);
        if (a > b) {
            long tmp = a;
            a = b;
            b = tmp;
        }
        while (a != 0) {
            b = b % a;
            long tmp = a;
            a = b;
            b = tmp;
        }
        return b;
    }

    private static boolean divi(long a, long b) {
        if (a == 0) return true;
        if (b == 0) return false;
        return (a % b) == 0;
    }

    private static boolean match(List<Pair> v1, List<Pair> v2, List<Pair> v3, List<Pair> v4, List<Integer> xt, List<Integer> yt) {
        v3.clear();
        for (int i = 0; i < v1.size(); i++) {
            v3.add(new Pair(v1.get(i).first - v2.get(i).first, v1.get(i).second - v2.get(i).second));
        }
        for (int i = 1; i < v3.size(); i++) {
            if (!v3.get(i).equals(v3.get(0))) return false;
        }

        v4.clear();
        v4.add(new Pair(xt.get(0) - xt.get(1), yt.get(0) - yt.get(1)));
        v4.add(new Pair(xt.get(0) - xt.get(2), yt.get(0) - yt.get(2)));
        v4.add(new Pair(xt.get(1) - xt.get(2), yt.get(1) - yt.get(2)));

        long xT = v3.get(0).first;
        long yT = v3.get(0).second;

        long gx = gcd(gcd(v4.get(0).first, v4.get(1).first), v4.get(2).first);
        long gy = gcd(gcd(v4.get(0).second, v4.get(1).second), v4.get(2).second);
        if (!divi(xT, gx) || !divi(yT, gy)) return false;

        v4.get(0).first *= v4.get(2).second;
        v4.get(1).first *= v4.get(2).second;
        xT *= v4.get(2).second;

        v4.get(0).second *= v4.get(2).first;
        v4.get(1).second *= v4.get(2).first;
        yT *= v4.get(2).first;

        long ah = v4.get(0).first - v4.get(0).second;
        long bh = v4.get(1).first - v4.get(1).second;
    }
    void test_case_16() {
    int Arr0[] = {0, 0, 11, 22};
    vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
    int Arr1[] = {3, 4, 6};
    vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
    int Arr2[] = {6, 8, 12};
    vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
    string Arg6 = "impossible";
    verify_case(16, Arg6, ifPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
}

// END CUT HERE

}
