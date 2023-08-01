import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.Random;

public class LUC {
    private BigInteger n, e, p, q, u;

    public LUC(int keySize, BigInteger publicExponent) {
        generateKeyPair(keySize, publicExponent);
    }

    private void generateKeyPair(int keySize, BigInteger publicExponent) {
        SecureRandom rng = new SecureRandom();
        e = publicExponent;

        while (true) {
            p = BigInteger.probablePrime(keySize / 2, rng);
            if (p.subtract(BigInteger.ONE).gcd(e).equals(BigInteger.ONE) &&
                p.add(BigInteger.ONE).gcd(e).equals(BigInteger.ONE)) {
                break;
            }
        }

        while (true) {
            q = BigInteger.probablePrime(keySize / 2, rng);
            if (q.subtract(BigInteger.ONE).gcd(e).equals(BigInteger.ONE) &&
                q.add(BigInteger.ONE).gcd(e).equals(BigInteger.ONE)) {
                break;
            }
        }

        n = p.multiply(q);
        u = q.modInverse(p);
    }

    public BigInteger applyFunction(BigInteger x) {
        return lucas(e, x, n);
    }

    public BigInteger calculateInverse(BigInteger x) {
        return inverseLucas(e, x, q, p, u);
    }

    private static BigInteger lucas(BigInteger e, BigInteger x, BigInteger n) {
        BigInteger[] lucasValues = lucasSequence(e, x, n);
        return lucasValues[0].subtract(lucasValues[1]).mod(n);
    }

    private static BigInteger[] lucasSequence(BigInteger e, BigInteger x, BigInteger n) {
        int m = e.bitLength();
        BigInteger[] result = new BigInteger[]{BigInteger.ONE, x};
        for (int i = m - 2; i >= 0; i--) {
            result[0] = result[0].multiply(result[1]).mod(n);
            result[1] = result[1].multiply(result[1]).subtract(BigInteger.ONE).mod(n);
            if (e.testBit(i)) {
                BigInteger tmp = result[0];
                result[0] = result[0].add(result[1]).mod(n);
                result[1] = result[1].add(tmp).mod(n);
            }
        }
        return result;
    }

    private static BigInteger inverseLucas(BigInteger e, BigInteger x, BigInteger q, BigInteger p, BigInteger u) {
        BigInteger[] lucasValuesP = lucasSequence(e, x, p);
        BigInteger[] lucasValuesQ = lucasSequence(e, x, q);

        BigInteger vP = lucasValuesP[0].subtract(lucasValuesP[1]).mod(p);
        BigInteger vQ = lucasValuesQ[0].subtract(lucasValuesQ[1]).mod(q);

        BigInteger xp = p.multiply(u).multiply(vQ).add(q.multiply(vP)).mod(p.multiply(q));
        return xp;
    }
}
