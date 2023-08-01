import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

public class XmlrpcMethod {
    private String functionName;
    private String methodName;
    private String help;
    private List<List<XmlrpcType>> signatureList;

    public XmlrpcMethod(String functionName, String methodName, String help, List<List<XmlrpcType>> signatureList) {
        this.functionName = functionName;
        this.methodName = methodName;
        this.help = help;
        this.signatureList = signatureList;
    }

    public XmlrpcMethod(XmlrpcMethod other) {
        this.functionName = other.functionName;
        this.methodName = other.methodName;
        this.help = other.help;
        this.signatureList = new ArrayList<>(other.signatureList);
    }

    public XmlrpcMethod assign(XmlrpcMethod other) {
        if (this != other) {
            this.functionName = other.functionName;
            this.methodName = other.methodName;
            this.help = other.help;
            this.signatureList = new ArrayList<>(other.signatureList);
        }
        return this;
    }

    public int parameterCount(int synopsisIndex) {
        List<XmlrpcType> funcSynopsis = signatureList.get(synopsisIndex);
        int size = funcSynopsis.size();

        if (size < 1) {
            throw new IllegalArgumentException("Synopsis contains no items");
        }

        return size - 1;
    }

    public XmlrpcType parameterType(int synopsisIndex, int parameterIndex) {
        List<XmlrpcType> funcSynopsis = signatureList.get(synopsisIndex);
        return funcSynopsis.get(parameterIndex + 1);
    }

    public XmlrpcType returnType(int synopsisIndex) {
        List<XmlrpcType> funcSynopsis = signatureList.get(synopsisIndex);
        return funcSynopsis.get(0);
    }

    public void printParameters(PrintStream out, int synopsisIndex) {
        int end = parameterCount(synopsisIndex);

        boolean first = true;

        for (int i = 0; i < end; ++i) {
            if (!first) {
                out.print(", ");
            }

            XmlrpcType ptype = parameterType(synopsisIndex, i);
            String localName = ptype.defaultParameterBaseName(i + 1);
            out.print(ptype.parameterFragment(localName));

            first = false;
        }
    }

    public void printDeclaration(PrintStream out, int synopsisIndex) {
        try {
            XmlrpcType rtype = returnType(synopsisIndex);

            out.print("    " + rtype.returnTypeFragment + " " + functionName + " (");

            printParameters(out, synopsisIndex);

            out.println(");");
        } catch (Exception e) {
            String message = "Failed to generate header for signature " +
                    synopsisIndex + ". " + e.getMessage();
            throw new IllegalStateException(message);
        }
    }

    public void printDeclarations(PrintStream out) {
        try {
            out.println();
            out.println("    /* " + help + " */");

            int end = signatureList.size();

            for (int i = 0; i < end; ++i) {
                printDeclaration(out, i);
            }
        } catch (Exception e) {
            String message = "Failed to generate declarations for method " +
                    functionName + ". " + e.getMessage();
            throw new IllegalStateException(message);
        }
    }

    // The following methods are not fully implemented, as they would require
    // a complete implementation of the XML-RPC client and type handling in Java.
    // These are placeholders to give you an idea of how the code might look.
    public void printDefinition(OutputStream out, String className, int synopsisIndex) {
        throw new UnsupportedOperationException("printDefinition is not fully implemented");
    }

    public void printDefinitions(OutputStream out, String className) {
        throw new UnsupportedOperationException("printDefinitions is not fully implemented");
    }
}
