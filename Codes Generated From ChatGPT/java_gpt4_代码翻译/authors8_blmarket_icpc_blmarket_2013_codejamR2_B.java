import java.util.*;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
            System.err.println(i);
        }
    }

    private static void process(Scanner scanner) {
        int n = scanner.nextInt();
        long p = scanner.nextLong();
        BigInteger nn = BigInteger.ONE.shiftLeft(n);

        System.out.println(go2(nn.subtract(BigInteger.valueOf(p))).subtract(BigInteger.ONE) + " " + (nn.subtract(BigInteger.ONE).subtract(go2(BigInteger.valueOf(p)))));
    }

    private static BigInteger go2(BigInteger p) {
        BigInteger nn = BigInteger.ONE.shiftLeft(n);

        if (nn.equals(p)) return nn.subtract(BigInteger.ONE);

        BigInteger minCut = nn.subtract(p);
        BigInteger cur = BigInteger.ZERO;
        BigInteger ret = BigInteger.ONE;

        for (int i = 1; i <= n; i++) {
            cur = cur.or(BigInteger.ONE.shiftLeft(n - i));
            if (cur.compareTo(minCut) >= 0) {
                return ret;
            }
            ret = ret.multiply(BigInteger.valueOf(2)).add(BigInteger.ONE);
        }

        return ret;
    }

    private static BigInteger go1(BigInteger p) {
        BigInteger nn = BigInteger.ONE.shiftLeft(n);

        if (nn.equals(p)) return nn.subtract(BigInteger.ONE);

        BigInteger minCut = nn.subtract(p);
        BigInteger ret = BigInteger.ONE;

        for (int i = 1; i <= n; i++) {
            if (minCut.and(BigInteger.ONE.shiftLeft(n - i)).compareTo(BigInteger.ZERO) > 0) {
                return ret.subtract(BigInteger.ONE);
            }
            ret = ret.multiply(BigInteger.valueOf(2)).add(BigInteger.ONE);
        }

        return ret;
    }
}
