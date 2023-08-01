import java.util.ArrayList;
import java.util.List;

public class GIBaseInfo {
    public enum GIInfoType {
        INVALID,
        FUNCTION,
        CALLBACK,
        STRUCT,
        BOXED,
        ENUM,
        FLAGS,
        OBJECT,
        INTERFACE,
        CONSTANT,
        UNION,
        VALUE,
        SIGNAL,
        VFUNC,
        PROPERTY,
        FIELD,
        ARG,
        TYPE,
        INVALID_0,
        UNRESOLVED;

        public static String toString(GIInfoType infoType) {
            switch (infoType) {
                case INVALID:
                    return "invalid";
                case FUNCTION:
                    return "function";
                case CALLBACK:
                    return "callback";
                case STRUCT:
                    return "struct";
                case BOXED:
                    return "boxed";
                case ENUM:
                    return "enum";
                case FLAGS:
                    return "flags";
                case OBJECT:
                    return "object";
                case INTERFACE:
                    return "interface";
                case CONSTANT:
                    return "constant";
                case UNION:
                    return "union";
                case VALUE:
                    return "value";
                case SIGNAL:
                    return "signal";
                case VFUNC:
                    return "vfunc";
                case PROPERTY:
                    return "property";
                case FIELD:
                    return "field";
                case ARG:
                    return "arg";
                case TYPE:
                    return "type";
                case INVALID_0:
                case UNRESOLVED:
                    return "Unresolved";
                default:
                    return String.valueOf(infoType);
            }
        }
    }

    private GIInfoType infoType;
    private String name;
    private List<GIBaseInfo> methods;
    private List<GIBaseInfo> fields;

    public GIBaseInfo(GIInfoType infoType, String name) {
        this.infoType = infoType;
        this.name = name;
        this.methods = new ArrayList<>();
        this.fields = new ArrayList<>();
    }

    public void addMethod(GIBaseInfo methodInfo) {
        methods.add(methodInfo);
    }

    public void addField(GIBaseInfo fieldInfo) {
        fields.add(fieldInfo);
    }

    public String toString() {
        StringBuilder str = new StringBuilder();

        switch (infoType) {
            case FUNCTION:
            case CALLBACK:
            case SIGNAL:
            case VFUNC:
                // Handle these cases
                break;
            case STRUCT:
                str.append("struct ").append(name).append(" {");

                // Enumerate methods
                for (GIBaseInfo methodInfo : methods) {
                    str.append("\n\t").append(methodInfo.toString());
                }

                // Enumerate fields
                for (GIBaseInfo fieldInfo : fields) {
                    str.append("\n\t").append(fieldInfo.toString());
                }

                str.append("\n};");
                break;
            case FIELD:
                // Handle this case
                break;
            case TYPE:
                // Handle this case
                break;
            case ARG:
                // Handle this case
                break;
            case OBJECT:
                // Handle this case
                break;
            case INTERFACE:
                // Handle this case
                break;
            default:
                str.append(GIInfoType.toString(infoType));
                break;
        }

        return str.toString();
    }
public static String giBaseInfoToString(GICallableInfo info) {
        StringBuilder sb = new StringBuilder();
        sb.append(giInfoTypeToString(info.infoType));
        sb.append(" ").append(info.name).append("(");

        for (int i = 0; i < info.arguments.size(); ++i) {
            GIArgument arg = info.arguments.get(i);
            sb.append(arg.value.toString());
            if (i < info.arguments.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append(")");

        return sb.toString();
    }

    public static void main(String[] args) {
        GICallableInfo callableInfo = new GICallableInfo();
        callableInfo.infoType = GIInfoType.FUNCTION;
        callableInfo.name = "testFunction";
        callableInfo.arguments = new ArrayList<>();

        GIArgument arg1 = new GIArgument();
        arg1.value = "int";
        callableInfo.arguments.add(arg1);

        GIArgument arg2 = new GIArgument();
        arg2.value = "String";
        callableInfo.arguments.add(arg2);

        System.out.println(giBaseInfoToString(callableInfo));
    }
}
