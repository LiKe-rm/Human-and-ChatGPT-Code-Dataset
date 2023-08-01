import org.luaj.vm2.Globals;
import org.luaj.vm2.LuaError;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.lib.jse.JsePlatform;

import java.util.Scanner;

public class LuaInteractive {

    private static int runInteractive(Globals globals) {
        Scanner scanner = new Scanner(System.in);
        String line;

        while (scanner.hasNextLine()) {
            line = scanner.nextLine();
            try {
                if (!line.isEmpty()) {
                    LuaValue chunk = globals.load(line);
                    chunk.call();
                }
            } catch (LuaError err) {
                System.err.println(err.getMessage());
            }
        }

        return 0;
    }

    public static void main(String[] args) {
        Globals globals = JsePlatform.standardGlobals();

        if (args.length == 0) {
            // Behave interactively if no filename was given.
            runInteractive(globals);
        } else {
            try {
                // We were given a filename, so just read it and return
                LuaValue chunk = globals.loadfile(args[0]);
                LuaValue[] luaArgs = new LuaValue[args.length];
                for (int i = 0; i < args.length; i++) {
                    luaArgs[i] = LuaValue.valueOf(args[i]);
                }
                LuaValue result = chunk.invoke(LuaValue.varargsOf(luaArgs)).arg1();
                System.exit(result.isint() ? result.toint() : 0);
            } catch (LuaError ex) {
                System.err.println(ex.getMessage());
                System.exit(-1);
            }
        }
    }
}
