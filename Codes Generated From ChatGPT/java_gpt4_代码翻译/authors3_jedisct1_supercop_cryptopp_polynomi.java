import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Polynomial {
    private final List<BigInteger> coefficients;

    public Polynomial() {
        coefficients = new ArrayList<>();
    }

    public Polynomial(int size) {
        coefficients = new ArrayList<>(size);
        for (int i = 0; i < size; i++) {
            coefficients.add(BigInteger.ZERO);
        }
    }

    public Polynomial(List<BigInteger> coefficients) {
        this.coefficients = new ArrayList<>(coefficients);
    }

    public Polynomial(Polynomial other) {
        this.coefficients = new ArrayList<>(other.coefficients);
    }

    public void randomize(int coefficientCount) {
        coefficients.clear();
        Random rng = new Random();
        for (int i = 0; i < coefficientCount; i++) {
            coefficients.add(new BigInteger(16, rng));
        }
    }

    public int degree() {
        int degree = coefficients.size() - 1;
        while (degree >= 0 && coefficients.get(degree).equals(BigInteger.ZERO)) {
            degree--;
        }
        return degree;
    }

    public BigInteger getCoefficient(int i) {
        return (i < coefficients.size()) ? coefficients.get(i) : BigInteger.ZERO;
    }

    public void setCoefficient(int i, BigInteger value) {
        if (i >= coefficients.size()) {
            for (int j = coefficients.size(); j <= i; j++) {
                coefficients.add(BigInteger.ZERO);
            }
        }
        coefficients.set(i, value);
    }

    public Polynomial add(Polynomial other) {
        int maxSize = Math.max(degree(), other.degree()) + 1;
        Polynomial result = new Polynomial(maxSize);
        for (int i = 0; i < maxSize; i++) {
            result.setCoefficient(i, getCoefficient(i).add(other.getCoefficient(i)));
        }
        return result;
    }

    public Polynomial subtract(Polynomial other) {
        int maxSize = Math.max(degree(), other.degree()) + 1;
        Polynomial result = new Polynomial(maxSize);
        for (int i = 0; i < maxSize; i++) {
            result.setCoefficient(i, getCoefficient(i).subtract(other.getCoefficient(i)));
        }
        return result;
    }

    public Polynomial multiply(Polynomial other) {
        int maxSize = degree() + other.degree() + 1;
        Polynomial result = new Polynomial(maxSize);
        for (int i = 0; i <= degree(); i++) {
            for (int j = 0; j <= other.degree(); j++) {
                BigInteger product = getCoefficient(i).multiply(other.getCoefficient(j));
                result.setCoefficient(i + j, result.getCoefficient(i + j).add(product));
            }
        }
        return result;
    }

    public Polynomial[] divideAndRemainder(Polynomial divisor) {
        if (divisor.degree() < 0) {
            throw new IllegalArgumentException("Divide by zero");
        }
        Polynomial quotient = new Polynomial();
        Polynomial remainder = new Polynomial(this);
        while (remainder.degree() >= divisor.degree()) {
            int exponent = remainder.degree() - divisor.degree();
            BigInteger factor = remainder.getCoefficient(remainder.degree()).divide(divisor.getCoefficient(divisor.degree()));
            Polynomial term = new Polynomial();
            term.setCoefficient(exponent, factor);
            quotient = quotient.add(term);
            remainder = remainder.subtract(term.multiply(divisor));
        }
        return new Polynomial[]{quotient, remainder};
    }
}
