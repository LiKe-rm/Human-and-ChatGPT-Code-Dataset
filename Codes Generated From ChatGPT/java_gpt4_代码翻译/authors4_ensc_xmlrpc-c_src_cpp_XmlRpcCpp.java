import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.HashMap;
import java.util.Map;

public class XmlRpcExample {
    public static class XmlRpcFault extends Exception {
        private int faultCode;
        private String faultString;

        public XmlRpcFault(int faultCode, String faultString) {
            this.faultCode = faultCode;
            this.faultString = faultString;
        }

        public int getFaultCode() {
            return faultCode;
        }

        public String getFaultString() {
            return faultString;
        }
    }

    public static class XmlRpcEnv {
        private XmlRpcFault fault;

        public XmlRpcEnv() {
            this.fault = null;
        }

        public boolean hasFaultOccurred() {
            return fault != null;
        }

        public XmlRpcFault getFault() {
            return fault;
        }

        public void setFault(XmlRpcFault fault) {
            this.fault = fault;
        }
    }

    public static class XmlRpcValue {
        private Object value;

        public XmlRpcValue() {
            this.value = false;
        }

        public XmlRpcValue(Object value) {
            this.value = value;
        }

        public static XmlRpcValue makeInt(int i) {
            return new XmlRpcValue(i);
        }

        public static XmlRpcValue makeBool(boolean b) {
            return new XmlRpcValue(b);
        }

        public static XmlRpcValue makeDouble(double d) {
            return new XmlRpcValue(d);
        }

        public static XmlRpcValue makeDateTime(String dateTime) {
            return new XmlRpcValue(dateTime);
        }

        public static XmlRpcValue makeString(String str) {
            return new XmlRpcValue(str);
        }

        public static XmlRpcValue makeArray() {
            return new XmlRpcValue(new Object[0]);
        }

        public static XmlRpcValue makeStruct() {
            return new XmlRpcValue(new HashMap<String, XmlRpcValue>());
        }

        public static XmlRpcValue makeBase64(byte[] data) {
            return new XmlRpcValue(Base64.getEncoder().encodeToString(data));
        }

        public int getInt() {
            return (Integer) value;
        }

        public boolean getBool() {
            return (Boolean) value;
        }

        public double getDouble() {
            return (Double) value;
        }

        public String getDateTime() {
            return (String) value;
        }

        public String getString() {
            return (String) value;
        }

        public Object[] getArray() {
            return (Object[]) value;
        }

        public Map<String, XmlRpcValue> getStruct() {
            return (Map<String, XmlRpcValue>) value;
        }

        public byte[] getBase64() {
            return Base64.getDecoder().decode((String) value);
        }

        public void setInt(int i) {
            value = i;
        }

        public void setBool(boolean b) {
            value = b;
        }

        public void setDouble(double d) {
            value = d;
        }

        public void setDateTime(String dateTime) {
            value = dateTime;
        }

        public void setString(String str) {
            value = str;
        }

        public void setArray(Object[] array) {
            value = array;
        }

        public void setStruct(Map<String, XmlRpcValue> struct) {
            value = struct;
        }

        public void setBase64(byte[] data) {
            value = Base64.getEncoder().encodeToString(data);
        }

        @Override
        public String toString() {
            return String.valueOf(value);
        }
    }
}
