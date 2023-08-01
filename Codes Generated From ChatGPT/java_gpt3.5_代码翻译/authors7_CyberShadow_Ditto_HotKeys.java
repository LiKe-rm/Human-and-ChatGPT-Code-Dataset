import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import javax.swing.KeyStroke;

public class HotKeys {
    private static int nextId = 0;
    private static ArrayList<HotKey> hotKeys = new ArrayList<>();
    private String name;
    private int key;
    private boolean isRegistered;
    private boolean unregisterOnShowDitto;
    private int clipId;
    private int globalId;

    public HotKeys(String name, int defaultKey, boolean unregisterOnShowDitto) {
        this.name = name;
        this.isRegistered = false;
        this.unregisterOnShowDitto = unregisterOnShowDitto;
        this.clipId = 0;
        this.key = defaultKey;
        this.globalId = nextId++;
        hotKeys.add(this);
    }

    public static String getHotKeyDisplay(int key) {
        return KeyStroke.getKeyStroke(key).toString().replace("pressed ", "");
    }

    public static String getVirtualKeyName(int keyCode) {
        return KeyEvent.getKeyText(keyCode);
    }

    public static int getModifier(int key) {
        int modifier = 0;
        if ((key & InputEvent.SHIFT_DOWN_MASK) != 0) {
            modifier |= KeyEvent.SHIFT_DOWN_MASK;
        }
        if ((key & InputEvent.CTRL_DOWN_MASK) != 0) {
            modifier |= KeyEvent.CTRL_DOWN_MASK;
        }
        if ((key & InputEvent.ALT_DOWN_MASK) != 0) {
            modifier |= KeyEvent.ALT_DOWN_MASK;
        }
        if ((key & InputEvent.META_DOWN_MASK) != 0) {
            modifier |= KeyEvent.META_DOWN_MASK;
        }
        return modifier;
    }

    public void setKey(int key) {
        if (this.key == key) {
            return;
        }
        this.key = key;
    }

    public boolean register() {
        if (this.key != 0) {
            this.isRegistered = true;
        } else {
            this.isRegistered = false;
        }
        return this.isRegistered;
    }

    public boolean unregister(boolean onShowingDitto) {
        if (!this.isRegistered) {
            return true;
        }
        if (onShowingDitto && !this.unregisterOnShowDitto) {
            return true;
        }
        if (this.key != 0) {
            this.isRegistered = false;
            return true;
        } else {
            this.isRegistered = false;
            return true;
        }
    }

    public static void registerAll() {
        for (HotKey hotKey : hotKeys) {
            hotKey.register();
        }
    }

    public static void unregisterAll(boolean onShowDitto) {
        for (HotKey hotKey : hotKeys) {
            hotKey.unregister(onShowDitto);
        }
    }

    public static boolean findFirstConflict() {
        Map<Integer, Integer> keys = new HashMap<>();
        for (HotKey hotKey : hotKeys) {
            int key = hotKey.key;
            if (keys.containsKey(key)) {
                return true;
            } else {
                keys.put(key, 1);
            }
        }
        return false;
    }

    public static void main(String[] args) {
        HotKeys hotKey1 = new HotKeys("hotkey1", KeyEvent.VK_A | KeyEvent.CTRL_DOWN_MASK, false);
        HotKeys hotKey2 = new HotKeys("hotkey2", KeyEvent.VK_B | KeyEvent.CTRL_DOWN_MASK, false);
        HotKeys hotKey3 = new HotKeys("hotkey3", KeyEvent.VK_C | KeyEvent.CTRL_DOWN_MASK, false);
    }
}
