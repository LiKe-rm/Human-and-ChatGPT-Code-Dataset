import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class XmlRpcTest {

    public interface TestSuite {
        String suiteName();
        void runTests();
    }

    // ... booleanTestSuite, datetimeTestSuite, stringTestSuite, bytestringTestSuite, nilTestSuite, i8TestSuite classes ...

    public static class StructTestSuite implements TestSuite {
        public String suiteName() {
            return "structTestSuite";
        }

        public void runTests() {
            Map<String, XmlRpcValue> structData = new LinkedHashMap<>();
            structData.put("the_integer", new XmlRpcValue(XmlRpcValue.ValueType.INT, 9));

            XmlRpcValue struct1 = new XmlRpcValue(XmlRpcValue.ValueType.STRUCT, structData);

            Map<String, XmlRpcValue> dataReadBack = struct1.asStruct();

            assert dataReadBack.get("the_integer").asInt() == 9;

            Map<String, Integer> structDatax = new LinkedHashMap<>();
            structDatax.put("one", 1);
            structDatax.put("two", 2);

            XmlRpcValue struct5 = XmlRpcValue.toValue(structDatax);
            assert struct5.getType() == XmlRpcValue.ValueType.STRUCT;
            Map<String, XmlRpcValue> dataReadBackx = struct5.asStruct();

            assert dataReadBackx.get("two").asInt() == 2;

            Map<String, Integer> test5x = XmlRpcValue.fromValue(struct5);
            assert test5x.get("two") == 2;
        }
    }

    // ... other test suite classes ...

    public static void main(String[] args) {
        List<TestSuite> testSuites = new ArrayList<>();

        testSuites.add(new BooleanTestSuite());
        testSuites.add(new DatetimeTestSuite());
        testSuites.add(new StringTestSuite());
        testSuites.add(new ByteStringTestSuite());
        testSuites.add(new NilTestSuite());
        testSuites.add(new I8TestSuite());
        testSuites.add(new StructTestSuite());
        // ... add other test suites ...

        for (TestSuite suite : testSuites) {
            System.out.println("Running " + suite.suiteName());
            suite.runTests();
        }

        System.out.println("All tests passed.");
    }
}
