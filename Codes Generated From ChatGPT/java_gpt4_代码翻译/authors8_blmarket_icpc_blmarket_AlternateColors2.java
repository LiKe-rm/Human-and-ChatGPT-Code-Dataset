import java.util.*;

public class AlternateColors2 {

    public long C(int a, int b) {
        long ret = 1;
        for (int i = 0; i < b; i++) {
            ret *= (a - i);
            ret /= (i + 1);
        }
        return ret;
    }

    public long H(int a, int b) {
        return C(a + b - 1, b - 1);
    }

    public long countWays(int n, int k) {
        long ret = 0;
        n--;
        k--;

        int tmp = k / 3;
        for (int i = tmp; i >= 0; i--) {
            int rest = k - (i * 3);
            if (rest == 0) {
                ret += H(n - (i * 3), 3);
                continue;
            }

            int tmp2 = rest / 2;
            for (int j = tmp2; j > 0; j--) {
                int rest2 = rest - (j * 2);
                if (rest2 == 0) {
                    ret += 2 * H(n - i * 3 - j * 2, 2);
                    continue;
                }

                ret += 2;
            }
            ret++;
        }
        return ret;
    }

    public static void main(String[] args) {
        AlternateColors2 solver = new AlternateColors2();
        int n = 6;
        int k = 4;
        long result = solver.countWays(n, k);
        System.out.println("Result: " + result);
    }
}
