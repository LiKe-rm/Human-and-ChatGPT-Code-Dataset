import java.util.HashMap;
import java.util.Map;

public abstract class XmlrpcType {

    private String typeName;

    public XmlrpcType(String typeName) {
        this.typeName = typeName;
    }

    public String getTypeName() {
        return typeName;
    }

    public String defaultParameterBaseName(int position) {
        return typeName + position;
    }

    public abstract String parameterFragment(String baseName);

    public abstract String inputConversionFragment(String baseName);

    public abstract String returnTypeFragment();

    public abstract String outputConversionFragment(String varName);

    private static final Map<String, XmlrpcType> TYPES;

    static {
        TYPES = new HashMap<>();

        // Add instances of XmlrpcType subclasses for each supported XML-RPC data type.
        TYPES.put("int", new SimpleXmlrpcType("int", "Integer", "new Integer", "intValue"));
        TYPES.put("boolean", new SimpleXmlrpcType("boolean", "Boolean", "new Boolean", "booleanValue"));
        TYPES.put("double", new SimpleXmlrpcType("double", "Double", "new Double", "doubleValue"));
        TYPES.put("string", new SimpleXmlrpcType("string", "String", "", ""));
        TYPES.put("dateTime.iso8601", new RawXmlrpcType("dateTime"));
        TYPES.put("base64", new RawXmlrpcType("base64"));
        TYPES.put("struct", new RawXmlrpcType("struct"));
        TYPES.put("array", new RawXmlrpcType("array"));
        TYPES.put("void", new VoidXmlrpcType());
    }

    public static XmlrpcType findXmlrpcType(String name) {
        XmlrpcType xmlrpcType = TYPES.get(name);

        if (xmlrpcType == null) {
            throw new IllegalArgumentException("Unknown XML-RPC type name '" + name + "'");
        }

        return xmlrpcType;
    }
}

abstract class RawXmlrpcType extends XmlrpcType {

    public RawXmlrpcType(String typeName) {
        super(typeName);
    }

    @Override
    public String parameterFragment(String baseName) {
        return "Object /*" + getTypeName() + "*/ " + baseName;
    }

    @Override
    public String inputConversionFragment(String baseName) {
        return baseName;
    }

    @Override
    public String returnTypeFragment() {
        return "Object /*" + getTypeName() + "*/";
    }

    @Override
    public String outputConversionFragment(String varName) {
        return varName;
    }
}

class SimpleXmlrpcType extends XmlrpcType {

    private String nativeType;
    private String makerFunc;
    private String getterFunc;

    public SimpleXmlrpcType(String typeName, String nativeType, String makerFunc, String getterFunc) {
        super(typeName);
        this.nativeType = nativeType;
        this.makerFunc = makerFunc;
        this.getterFunc = getterFunc;
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
        return getterFunc + "(" + varName + ")";
    }
}

class VoidXmlrpcType extends XmlrpcType {
    public VoidXmlrpcType() {
        super("void");
    }

    @Override
    public String parameterFragment(String baseName) {
        throw new IllegalArgumentException("Can't handle functions with 'void' arguments");
    }

    @Override
    public String inputConversionFragment(String baseName) {
        throw new IllegalArgumentException("Can't handle functions with 'void' arguments");
    }

    @Override
    public String returnTypeFragment() {
        return "void";
    }

    @Override
    public String outputConversionFragment(String varName) {
        return "/* Return value ignored. */";
    }
}

public class XmlrpcTypes {
    private static final Map<String, XmlrpcType> TYPES = new HashMap<>();

    static {
        registerType(new SimpleXmlrpcType("int", "Integer", "new Integer", "intValue"));
        registerType(new SimpleXmlrpcType("bool", "Boolean", "new Boolean", "booleanValue"));
        registerType(new SimpleXmlrpcType("double", "Double", "new Double", "doubleValue"));
        registerType(new SimpleXmlrpcType("string", "String", "", ""));
        registerType(new RawXmlrpcType("dateTime"));
        registerType(new RawXmlrpcType("base64"));
        registerType(new RawXmlrpcType("struct"));
        registerType(new RawXmlrpcType("array"));
        registerType(new VoidXmlrpcType());
    }

    private XmlrpcTypes() {
        // Prevent instantiation
    }

    public static void registerType(XmlrpcType type) {
        TYPES.put(type.typeName(), type);
    }

    public static XmlrpcType findXmlrpcType(String name) {
        XmlrpcType type = TYPES.get(name);
        if (type == null) {
            throw new IllegalArgumentException("Unknown XML-RPC type name '" + name + "'");
        }
        return type;
    }
}
