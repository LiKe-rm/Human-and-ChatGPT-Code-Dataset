import org.luaj.vm2.Globals;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.lib.jse.JsePlatform;

public class BranchInst {
    private String name;

    public BranchInst(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static class LuaBranchInst extends LuaValue {
        private BranchInst branchInst;

        public LuaBranchInst(BranchInst branchInst) {
            this.branchInst = branchInst;
        }

        @Override
        public int type() {
            return LuaValue.TUSERDATA;
        }

        @Override
        public String typename() {
            return "BranchInst";
        }

        @Override
        public Object userdata() {
            return branchInst;
        }
    }

    public static void main(String[] args) {
        Globals globals = JsePlatform.standardGlobals();
        LuaValue luaBranchInstConstructor = new LuaBranchInst(null) {
            @Override
            public LuaValue call(LuaValue arg) {
                return new LuaBranchInst(new BranchInst(arg.checkjstring()));
            }
        };

        globals.set("BranchInst", luaBranchInstConstructor);
        LuaValue chunk = globals.load("local bi = BranchInst('example')\n" +
                "print(bi:getName())\n" +
                "bi:setName('new_example')\n" +
                "print(bi:getName())");
        chunk.call();
    }
}
