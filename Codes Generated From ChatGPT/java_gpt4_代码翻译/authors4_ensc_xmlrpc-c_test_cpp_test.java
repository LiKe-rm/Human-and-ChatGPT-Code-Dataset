import java.util.*;

public class TestHarness {
    public static void main(String[] args) {
        testFault();
        testEnv();
        testValue();
    }

    public static void testFault() {
        // Create a new fault and perform basic operations.
        XmlRpcFault fault1 = new XmlRpcFault(6, "Sample fault");
        assert fault1.getFaultCode() == 6;
        assert fault1.getFaultString().equals("Sample fault");

        // Test copy constructor.
        XmlRpcFault fault2 = new XmlRpcFault(fault1);
        assert fault2.getFaultCode() == 6;
        assert fault2.getFaultString().equals("Sample fault");
    }

    public static void testEnv() {
        // Perform simple environment tests.
        XmlRpcEnv env1 = new XmlRpcEnv();
        assert !env1.hasFaultOccurred();
        env1.setFault(8, "Fault 8");
        assert env1.hasFaultOccurred();
        assert env1.getFault().getFaultCode() == 8;
        assert env1.getFault().getFaultString().equals("Fault 8");

        // Test clearing fault.
        env1.clearFault();
        assert !env1.hasFaultOccurred();
    }

    public static void testValue() {
        // Test basic value functionality.
        XmlRpcValue value1 = new XmlRpcValue();
        value1.setInt(42);
        assert value1.getType() == XmlRpcValue.Type.INTEGER;
        assert value1.getInt() == 42;

        // Test copy constructor.
        XmlRpcValue value2 = new XmlRpcValue(value1);
        assert value2.getType() == XmlRpcValue.Type.INTEGER;
        assert value2.getInt() == 42;

        // Test fault in environment.
        XmlRpcEnv env = new XmlRpcEnv();
        value1.setFault(env, 9, "Fault 9");
        assert env.hasFaultOccurred();
        assert env.getFault().getFaultCode() == 9;
        assert env.getFault().getFaultString().equals("Fault 9");
    }
}

class XmlRpcFault {
    private int faultCode;
    private String faultString;

    public XmlRpcFault(int faultCode, String faultString) {
        this.faultCode = faultCode;
        this.faultString = faultString;
    }

    public XmlRpcFault(XmlRpcFault other) {
        this.faultCode = other.faultCode;
        this.faultString = other.faultString;
    }

    public int getFaultCode() {
        return faultCode;
    }

    public String getFaultString() {
        return faultString;
    }
}

class XmlRpcEnv {
    private XmlRpcFault fault;

    public XmlRpcEnv() {
        fault = null;
    }

    public boolean hasFaultOccurred() {
        return fault != null;
    }

    public XmlRpcFault getFault() {
        return fault;
    }

    public void setFault(int faultCode, String faultString) {
        fault = new XmlRpcFault(faultCode, faultString);
    }

    public void clearFault() {
        fault = null;
    }
}

class XmlRpcValue {
    public enum Type {
        INTEGER,
        STRING,
        FAULT
    }

    private Type type;
    private int intValue;
    private String stringValue;
    private XmlRpcFault faultValue;

    public XmlRpcValue() {
        type = null;
    }

    public XmlRpcValue(XmlRpcValue other) {
        this.type = other.type;
        this.intValue = other.intValue;
        this.stringValue = other.stringValue;
        this.faultValue = other.faultValue != null ? new XmlRpcFault(other.faultValue) : null;
    }

    public Type getType() {
        return type;
    }

    public void setInt(int value) {
        type = Type.INTEGER;
        intValue = value;
    }

    public int getInt() {
        return intValue;
    }

    public void setString(String value) {
        type = Type.STRING;
        stringValue = value;
    }

    public String getString() {
        return stringValue;
    }

    public void setFault(XmlRpcFault value) {
        type = Type.FAULT;
        faultValue = new XmlRpcFault(value);
    }

    public XmlRpcFault getFault() {
        return faultValue;
    }

    public boolean isInt() {
        return type == Type.INTEGER;
    }

    public boolean isString() {
        return type == Type.STRING;
    }

    public boolean isFault() {
        return type == Type.FAULT;
    }

    public void clear() {
        type = null;
    }
}

public class XmlRpcParser {
    public static XmlRpcValue parseResponse(String xml) {
        XmlRpcEnv env = new XmlRpcEnv();
        XmlRpcValue value = parseValue(xml, env);

        if (env.hasFaultOccurred()) {
            value.setFault(env.getFault());
        }

        return value;
    }

    private static XmlRpcValue parseValue(String xml, XmlRpcEnv env) {
        // Implement XML parsing logic to extract the desired value
        // based on the XML-RPC specification. Set the fault in the env
        // if an error occurs during parsing.

        return new XmlRpcValue();
    }
}
