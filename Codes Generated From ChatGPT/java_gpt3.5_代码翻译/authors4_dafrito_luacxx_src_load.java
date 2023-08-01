import org.luaj.vm2.Globals;
import org.luaj.vm2.LuaError;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.compiler.LuaC;
import org.luaj.vm2.lib.jse.JsePlatform;

import java.io.*;

public class LuaLoader {
    public static LuaValue loadFile(Globals globals, String filePath) throws IOException {
        try (FileReader fileReader = new FileReader(filePath)) {
            return loadReader(globals, fileReader, filePath);
        }
    }

    public static LuaValue loadReader(Globals globals, Reader reader, String chunkName) throws IOException {
        try (BufferedReader bufferedReader = new BufferedReader(reader)) {
            String line;
            StringBuilder luaCode = new StringBuilder();
            boolean skipShebang = true;

            while ((line = bufferedReader.readLine()) != null) {
                if (skipShebang && line.startsWith("#!")) {
                    luaCode.append("\n");
                } else {
                    luaCode.append(line).append("\n");
                }
                skipShebang = false;
            }

            return globals.load(luaCode.toString(), chunkName, "t", globals);
        }
    }

    public static void main(String[] args) {
        try {
            Globals globals = JsePlatform.standardGlobals();
            LuaC.install(globals);
            String filePath = "path/to/your/lua_script.lua";
            LuaValue chunk = loadFile(globals, filePath);
            LuaValue result = chunk.call();
            System.out.println("Result: " + result);
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        } catch (LuaError e) {
            System.err.println("Error running Lua script: " + e.getMessage());
        }
    }
}
