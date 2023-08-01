import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class CAST128 {

    private static final int[][] S = {
        // ...
    };

    private int[] K = new int[32];
    private boolean reduced;
    private int[] t = new int[3];

    public CAST128(byte[] userKey, int keylength) {
        setKey(userKey, keylength);
    }

    private static int getByte(int x, int n) {
        return (x >> (8 * n)) & 0xFF;
    }

    private static int rotlVariable(int x, int y) {
        return (x << y) | (x >>> (32 - y));
    }

    private void setKey(byte[] userKey, int keylength) {
        // ...
    }

    private void f1(int l, int r, int km, int kr) {
        // ...
    }

    private void f2(int l, int r, int km, int kr) {
        // ...
    }

    private void f3(int l, int r, int km, int kr) {
        // ...
    }

    public byte[] encryptBlock(byte[] inBlock) {
        // ...
    }

    public byte[] decryptBlock(byte[] inBlock) {
        // ...
    }

    public static void main(String[] args) {
        // ...
    }
}
