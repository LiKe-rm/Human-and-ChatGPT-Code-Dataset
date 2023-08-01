import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;
import org.lwjgl.system.*;

import java.nio.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLongArray;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryStack.*;
import static org.lwjgl.system.MemoryUtil.*;

public class MonitorSync {
    private static final int WINDOW_WIDTH = 64;
    private static final int WINDOW_HEIGHT = 64;
    private static final int MAX_WINDOWS = 16;
    private static final int NUM_VBLANK_SLOTS = 100;
    private static final int SLOT_CONFIDENCE = 50;

    private static int numWindows;
    private static TestWindow[] windows;

    public static void main(String[] args) {
        windows = new TestWindow[MAX_WINDOWS];
        numWindows = args.length;

        for (int i = 0; i < numWindows; i++) {
            String[] coordinates = args[i].split("x");
            int x = Integer.parseInt(coordinates[0]);
            int y = Integer.parseInt(coordinates[1]);
            windows[i] = new TestWindow(i, x, y);
            windows[i].run();
        }

        for (int i = 0; i < numWindows; i++) {
            windows[i].wait();
        }

        System.out.println("Shutting Down");
    }

    private static class TestWindow {
        private final int index;
        private final int x;
        private final int y;
        private long window;

        private static AtomicInteger numStarted = new AtomicInteger(0);
        private static AtomicBoolean allStarted = new AtomicBoolean(false);
        private static AtomicLongArray times = new AtomicLongArray(MAX_WINDOWS);

        private Thread thread;

        public TestWindow(int index, int x, int y) {
            this.index = index;
            this.x = x;
            this.y = y;
        }

        public void run() {
            thread = new Thread(this::runLoop);
            thread.start();
        }

        public void wait() {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void runLoop() {
            if (!glfwInit()) {
                throw new IllegalStateException("Unable to initialize GLFW");
            }

            glfwDefaultWindowHints();
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Monitor Sync", NULL, NULL);
            if (window == NULL) {
                throw new RuntimeException("Failed to create the GLFW window");
            }

            glfwSetWindowPos(window, x, y);

            try (MemoryStack stack = stackPush()) {
                IntBuffer pWidth = stack.mallocInt(1);
                IntBuffer pHeight = stack.mallocInt(1);

                glfwGetWindowSize(window, pWidth, pHeight);
                GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

                glfwSetWindowPos(window, (vidmode.width() - pWidth.get(0)) / 2,
                        (vidmode.height() - pHeight.get(0)) / 2);
            }

            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);
            glfwShowWindow(window);

            GL.createCapabilities();

        }
    }
}
