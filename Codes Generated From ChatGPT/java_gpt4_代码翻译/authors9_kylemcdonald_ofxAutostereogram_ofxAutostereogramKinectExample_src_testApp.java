import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class TestApp extends JPanel {
    private final ControlPanel panel;
    private final Kinect kinect;
    private final BufferedImage tile;
    private final BufferedImage sis;
    private final BufferedImage kinectDepth;

    public TestApp() throws IOException {
        panel = new ControlPanel();
        kinect = new Kinect();
        kinect.init();
        kinect.open();

        tile = ImageIO.read(new File("tile.png"));
        BufferedImage resizedTile = new BufferedImage(128, 128, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = resizedTile.createGraphics();
        g.drawImage(tile, 0, 0, 128, 128, null);
        g.dispose();

        sis = new BufferedImage(640 + 128, 480, BufferedImage.TYPE_INT_RGB);
        kinectDepth = new BufferedImage(640, 480, BufferedImage.TYPE_BYTE_GRAY);
    }

    public void update() {
        boolean newMultiplier = panel.hasValueChanged("depthMultiplier");

        if (panel.hasValueChanged("nearClipping") || panel.hasValueChanged("farClipping")) {
            kinect.setDepthClipping(
                    panel.getValueF("nearClipping") * 10,
                    panel.getValueF("farClipping") * 10);
        }

        kinect.update();

        kinectDepth.getRaster().setPixels(0, 0, 640, 480, kinect.getDepthPixels());
        // Assuming the existence of an Autostereogram class with a makeAutostereogram method
        if (panel.getValueB("realtime") || panel.getValueB("snapshot") || newMultiplier) {
            float depthMultiplier = (float) mouseX / ofGetWidth();
            Autostereogram.makeAutostereogram(tile, kinectDepth, panel.getValueF("depthMultiplier"), sis);
            panel.setValueB("snapshot", false);
        }

        if (panel.getValueB("export")) {
            String time = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd 'at' HH.mm.ss"));
            File outputFile = new File("Autostereogram Export " + time + ".png");
            try {
                ImageIO.write(sis, "png", outputFile);
            } catch (IOException e) {
                e.printStackTrace();
            }
            panel.setValueB("export", false);
        }

        panel.clearAllChanged();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.GRAY);
        g.fillRect(0, 0, getWidth(), getHeight());

        g.setColor(Color.WHITE);
        g.drawImage(kinectDepth, 128, 0, null);
        g.drawImage(sis, 0, 480, null);
    }

    public void exit() {
        kinect.close();
    }

    public static void main(String[] args) throws IOException {
        JFrame frame = new JFrame("TestApp");
        TestApp testApp = new TestApp();
        frame.add(testApp);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(640 + 128, 480);
        frame.setVisible(true);

        while (true) {
            testApp.update();
            testApp.repaint();
        }
    }
}

// Implement the ControlPanel, Kinect, and Autostereogram classes here.
