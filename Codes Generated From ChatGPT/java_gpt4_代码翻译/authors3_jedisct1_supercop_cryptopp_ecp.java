import org.bouncycastle.crypto.ec.CustomNamedCurves;
import org.bouncycastle.crypto.params.ECDomainParameters;
import org.bouncycastle.math.ec.ECCurve;
import org.bouncycastle.math.ec.ECPoint;
import org.bouncycastle.math.ec.FixedPointCombMultiplier;
import org.bouncycastle.math.ec.custom.sec.SecP256R1Curve;
import org.bouncycastle.util.BigIntegers;
import org.bouncycastle.util.encoders.Hex;

import java.math.BigInteger;
import java.security.SecureRandom;

public class ECPJava {
    private final ECCurve curve;
    private final ECPoint G;
    private final BigInteger n;
    private final SecureRandom random;

    public ECPJava() {
        ECDomainParameters params = CustomNamedCurves.getByName("secp256r1");
        curve = params.getCurve();
        G = params.getG();
        n = params.getN();
        random = new SecureRandom();
    }

    public ECPoint scalarMultiply(ECPoint P, BigInteger k) {
        return new FixedPointCombMultiplier().multiply(P, k);
    }

    public void encodePoint(ECPoint point, boolean compressed) {
        byte[] encoded = point.getEncoded(compressed);
        System.out.println("Encoded Point: " + Hex.toHexString(encoded));
    }

    public ECPoint decodePoint(byte[] encoded) {
        return curve.decodePoint(encoded);
    }

    public static void main(String[] args) {
        ECPJava ecp = new ECPJava();

        // Test scalar multiplication
        BigInteger k = BigIntegers.createRandomInRange(BigInteger.ONE, ecp.n.subtract(BigInteger.ONE), ecp.random);
        ECPoint result = ecp.scalarMultiply(ecp.G, k);
        System.out.println("Scalar Multiplication Result: " + result);

        // Test point encoding
        ecp.encodePoint(result, true);
        ecp.encodePoint(result, false);

        // Test point decoding
        byte[] encoded = result.getEncoded(false);
        ECPoint decoded = ecp.decodePoint(encoded);
        System.out.println("Decoded Point: " + decoded);
    }
}
