import com.jogamp.opengl.*;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.FPSAnimator;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

public class MonitorSync {
    private static final int WINDOW_WIDTH = 64;
    private static final int WINDOW_HEIGHT = 64;
    private static final int MAX_WINDOWS = 16;

    private static final int NUM_VBLANK_SLOTS = 100;
    private static final int SLOT_CONFIDENCE = 50;

    public static void main(String[] args) {
        final int numWindows = args.length;

        TestWindow[] windows = new TestWindow[MAX_WINDOWS];
        AtomicInteger numStarted = new AtomicInteger(0);
        AtomicBoolean allStarted = new AtomicBoolean(false);
        AtomicLong[] times = new AtomicLong[MAX_WINDOWS];
        for (int i = 0; i < numWindows; i++) {
            int x = Integer.parseInt(args[i].split("x")[0]);
            int y = Integer.parseInt(args[i].split("x")[1]);
            times[i] = new AtomicLong(0);
            windows[i] = new TestWindow(i, x, y, numStarted, allStarted, times);
            windows[i].setVisible(true);
        }

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            for (int i = 0; i < numWindows; i++) {
                if (windows[i] != null) {
                    windows[i].dispose();
                }
            }
        }));
    }

    private static class TestWindow extends JFrame {
        private final int index;
        private final AtomicInteger numStarted;
        private final AtomicBoolean allStarted;
        private final AtomicLong[] times;
        private final GLCanvas canvas;

        TestWindow(int index, int x, int y, AtomicInteger numStarted, AtomicBoolean allStarted, AtomicLong[] times) {
            this.index = index;
            this.numStarted = numStarted;
            this.allStarted = allStarted;
            this.times = times;

            setTitle("Test Window " + index);
            setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
            setLocation(x, y);
            setUndecorated(true);
            setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

            GLCapabilities capabilities = new GLCapabilities(GLProfile.get(GLProfile.GL2));
            capabilities.setDoubleBuffered(true);
            canvas = new GLCanvas(capabilities);
            canvas.addGLEventListener(new GLEventListenerImpl());
            getContentPane().add(canvas);

            addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    super.windowClosing(e);
                    System.exit(0);
                }
            });

            FPSAnimator animator = new FPSAnimator(canvas, 60);
            animator.start();
        }

        private class GLEventListenerImpl implements GLEventListener {
            @Override
            public void init(GLAutoDrawable drawable) {
                GL2 gl = drawable.getGL().getGL2();
                gl.glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
            }

            @Override
            public void dispose(GLAutoDrawable drawable) {
            }

            @Override
            public void display(GLAutoDrawable drawable) {
                GL2 gl = drawable.getGL().getGL2();
                gl.glClear(GL.GL_COLOR_BUFFER_BIT);

                long now = System.nanoTime();
                if (!allStarted.get()) {
                    if (numStarted.incrementAndGet() >= SLOT_CONFIDENCE) {
                        allStarted.set(true);
                    }
                } else {
                    long time = now - times[index].getAndSet(now);
                    System.out.printf("Window %d: %d ns\n", index, time);
                }
            }

            @Override
            public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
                GL2 gl = drawable.getGL().getGL2();
                gl.glMatrixMode(GL2.GL_PROJECTION);
                gl.glLoadIdentity();
                gl.glOrtho(0, width, height, 0, -1, 1);
                gl.glMatrixMode(GL2.GL_MODELVIEW);
                gl.glLoadIdentity();
                gl.glViewport(0, 0, width, height);
            }
        }
    }
}
