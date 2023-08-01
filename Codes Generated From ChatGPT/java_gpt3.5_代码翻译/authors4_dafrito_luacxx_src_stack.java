import org.luaj.vm2.*;
import org.luaj.vm2.lib.*;
import java.util.stream.Collectors;

public class LuaUtil {
    private static boolean debuggingAllowed = false;

    public static void allowDebugging(boolean allowed) {
        debuggingAllowed = allowed;
    }

    public static boolean isDebuggingAllowed() {
        return debuggingAllowed;
    }

    public static boolean isDebugging(LuaState state) {
        if (!isDebuggingAllowed()) {
            return false;
        }
        LuaValue debuggingValue = state.getGlobals().get("debugging");
        return debuggingValue.toboolean();
    }

    public static String dump(LuaState state) {
        LuaTable stack = state.getStack();
        StringBuilder sb = new StringBuilder();

        sb.append("Lua stack (");
        sb.append(stack.length());
        sb.append(stack.length() == 1 ? " item" : " items");
        sb.append("): ");

        for (int i = 1; i <= stack.length(); i++) {
            LuaValue value = stack.get(i);

            switch (value.type()) {
                case LuaValue.TBOOLEAN:
                    sb.append(value.toboolean() ? "true" : "false");
                    break;
                case LuaValue.TSTRING:
                    String strValue = value.tojstring();
                    sb.append('"');
                    sb.append(strValue.length() > 30 ? strValue.substring(0, 30) + "..." : strValue);
                    sb.append('"');
                    break;
                case LuaValue.TNUMBER:
                    sb.append(value.tojstring());
                    break;
                case LuaValue.TUSERDATA:
                case LuaValue.TTABLE:
                    sb.append(value.typename());
                    sb.append("(size=");
                    sb.append(value.rawlen());
                    sb.append(")");
                    break;
                case LuaValue.TFUNCTION:
                case LuaValue.TTHREAD:
                    sb.append(value.typename());
                    sb.append("@");
                    sb.append(value.tojstring());
                    break;
                default:
                    sb.append(value.typename());
            }

            if (i != stack.length()) {
                sb.append(", ");
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        LuaState state = new LuaState();
        state.getGlobals().set("debugging", LuaValue.valueOf(true));

        System.out.println("Is debugging: " + isDebugging(state));

        state.load("a = 1; b = 'hello'; c = true; d = function() end; e = {1, 2, 3};").call();

        System.out.println("Dump: " + dump(state));
    }

    public static class LuaState {
        private final Globals globals;
        private final LuaTable stack;

        public LuaState() {
            this.globals = JsePlatform.standardGlobals();
            this.stack = new LuaTable();
        }

        public LuaValue load(String script) {
            return globals.load(script);
        }

        public LuaTable getStack() {
            return stack;
        }

        public Globals getGlobals() {
            return globals;
        }
    }
	public static String traceback(LuaState state, int toplevel) {
        LuaValue debug = state.getGlobals().get("debug");
        LuaValue traceback = debug.get("traceback");
        LuaValue result = traceback.call(LuaValue.NONE, LuaValue.valueOf(toplevel));

        return result.tojstring();
    }

    public static void printTraceback(LuaState state) {
        System.out.println(traceback(state, 1));
    }

    public static void executeScript(LuaState state, String script) {
        try {
            state.load(script).call();
        } catch (LuaError e) {
            System.err.println("Error: " + e.getMessage());
            printTraceback(state);
        }
    }

    public static void main(String[] args) {
        LuaState state = new LuaState();
        state.getGlobals().set("debugging", LuaValue.valueOf(true));

        System.out.println("Is debugging: " + isDebugging(state));

        executeScript(state, "a = 1; b = 'hello'; c = true; d = function() end; e = {1, 2, 3};");

        System.out.println("Dump: " + dump(state));

        executeScript(state, "error('This is an intentional error.')");
    }
}
}
