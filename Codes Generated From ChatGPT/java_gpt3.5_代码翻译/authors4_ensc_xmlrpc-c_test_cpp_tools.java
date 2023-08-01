import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;

public abstract class TestSuite {

    public abstract String suiteName();

    public abstract void runTests(int indentation) throws Exception;

    public void run(int indentation) {
        try {
            System.out.println(" ".repeat(indentation * 2) + "Running " + suiteName());
            runTests(indentation);
        } catch (Exception e) {
            System.err.println(suiteName() + " failed. " + e.getMessage());
            e.printStackTrace();
        }
        System.out.println(" ".repeat(indentation * 2) + suiteName() + " tests passed.");
    }

    public static void logFailedTest(String fileName, int lineNum, String statement) {
        String msg = String.format("\n%s:%d: expected (%s)", fileName, lineNum, statement);
        throw new RuntimeException(msg);
    }

    public static RuntimeException fileLineError(String filename, int lineNumber, String description) {
        String combined = String.format("%s:%d %s", filename, lineNumber, description);
        return new RuntimeException(combined);
    }

    public static InetAddress testIpAddrFromDecimal(int byte0, int byte1, int byte2, int byte3) {
        byte[] addr = new byte[]{
                (byte) byte0,
                (byte) byte1,
                (byte) byte2,
                (byte) byte3
        };

        try {
            return InetAddress.getByAddress(addr);
        } catch (UnknownHostException e) {
            throw new RuntimeException("Invalid IP address", e);
        }
    }
}
