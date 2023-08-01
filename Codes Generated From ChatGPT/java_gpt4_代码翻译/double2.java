import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class PolynomialOver<T> {
    private List<T> coefficients;
    private Ring<T> ring;

    public PolynomialOver(Ring<T> ring) {
        this.ring = ring;
        coefficients = new ArrayList<>();
    }

    public PolynomialOver(Ring<T> ring, int coefficientCount) {
        this.ring = ring;
        coefficients = new ArrayList<>(coefficientCount);
        for (int i = 0; i < coefficientCount; ++i) {
            coefficients.add(ring.identity());
        }
    }

    public void randomize(Random random, int coefficientCount) {
        coefficients.clear();
        for (int i = 0; i < coefficientCount; ++i) {
            coefficients.add(ring.randomElement(random));
        }
    }

    public int coefficientCount() {
        int count = coefficients.size();
        while (count > 0 && ring.equal(coefficients.get(count - 1), ring.identity())) {
            count--;
        }
        coefficients = coefficients.subList(0, count);
        return count;
    }

    public T getCoefficient(int i) {
        return (i < coefficients.size()) ? coefficients.get(i) : ring.identity();
    }

    public void setCoefficient(int i, T value) {
        if (i >= coefficients.size()) {
            for (int j = coefficients.size(); j <= i; ++j) {
                coefficients.add(ring.identity());
            }
        }
        coefficients.set(i, value);
    }

    // Additional methods similar to the original C++ code should be implemented here
    // ...
}

interface Ring<T> {
    T add(T a, T b);
    T subtract(T a, T b);
    T multiply(T a, T b);
    T divide(T a, T b);
    T identity();
    T multiplicativeIdentity();
    T inverse(T a);
    T randomElement(Random random);
    boolean equal(T a, T b);
    boolean isUnit(T a);
}

class BigIntRing implements Ring<BigInteger> {
    private int bitLength;

    public BigIntRing(int bitLength) {
        this.bitLength = bitLength;
    }

    @Override
    public BigInteger add(BigInteger a, BigInteger b) {
        return a.add(b);
    }

    @Override
    public BigInteger subtract(BigInteger a, BigInteger b) {
        return a.subtract(b);
    }

    @Override
    public BigInteger multiply(BigInteger a, BigInteger b) {
        return a.multiply(b);
    }

    @Override
    public BigInteger divide(BigInteger a, BigInteger b) {
        return a.divide(b);
    }

    @Override
    public BigInteger identity() {
        return BigInteger.ZERO;
    }

    @Override
    public BigInteger multiplicativeIdentity() {
        return BigInteger.ONE;
    }

    @Override
    public BigInteger inverse(BigInteger a) {
        return a.negate();
    }

    @Override
    public BigInteger randomElement(Random random) {
        return new BigInteger(bitLength, random);
    }

    @Override
    public boolean equal(BigInteger a, BigInteger b) {
        return a.equals(b);
    }

    @Override
    public boolean isUnit(BigInteger a) {
        return a.equals(BigInteger.ONE) || a.equals(BigInteger.ONE.negate());
    }
}
