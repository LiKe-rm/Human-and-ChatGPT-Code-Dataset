import org.luaj.vm2.Globals;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.lib.jse.JsePlatform;

public class BasicBlock {
    private String name;

    public BasicBlock(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static class LuaBasicBlock extends LuaValue {
        private BasicBlock basicBlock;

        public LuaBasicBlock(BasicBlock basicBlock) {
            this.basicBlock = basicBlock;
        }

        @Override
        public int type() {
            return LuaValue.TUSERDATA;
        }

        @Override
        public String typename() {
            return "BasicBlock";
        }

        @Override
        public Object userdata() {
            return basicBlock;
        }
    }

    public static void main(String[] args) {
        Globals globals = JsePlatform.standardGlobals();
        LuaValue luaBasicBlockConstructor = new LuaBasicBlock(null) {
            @Override
            public LuaValue call(LuaValue arg) {
                return new LuaBasicBlock(new BasicBlock(arg.checkjstring()));
            }
        };

        globals.set("BasicBlock", luaBasicBlockConstructor);
        LuaValue chunk = globals.load("local bb = BasicBlock('example')\n" +
                "print(bb:getName())\n" +
                "bb:setName('new_example')\n" +
                "print(bb:getName())");
        chunk.call();
    }
}
