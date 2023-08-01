import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {

    private static final int MAX_SIZE = 10005;
    private static final long MOD = 1000000007L;
    private static final long[] inverse = new long[MAX_SIZE];

    public static void main(String[] args) throws IOException {
        precalc();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(br);
        }
    }

    private static void precalc() {
        inverse[1] = 1;
        for (int i = 2; i <= MAX_SIZE - 1; i++) {
            int mul = (int) ((MOD + i - 1) / i);
            int mulx = (i * mul) % (int) MOD;
            inverse[i] = (inverse[mulx] * mul) % MOD;
        }
    }

    private static void process(BufferedReader br) throws IOException {
        String[] input = br.readLine().split(" ");
        int n = Integer.parseInt(input[0]);
        int k = Integer.parseInt(input[1]);

        List<Integer> data = new ArrayList<>();
        input = br.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            data.add(Integer.parseInt(input[i]));
        }

        Collections.sort(data, Collections.reverseOrder());

        long cc1 = 1;
        long cc2 = 1;
        for (int i = n - k + 1; i <= n - 1; i++) {
            cc1 *= i;
            cc1 %= MOD;
        }
        for (int i = 1; i <= k - 1; i++) {
            cc2 *= inverse[i];
            cc2 %= MOD;
        }

        long ret = 0;
        for (int i = 0; i <= n - k; i++) {
            long tmp = cc1 * data.get(i);
            tmp %= MOD;
            tmp *= cc2;
            tmp %= MOD;
            ret += tmp;

            cc1 *= (n - k - i);
            cc1 %= MOD;
            cc1 *= inverse[n - 1 - i];
            cc1 %= MOD;
        }
        ret %= MOD;
        System.out.println(ret);
    }
}
