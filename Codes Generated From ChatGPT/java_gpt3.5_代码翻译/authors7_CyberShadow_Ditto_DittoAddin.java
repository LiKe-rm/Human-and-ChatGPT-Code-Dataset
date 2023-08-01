import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class DittoAddin {
    private String dllName;
    private Object instance;
    private Method supportedFunctions;
    private Method prePasteFunction;
    private List<Function> prePasteFunctions;

    public DittoAddin() {
        this.dllName = null;
        this.instance = null;
        this.supportedFunctions = null;
        this.prePasteFunction = null;
        this.prePasteFunctions = new ArrayList<>();
    }

    public boolean doLoad(String dllName, DittoInfo dittoInfo) {
        boolean loaded = false;

        this.dllName = dllName;
        try {
            Class<?> clazz = Class.forName(dllName);
            instance = clazz.getDeclaredConstructor().newInstance();

            Method dittoAddinMethod = clazz.getMethod("dittoAddin", DittoInfo.class, DittoAddinInfo.class);
            DittoAddinInfo dittoAddinInfo = new DittoAddinInfo();
            loaded = (boolean) dittoAddinMethod.invoke(instance, dittoInfo, dittoAddinInfo);

            if (loaded) {
                supportedFunctions = clazz.getMethod("supportedFunctions", DittoInfo.class, FunctionType.class, List.class);
                supportedFunctions.invoke(instance, dittoInfo, FunctionType.PRE_PASTE, prePasteFunctions);
            } else {
                System.err.println("Ditto Addin - dittoAddin returned false, not loading Addin");
            }
        } catch (Exception e) {
            System.err.println("Ditto Addin - Failed to load library on Addin " + dllName);
        }

        return loaded;
    }

    public void cleanup() {
        instance = null;
        supportedFunctions = null;
        prePasteFunction = null;
        prePasteFunctions.clear();
    }

    public boolean supportedFunctions(DittoInfo dittoInfo, FunctionType type, List<Function> functions) {
        if (supportedFunctions != null) {
            try {
                return (boolean) supportedFunctions.invoke(instance, dittoInfo, type, functions);
            } catch (Exception e) {
                System.err.println("Ditto Addin - supportedFunctions returned false");
            }
        } else {
            System.err.println("Ditto Addin - supportedFunctions is null, not calling function to load supported functions");
        }
        return false;
    }

    public boolean prePasteFunction(DittoInfo dittoInfo, String functionName, IClip clip) {
        try {
            if (instance != null) {
                Class<?> clazz = instance.getClass();
                prePasteFunction = clazz.getMethod(functionName, DittoInfo.class, IClip.class);
                return (boolean) prePasteFunction.invoke(instance, dittoInfo, clip);
            }
        } catch (Exception e) {
            System.err.println("Ditto Addin - Failed to call prePasteFunction");
        }
        return false;
    }
}
