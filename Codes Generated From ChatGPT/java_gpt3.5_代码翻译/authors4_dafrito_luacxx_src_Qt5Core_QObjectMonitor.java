import java.util.function.Consumer;

public class QObjectMonitor {
    private QObject object;
    private LuaUserdata userdata;
    private boolean destroyOnGC;

    public QObjectMonitor(QObject object, LuaUserdata userdata) {
        if (!userdata.isManaged()) {
            throw new IllegalStateException("Refusing to manage a non-managed userdata");
        }

        this.object = object;
        this.userdata = userdata;
        this.destroyOnGC = false;

        // Watch for destruction from Java side
        object.connect("destroyed", this::destroyedFromJava);

        // Watch for destruction from Lua
        userdata.setManager(this::destroyedFromLua);
    }

    public void destroyedFromJava(Object obj) {
        if (userdata == null) {
            // Already destroyed from Lua
            assert object == null;
            return;
        }
        object = null;
        if (userdata != null) {
            LuaUserdata tmp = userdata;
            userdata = null;
            tmp.reset();
        }
    }

    public void destroyedFromLua() {
        if (object == null) {
            // Already destroyed from Java side
            assert userdata == null;
            return;
        }
        userdata = null;
        if (destroyOnGC && object != null) {
            QObject tmp = object;
            object = null;
            tmp = null; // In Java, setting an object to null is equivalent to delete in C++
        }
    }

    public void setDestroyOnGC(boolean destroy) {
        this.destroyOnGC = destroy;
        if (userdata == null) {
            destroyedFromLua();
        }
    }

    @Override
    protected void finalize() throws Throwable {
        destroyedFromJava(null);
        super.finalize();
    }
}

class LuaUserdata {
    private boolean managed;
    private Consumer<Void> manager;

    public boolean isManaged() {
        return managed;
    }

    public void setManaged(boolean managed) {
        this.managed = managed;
    }

    public void setManager(Consumer<Void> manager) {
        this.manager = manager;
    }

    public void reset() {
        // Reset the userdata object
    }
}
