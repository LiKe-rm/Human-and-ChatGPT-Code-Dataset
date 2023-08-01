import org.lwjgl.opengl.GL11;
import org.lwjgl.util.vector.Vector2f;
import java.util.ArrayList;
import java.util.List;

public class OfxMultiscreen {

    private static boolean master = true;
    private static String appName = "";
    private static String appDirectory = "";
    private static String hostname = "";
    private static MultiCard card;
    private static int display = 0;
    private static MultiScreen localScreen;
    private static List<MultiComputer> computers = new ArrayList<>();

    private static OfTrueTypeFont font;
    private static boolean powersave = true;
    private static boolean debug = true;
    private static Vector2f maxSize = new Vector2f();
    private static boolean hasMaxSize = false;

    public static void multiLoad() {
        // Fill in the implementation here
    }

    public static void loadScreens(OfxXmlSettings settings) {
        // Fill in the implementation here
    }

    public static void multiSetup() {
        // Fill in the implementation here
    }

    public static void startScreens() {
        // Fill in the implementation here
    }

    public static void stopScreens() {
        // Fill in the implementation here
    }

    public static void execute(String command) {
        // Fill in the implementation here
    }

    public static void executeDisplay(String command) {
        // Fill in the implementation here
    }

    public static void launch(String appName) {
        // Fill in the implementation here
    }

    public static Vector2f getMaxSize() {
        // Fill in the implementation here
        return new Vector2f();
    }

    public static void draw() {
        // Fill in the implementation here
    }

    public static void drawScreen() {
        // Fill in the implementation here
    }

    public static void drawDebug() {
        // Fill in the implementation here
    }

    public static String getHostname() {
        // Fill in the implementation here
        return "";
    }

    public static int getDisplay() {
        // Fill in the implementation here
        return 0;
    }

    public static float ofGetWidthLocal() {
        return MultiScreen.getSize().x;
    }

    public static float ofGetHeightLocal() {
        return MultiScreen.getSize().y;
    }
}
