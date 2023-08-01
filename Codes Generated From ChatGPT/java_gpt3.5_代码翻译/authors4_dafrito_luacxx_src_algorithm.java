import org.luaj.vm2.*;
import org.luaj.vm2.lib.jse.JsePlatform;

import java.util.HashMap;
import java.util.Map;

public class LuaIntegration {

    private static final LuaValue ON_ERROR = new OneArgFunction() {
        @Override
        public LuaValue call(LuaValue error) {
            if (error.isstring()) {
                throw new LuaError(error.tojstring());
            } else {
                throw new LuaError("An unspecified runtime error occurred during the execution of Lua code");
            }
        }
    };

    public static void invoke(LuaValue callable, Varargs args) {
        invoke(callable, args, LuaValue.NONE);
    }

    public static void invoke(LuaValue callable, Varargs args, LuaValue errorHandler) {
        LuaValue result;
        if (errorHandler.isnil()) {
            result = callable.invoke(args);
        } else {
            result = callable.invoke(args).catcherrors(errorHandler);
        }

        if (!result.isnil()) {
            throw new LuaError(result.tojstring());
        }
    }

    public static void main(String[] args) {
        Globals globals = JsePlatform.standardGlobals();
        LuaValue chunk = globals.load("return function(a, b) return a + b end");
        LuaValue func = chunk.call();

        try {
            invoke(func, LuaValue.varargsOf(new LuaValue[]{LuaValue.valueOf(1), LuaValue.valueOf(2)}), ON_ERROR);
        } catch (LuaError e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
