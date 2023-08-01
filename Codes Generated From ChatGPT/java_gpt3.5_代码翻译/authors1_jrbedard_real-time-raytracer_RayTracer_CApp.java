import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.image.BufferedImage;

public class CApp {
    private boolean runGame;
    private int glWidth;
    private int glHeight;
    private CPoint3 viewPosition;
    private float yaw;
    private float pitch;
    private float roll;
    private int oldMouseX;
    private int oldMouseY;
    private int mouseX;
    private int mouseY;
    private int posX;
    private int posY;

    private boolean wireframe;
    private boolean cRaytraced;
    private boolean showHelp;
    private boolean useHardware;
    private boolean showMask;
    private boolean saveTGA;

    public CApp() {
        runGame = true;
        glWidth = 0;
        glHeight = 0;
        viewPosition = new CPoint3(60, -47, 41);
        yaw = -44.0f;
        pitch = -71.0f;
        roll = 0.0f;
        oldMouseX = 0;
        oldMouseY = 0;
        mouseX = 0;
        mouseY = 0;
        posX = 0;
        posY = 0;

        wireframe = false;
        cRaytraced = true;
        showHelp = false;
        useHardware = false;
        showMask = false;
        saveTGA = false;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            CAppFrame frame = new CAppFrame();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
        });
    }
}

class CAppFrame extends JFrame {
    private final CAppView cAppView;

    public CAppFrame() {
        setTitle("CApp");
        setSize(800, 600);

        cAppView = new CAppView();
        add(cAppView);

        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                cAppView.resize(getWidth(), getHeight());
            }
        });
    }
}

class CAppView extends JPanel {
    private BufferedImage screenTexture;

    public CAppView() {
        // TODO: Add the view's initialization code here
    }

    public void resize(int width, int height) {
        screenTexture = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // TODO: Add the view's drawing code here
    }
}

class CPoint3 {
    public float x, y, z;

    public CPoint3(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
}
