import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public abstract class AbstractAlgebra<T> {
    public abstract T add(T a, T b);
    public abstract T subtract(T a, T b);
    public abstract T multiply(T a, T b);
    public abstract T divide(T a, T b);
    public abstract T negate(T a);
    public abstract T identity();
    public abstract T zero();
    public abstract T multiplicativeIdentity();

    public T scalarMultiply(T base, BigInteger exponent) {
        T result = multiplicativeIdentity();
        T temp = base;
        for (int i = 0; i < exponent.bitLength(); i++) {
            if (exponent.testBit(i)) {
                result = multiply(result, temp);
            }
            temp = multiply(temp, temp);
        }
        return result;
    }

    public T cascadeScalarMultiply(T x, BigInteger e1, T y, BigInteger e2) {
        List<T> bases = new ArrayList<>();
        List<BigInteger> exponents = new ArrayList<>();

        bases.add(x);
        bases.add(y);
        exponents.add(e1);
        exponents.add(e2);

        return simultaneousMultiply(bases, exponents);
    }

    public T simultaneousMultiply(List<T> bases, List<BigInteger> exponents) {
        int n = bases.size();
        T[] results = (T[]) new Object[n];
        for (int i = 0; i < n; i++) {
            results[i] = scalarMultiply(bases.get(i), exponents.get(i));
        }

        T result = results[0];
        for (int i = 1; i < n; i++) {
            result = add(result, results[i]);
        }
        return result;
    }

    public T exponentiate(T base, BigInteger exponent) {
        return scalarMultiply(base, exponent);
    }

    public T cascadeExponentiate(T x, BigInteger e1, T y, BigInteger e2) {
        return cascadeScalarMultiply(x, e1, y, e2);
    }
}
