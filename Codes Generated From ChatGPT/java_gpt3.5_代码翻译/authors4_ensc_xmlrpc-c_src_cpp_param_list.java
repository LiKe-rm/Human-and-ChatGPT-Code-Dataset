import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ParamList {

    private List<Object> paramVector;

    public ParamList(int paramCount) {
        this.paramVector = new ArrayList<>(paramCount);
    }

    public ParamList add(Object param) {
        this.paramVector.add(param);
        return this;
    }

    public int size() {
        return this.paramVector.size();
    }

    public Object get(int subscript) {
        if (subscript >= this.paramVector.size()) {
            throw new IndexOutOfBoundsException("Subscript of ParamList out of bounds");
        }
        return this.paramVector.get(subscript);
    }

    public int getInt(int paramNumber, int minimum, int maximum) {
        Object value = get(paramNumber);
        if (!(value instanceof Integer)) {
            throw new IllegalArgumentException("Parameter that is supposed to be integer is not");
        }
        int intValue = (int) value;
        if (intValue < minimum || intValue > maximum) {
            throw new IllegalArgumentException("Integer parameter out of range");
        }
        return intValue;
    }

    public boolean getBoolean(int paramNumber) {
        Object value = get(paramNumber);
        if (!(value instanceof Boolean)) {
            throw new IllegalArgumentException("Parameter that is supposed to be boolean is not");
        }
        return (boolean) value}

    public double getDouble(int paramNumber, double minimum, double maximum) {
        Object value = get(paramNumber);
        if (!(value instanceof Double)) {
            throw new IllegalArgumentException("Parameter that is supposed to be floating point number is not");
        }
        double doubleValue = (double) value;
        if (doubleValue < minimum || doubleValue > maximum) {
            throw new IllegalArgumentException("Floating point number parameter out of range");
        }
        return doubleValue;
    }

    public LocalDateTime getDatetime(int paramNumber, TimeConstraint constraint) {
        Object value = get(paramNumber);
        if (!(value instanceof LocalDateTime)) {
            throw new IllegalArgumentException("Parameter that is supposed to be a datetime is not");
        }
        LocalDateTime dateTimeValue = (LocalDateTime) value;
        LocalDateTime now = LocalDateTime.now();

        switch (constraint) {
            case ANY:
                break;
            case NO_FUTURE:
                if (dateTimeValue.isAfter(now)) {
                    throw new IllegalArgumentException(
                            "Datetime parameter that is not supposed to be in the future is.");
                }
                break;
            case NO_PAST:
                if (dateTimeValue.isBefore(now)) {
                    throw new IllegalArgumentException("Datetime parameter that is not supposed to be in the past is.");
                }
                break;
        }
        return dateTimeValue;
    }

    public String getString(int paramNumber) {
        Object value = get(paramNumber);
        if (!(value instanceof String)) {
            throw new IllegalArgumentException("Parameter that is supposed to be a string is not");
        }
        return (String) value;
    }

    public byte[] getBytestring(int paramNumber) {
        Object value = get(paramNumber);
        if (!(value instanceof byte[])) {
            throw new IllegalArgumentException("Parameter that is supposed to be a byte string is not");
        }
        return (byte[]) value;
    }

    public List<Object> getArray(int paramNumber, int minSize, int maxSize) {
        Object value = get(paramNumber);
        if (!(value instanceof List<?>)) {
            throw new IllegalArgumentException("Parameter that is supposed to be an array is not");
        }
        List<Object> arrayValue = (List<Object>) value;

        if (arrayValue.size() < minSize || arrayValue.size() > maxSize) {
            throw new IllegalArgumentException("Array parameter has invalid number of elements");
        }
        return arrayValue;
    }

    public Map<String, Object> getStruct(int paramNumber) {
        Object value = get(paramNumber);
        if (!(value instanceof Map<?, ?>)) {
            throw new IllegalArgumentException("Parameter that is supposed to be a structure is not");
        }
        return (Map<String, Object>) value;
    }

    public void getNil(int paramNumber) {
        Object value = get(paramNumber);
        if (value != null) {
            throw new IllegalArgumentException("Parameter that is supposed to be nil is not");
        }
    }

    public long getI8(int paramNumber, long minimum, long maximum) {
        Object value = get(paramNumber);
        if (!(value instanceof Long)) {
            throw new IllegalArgumentException("Parameter that is supposed to be 64-bit integeris not");
        }
        long longValue = (long) value;
        if (longValue < minimum || longValue > maximum) {
            throw new IllegalArgumentException("64-bit integer parameter out of range");
        }
        return longValue;
    }

    public void verifyEnd(int paramNumber) {
        if (paramNumber < this.paramVector.size()) {
            throw new IllegalArgumentException("Too many parameters");
        }
        if (paramNumber > this.paramVector.size()) {
            throw new IllegalArgumentException("Not enough parameters");
        }
    }

    public enum TimeConstraint {
        ANY,
        NO_FUTURE,
        NO_PAST
    }
}
