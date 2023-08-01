import java.util.*;

public class BigFatInteger {
    private List<Integer> primes = new ArrayList<>();

    public int minOperations(int A, int B) {
        primes.clear();
        List<Integer> qs = new ArrayList<>();
        for (int i = 2; i * i <= A; i++) {
            boolean fail = false;
            for (int j = 0; j < primes.size(); j++) {
                if ((i % primes.get(j)) == 0) {
                    fail = true;
                    break;
                }
            }
            if (fail) continue;
            primes.add(i);
            int cnt = 0;
            while ((A % i) == 0) {
                cnt++;
                A /= i;
            }
            if (cnt == 0) continue;
            qs.add(cnt);
        }
        if (A != 1) qs.add(1);
        Collections.sort(qs, Collections.reverseOrder());

        for (int i = 0; i < qs.size(); i++) System.out.print(qs.get(i) + " ");
        System.out.println();

        long cc = (long) B * qs.get(0) - 1;
        int ret = qs.size();
        int cut = 1;
        while (cc > 0) {
            if (cc >= cut) {
                cc -= cut;
                cut *= 2;
                ret++;
            } else {
                return ret + 1;
            }
        }
        return ret;
    }

    public static void main(String[] args) {
        BigFatInteger test = new BigFatInteger();
        System.out.println(test.minOperations(12, 3)); // Sample test case
        // Add more test cases as needed
    }
}
