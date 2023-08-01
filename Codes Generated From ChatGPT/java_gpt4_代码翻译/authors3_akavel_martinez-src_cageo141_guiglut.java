import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.Path2D;
import java.util.ArrayList;

public class PolygonVisualization extends JFrame implements KeyListener {

    private static final long serialVersionUID = 1L;
    private JPanel mainPanel;
    private boolean showSubject = true;
    private boolean showClipping = true;
    private boolean showResult = false;

    private Polygon subjectPolygon;
    private Polygon clippingPolygon;
    private Polygon resultPolygon;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            PolygonVisualization app = new PolygonVisualization();
            app.setVisible(true);
        });
    }

    public PolygonVisualization() {
        setTitle("Polygon Visualization");
        setSize(700, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        init();
    }

    private void init() {
        mainPanel = new JPanel() {
            private static final long serialVersionUID = 1L;

            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

                if (showSubject) {
                    g2d.setColor(new Color(0, 255, 0, 255));
                    g2d.fill(subjectPolygon);
                    g2d.setColor(Color.BLACK);
                    g2d.draw(subjectPolygon);
                }

                if (showClipping) {
                    g2d.setColor(new Color(255, 0, 0, 85));
                    g2d.fill(clippingPolygon);
                    g2d.setColor(Color.BLACK);
                    g2d.draw(clippingPolygon);
                }

                if (showResult) {
                    g2d.setColor(Color.BLUE);
                    g2d.fill(resultPolygon);
                    g2d.setColor(Color.BLACK);
                    g2d.draw(resultPolygon);
                }
            }
        };

        setContentPane(mainPanel);
        mainPanel.addKeyListener(this);
        mainPanel.setFocusable(true);

        subjectPolygon = createSamplePolygon(50, 50);
        clippingPolygon = createSamplePolygon(100, 100);
        resultPolygon = createSamplePolygon(75, 75);
    }

    private Polygon createSamplePolygon(int offsetX, int offsetY) {
        Polygon polygon = new Polygon();
        polygon.addPoint(offsetX + 0, offsetY + 0);
        polygon.addPoint(offsetX + 100, offsetY + 0);
        polygon.addPoint(offsetX + 100, offsetY + 100);
        polygon.addPoint(offsetX + 0, offsetY + 100);
        return polygon;
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        switch (e.getKeyChar()) {
            case 'R':
            case 'r':
                showResult = !showResult;
                mainPanel.repaint();
                break;
            case 'S':
            case 's':
                showSubject = !showSubject;
                mainPanel.repaint();
                break;
            case 'C':
            case 'c':
                showClipping = !showClipping;
                mainPanel.repaint();
                break;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }
}
