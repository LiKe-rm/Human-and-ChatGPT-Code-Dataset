import com.jogamp.opengl.*;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.awt.AWTTextureIO;
import org.libsdl4j.SDL;
import org.libsdl4j.SDLException;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;

public class Slideshow implements GLEventListener {
    private int width = 800;
    private int height = 600;
    private String name = "fade";
    private boolean automatic = true;
    private boolean fullscreen = false;
    private float s = 0.0f;

    private Texture[] textures = new Texture[2];
    private int activeTexture = 0;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Slideshow slideshow = new Slideshow();
            slideshow.setup();
        });
    }

    private void setup() {
        try {
            SDL.init(SDL.SDL_INIT_VIDEO);
        } catch (SDLException e) {
            e.printStackTrace();
            System.exit(1);
        }

        GLProfile profile = GLProfile.get(GLProfile.GL2);
        GLCapabilities capabilities = new GLCapabilities(profile);
        GLCanvas canvas = new GLCanvas(capabilities);
        canvas.addGLEventListener(this);

        final JFrame frame = new JFrame(name);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(new BorderLayout());
        frame.getContentPane().add(canvas, BorderLayout.CENTER);
        frame.setSize(width, height);
        frame.setLocationRelativeTo(null);

        if (fullscreen) {
            frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
            frame.setUndecorated(true);
        }

        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        canvas.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (automatic) {
                    s = 0.0f;
                    loadNextImage();
                }
            }
        });

        frame.setVisible(true);
    }

    @Override
    public void init(GLAutoDrawable drawable) {
        GL2 gl = drawable.getGL().getGL2();

        gl.glEnable(GL.GL_TEXTURE_2D);

        gl.glClearColor(0, 0, 0, 1);
        gl.glViewport(0, 0, width, height);

        gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
        gl.glLoadIdentity();
        GLU glu = new GLU();
        glu.gluOrtho2D(0        0, width, height);

        gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);
        gl.glLoadIdentity();

        loadNextImage();

        animator = new FPSAnimator(drawable, 60);
        animator.start();
    }

    @Override
    public void display(GLAutoDrawable drawable) {
        GL2 gl = drawable.getGL().getGL2();

        gl.glClear(GL.GL_COLOR_BUFFER_BIT);

        if (automatic) {
            s += 0.01f;
            if (s >= 1.0f) {
                s = 0.0f;
                loadNextImage();
            }
        }

        gl.glLoadIdentity();
        gl.glColor3f(1, 1, 1);
        gl.glBindTexture(GL.GL_TEXTURE_2D, texture[0]);

        gl.glBegin(GL2.GL_QUADS);
        gl.glTexCoord2f(0, 0);
        gl.glVertex2f(0, 0);
        gl.glTexCoord2f(1, 0);
        gl.glVertex2f(width, 0);
        gl.glTexCoord2f(1, 1);
        gl.glVertex2f(width, height);
        gl.glTexCoord2f(0, 1);
        gl.glVertex2f(0, height);
        gl.glEnd();

        gl.glFlush();
    }

    private void loadNextImage() {
        if (currentImage == imagePaths.length - 1) {
            currentImage = 0
        } else {
            currentImage++;
        }
    
        BufferedImage image = null;
        try {
            image = ImageIO.read(new File(imagePaths[currentImage]));
        } catch (IOException e) {
            e.printStackTrace();
        }
    
        int[] pixels = new int[image.getWidth() * image.getHeight()];
        image.getRGB(0, 0, image.getWidth(), image.getHeight(), pixels, 0, image.getWidth());
    
        IntBuffer buffer = IntBuffer.wrap(pixels);
        buffer.position(0);
        buffer.limit(pixels.length);
    
        GLContext.getCurrentGL().glBindTexture(GL.GL_TEXTURE_2D, texture[0]);
        GLContext.getCurrentGL().glTexImage2D(GL.GL_TEXTURE_2D, 0, GL.GL_RGBA, image.getWidth(), image.getHeight(), 0, GL2.GL_BGRA, GL.GL_UNSIGNED_BYTE, buffer);
    }
    
    @Override
    public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
    }
    
    @Override
    public void dispose(GLAutoDrawable drawable) {
        if (animator != null) {
            animator.stop();
        }
    }
    
    public static void main(String[] args) {
        GLProfile.initSingleton();
        GLProfile glProfile = GLProfile.get(GLProfile.GL2);
        GLCapabilities glCapabilities = new GLCapabilities(glProfile);
        GLCanvas glCanvas = new GLCanvas(glCapabilities);
    
        SimpleSlideshow simpleSlideshow = new SimpleSlideshow();
        glCanvas.addGLEventListener(simpleSlideshow);
        glCanvas.addKeyListener(simpleSlideshow);
        JFrame frame = new JFrame("Simple Slideshow");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 400);
        frame.setContentPane(glCanvas);
        frame.setVisible(true);
    
        simpleSlideshow.animator = new FPSAnimator(glCanvas, 60);
        simpleSlideshow.animator.start();
    }
}        
           
