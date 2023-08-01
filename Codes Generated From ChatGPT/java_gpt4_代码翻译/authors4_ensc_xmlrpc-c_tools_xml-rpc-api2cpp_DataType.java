import java.util.HashMap;
import java.util.Map;

public abstract class DataType {

    private String typeName;

    public DataType(String typeName) {
        this.typeName = typeName;
    }

    public String getTypeName() {
        return typeName;
    }

    public abstract String defaultParameterBaseName(int position);

    public abstract String parameterFragment(String baseName);

    public abstract String inputConversionFragment(String baseName);

    public abstract String returnTypeFragment();

    public abstract String outputConversionFragment(String varName);

    private static Map<String, DataType> createTypeMap() {
        Map<String, DataType> typeMap = new HashMap<>();

        typeMap.put("int", new SimpleDataType("int", "int", "XmlRpcValue::makeInt", "getInt"));
        typeMap.put("boolean", new SimpleDataType("boolean", "boolean", "XmlRpcValue::makeBool", "getBool"));
        typeMap.put("double", new SimpleDataType("double", "double", "XmlRpcValue::makeDouble", "getDouble"));
        typeMap.put("string", new SimpleDataType("string", "String", "XmlRpcValue::makeString", "getString"));

        // Raw data types are not fully implemented in this example
        typeMap.put("dateTime.iso8601", new RawDataType("dateTime.iso8601"));
        typeMap.put("base64", new RawDataType("base64"));
        typeMap.put("struct", new RawDataType("struct"));
        typeMap.put("array", new RawDataType("array"));
        typeMap.put("void", new VoidDataType());

        return typeMap;
    }

    private static final Map<String, DataType> typeMap = createTypeMap();

    public static DataType findDataType(String name) {
        DataType dataType = typeMap.get(name);

        if (dataType == null) {
            throw new IllegalArgumentException("Unknown XML-RPC type name '" + name + "'");
        }

        return dataType;
    }
}

class SimpleDataType extends DataType {
    private String nativeType;
    private String makerFunc;
    private String getterFunc;

    public SimpleDataType(String typeName, String nativeType, String makerFunc, String getterFunc) {
        super(typeName);
        this.nativeType = nativeType;
        this.makerFunc = makerFunc;
        this.getterFunc = getterFunc;
    }

    @Override
    public String defaultParameterBaseName(int position) {
        return getTypeName() + position;
    }

    @Override
    public String parameterFragment(String baseName) {
        return nativeType + " " + baseName;
    }

    @Override
    public String inputConversionFragment(String baseName) {
        return makerFunc + "(" + baseName + ")";
    }

    @Override
    public String returnTypeFragment() {
        return nativeType;
    }

    @Override
    public String outputConversionFragment(String varName) {
        return varName + "." + getterFunc + "()";
    }
}

class RawDataType extends DataType {
    public RawDataType(String typeName) {
        super(typeName);
    }
}