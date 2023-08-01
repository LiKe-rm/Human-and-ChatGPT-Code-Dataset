import org.bouncycastle.math.ec.ECAlgorithms;
import org.bouncycastle.math.ec.ECPoint;
import org.bouncycastle.math.ec.custom.sec.SecT239Field;
import org.bouncycastle.util.Arrays;

import java.math.BigInteger;

public class EC2N {
    private SecT239Field field;
    private BigInteger a;
    private BigInteger b;

    public EC2N(SecT239Field field, BigInteger a, BigInteger b) {
        this.field = field;
        this.a = a;
        this.b = b;
    }

    public SecT239Field getField() {
        return field;
    }

    public BigInteger getA() {
        return a;
    }

    public BigInteger getB() {
        return b;
    }

    public boolean verifyPoint(ECPoint point) {
        if (point.isInfinity()) {
            return true;
        }

        BigInteger x = point.getAffineXCoord().toBigInteger();
        BigInteger y = point.getAffineYCoord().toBigInteger();

        BigInteger lhs = y.multiply(y).mod(field.getModulus());
        BigInteger rhs = x.multiply(x).multiply(x.add(a)).add(b).mod(field.getModulus());

        return lhs.equals(rhs);
    }

    public ECPoint addPoints(ECPoint p, ECPoint q) {
        return p.add(q);
    }

    public ECPoint subtractPoints(ECPoint p, ECPoint q) {
        return p.subtract(q);
    }

    public ECPoint doublePoint(ECPoint p) {
        return p.twice();
    }

    public ECPoint multiplyPoint(ECPoint p, BigInteger k) {
        return p.multiply(k);
    }

    public ECPoint getInverse(ECPoint p) {
        return p.negate();
    }

    public ECPoint getIdentity() {
        return field.getCurve().getInfinity();
    }

    public boolean isEqual(ECPoint p, ECPoint q) {
        return p.equals(q);
    }

    public boolean isOnCurve(ECPoint p) {
        return getField().getCurve().contains(p);
    }

    public ECPoint decodePoint(byte[] encodedPoint) {
        return getField().getCurve().decodePoint(encodedPoint);
    }

    public byte[] encodePoint(ECPoint point, boolean compressed) {
        return point.getEncoded(compressed);
    }

    public static void main(String[] args) {
        // Example usage of the EC2N class
        SecT239Field field = new SecT239Field();
        BigInteger a = new BigInteger("1");
        BigInteger b = new BigInteger("2");

        EC2N ec2n = new EC2N(field, a, b);

        ECPoint p = ec2n.getField().getCurve().createPoint(new BigInteger("3"), new BigInteger("4"));
        ECPoint q = ec2n.getField().getCurve().createPoint(new BigInteger("5"), new BigInteger("6"));

        ECPoint result = ec2n.addPoints(p, q);
        System.out.println("Addition result: " + result);
    }
}
