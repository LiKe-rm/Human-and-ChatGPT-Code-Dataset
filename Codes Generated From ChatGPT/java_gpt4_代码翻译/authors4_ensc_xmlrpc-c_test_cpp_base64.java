import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Base64;
import java.util.List;

public class Base64TestSuite {

    public static String suiteName() {
        return "base64TestSuite";
    }

    public static void runTests() {

        byte[] bytes0Data = "This is a test".getBytes(StandardCharsets.UTF_8);
        List<Byte> bytes0 = toByteList(bytes0Data);

        String base64_0 = "VGhpcyBpcyBhIHRlc3QA";

        String expectedBase64_0 = base64_0;

        test(base64FromBytes(bytes0).equals(expectedBase64_0));

        test(bytesFromBase64(base64_0).equals(bytes0));

        byte[] bytes1Data = { (byte) 0x80, (byte) 0xff };
        List<Byte> bytes1 = toByteList(bytes1Data);

        String base64_1 = "gP8=";

        String expectedBase64_1 = base64_1;

        test(base64FromBytes(bytes1).equals(expectedBase64_1));

        test(bytesFromBase64(base64_1).equals(bytes1));
    }

    private static String base64FromBytes(List<Byte> bytes) {
        byte[] byteArray = toByteArray(bytes);
        return Base64.getEncoder()..encodeToString(byteArray);
    }

    private static List<Byte> bytesFromBase64(String base64) {
        byte[] decodedBytes = Base64.getDecoder().decode(base64);
        return toByteList(decodedBytes);
    }

    private static List<Byte> toByteList(byte[] byteArray) {
        Byte[] boxedArray = new Byte[byteArray.length];
        for (int i = 0; i < byteArray.length; i++) {
            boxedArray[i] = byteArray[i];
        }
        return Arrays.asList(boxedArray);
    }

    private static byte[] toByteArray(List<Byte> byteList) {
        byte[] byteArray = new byte[byteList.size()];
        for (int i = 0; i < byteList.size(); i++) {
            byteArray[i] = byteList.get(i);
        }
        return byteArray;
    }

    private static void test(boolean condition) {
        if (!condition) {
            throw new AssertionError("Test failed");
        }
    }

    public static void main(String[] args) {
        System.out.println("Running " + suiteName());
        runTests();
        System.out.println("All tests passed");
    }
}
