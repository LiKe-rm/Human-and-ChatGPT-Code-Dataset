import javax.swing.*;
import java.awt.*;

public class StdGrfx {

    private static final Color SHADOW = SystemColor.controlShadow;
    private static final Color DARK_SHADOW = SystemColor.controlDkShadow;
    private static final Color LIGHT = SystemColor.controlLtHighlight;
    private static final Color HIGHLIGHT = SystemColor.controlHighlight;
    private static final Color DIALOG = SystemColor.control;
    private static final Color WINDOW = SystemColor.window;
    private static final Color SCROLLBAR = SystemColor.scrollbar;

    public static void draw3DFrame(Graphics g, Rectangle rect) {
        g.setColor(HIGHLIGHT);
        g.drawLine(rect.x, rect.y + rect.height - 1, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width - 1, rect.y);

        g.setColor(SHADOW);
        g.drawLine(rect.x, rect.y + rect.height - 1, rect.x + rect.width - 1, rect.y + rect.height - 1);
        g.drawLine(rect.x + rect.width - 1, rect.y + rect.height - 1, rect.x + rect.width - 1, rect.y);
    }

    public static void drawSunken3DFrame(Graphics g, Rectangle rect) {
        g.setColor(SHADOW);
        g.drawLine(rect.x, rect.y + rect.height - 1, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width - 1, rect.y);

        g.setColor(HIGHLIGHT);
        g.drawLine(rect.x, rect.y + rect.height - 1, rect.x + rect.width - 1, rect.y + rect.height - 1);
        g.drawLine(rect.x + rect.width - 1, rect.y + rect.height - 1, rect.x + rect.width - 1, rect.y);
    }

    public static void drawDoubleSunken3DFrame(Graphics g, Rectangle rect) {
        g.setColor(SHADOW);
        g.drawRect(rect.x, rect.y, rect.width - 1, rect.height - 1);

        g.setColor(DARK_SHADOW);
        g.drawRect(rect.x + 1, rect.y + 1, rect.width - 3, rect.height - 3);

        g.setColor(LIGHT);
        g.drawLine(rect.x + rect.width - 2, rect.y + 1, rect.x + rect.width - 2, rect.y + rect.height - 2);
        g.drawLine(rect.x + 1, rect.y + rect.height - 2, rect.x + rect.width - 2, rect.y + rect.height - 2);
    }

    public static void drawFramed3DBox(Graphics g, Rectangle rect) {
        g.setColor(DARK_SHADOW);
        g.fillRect(rect.x, rect.y, rect.width, rect.height);

        draw3DFrame(g, new Rectangle(rect.x + 1, rect.y + 1, rect.width - 2, rect.height - 2));
    }

    public static void drawSunkenFramed3DWindow(Graphics g, Rectangle rect) {
        g.setColor(WINDOW);
        g.fillRect(rect.x, rect.y, rect.width, rect.height);

        drawDoubleSunken3DFrame(g, rect);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("StdGrfx Example");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Rectangle rect1;
            }
        }
    }
}

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

public class StdGrfx {
    private static final BasicStroke stroke = new BasicStroke(1.0f);

    public static Color getShadowColor() {
        return UIManager.getColor("Panel.background").darker();
    }

    public static Color getDarkShadowColor() {
        return Color.BLACK;
    }

    public static Color getLightColor() {
        return UIManager.getColor("Panel.background").brighter();
    }

    public static Color getHighlightColor() {
        return Color.WHITE;
    }

    public static Color getDialogColor() {
        return UIManager.getColor("Panel.background");
    }

    public static Color getWindowColor() {
        return UIManager.getColor("window");
    }

    public static Color getScrollColor() {
        return UIManager.getColor("scrollbar");
    }

    public static void drawFramed3DBox(Graphics2D g, Rectangle rect) {
        g.setStroke(stroke);

        g.setColor(getDarkShadowColor());
        g.drawRect(rect.x, rect.y, rect.width, rect.height);
        rect.grow(-1, -1);
        draw3DFrame(g, rect);

        g.setColor(Color.BLACK);
    }

    public static void drawSunkenFramed3DWindow(Graphics2D g, Rectangle rect) {
        g.setColor(getWindowColor());
        g.fillRect(rect.x, rect.y, rect.width, rect.height);
        drawDoubleSunken3DFrame(g, rect);

        g.setColor(Color.BLACK);
    }

    public static void draw3DFrame(Graphics2D g, Rectangle rect) {
        rect.grow(0, 0);

        g.setColor(getHighlightColor());
        g.drawLine(rect.x, rect.y + rect.height, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width, rect.y);

        g.setColor(getShadowColor());
        g.drawLine(rect.x + rect.width, rect.y, rect.x + rect.width, rect.y + rect.height);
        g.drawLine(rect.x, rect.y + rect.height, rect.x + rect.width, rect.y + rect.height);

        g.setColor(Color.BLACK);
    }

    public static void drawSunken3DFrame(Graphics2D g, Rectangle rect) {
        rect.grow(0, 0);

        g.setColor(getShadowColor());
        g.drawLine(rect.x, rect.y + rect.height, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width, rect.y);

        g.setColor(getHighlightColor());
        g.drawLine(rect.x + rect.width, rect.y, rect.x + rect.width, rect.y + rect.height);
        g.drawLine(rect.x, rect.y + rect.height, rect.x + rect.width, rect.y + rect.height);

        g.setColor(Color.BLACK);
    }

    public static void drawDoubleSunken3DFrame(Graphics2D g, Rectangle rect) {
        rect.grow(0, 0);

        g.setColor(getShadowColor());
        g.drawLine(rect.x, rect.y + rect.height, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width, rect.y);

        g.setColor(getHighlightColor());
        g.drawLine(rect.x + rect.width, rect.y, rect.x + rect.width, rect.y + rect.height);
        g.drawLine(rect.x, rect.y + rect.height, rect.x + rect.width, rect.y + rect.height);

        rect.grow(-1, -1);
        g.setColor(getHighlightColor());
        g.drawLine(rect.x, rect.y + rect.height, rect.x, rect.y);
        g.drawLine(rect.x, rect.y, rect.x + rect.width, rect.y);

        g.setColor(getShadowColor());
        g.drawLine(rect.x + rect.width, rect.y, rect.x + rect.width, rect.y + rect.height);
        g.drawLine(rect.x, rect.y + rect.height, rect.x + rect.width, rect.y + rect.height);

        g.setColor(Color.BLACK);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("3D Frame Example");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            JPanel panel = new JPanel() {
                @Override
                protected void paintComponent(Graphics g) {
                    super.paintComponent(g);
                    Graphics2D g2d = (Graphics2D) g;
                    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

                    Rectangle rect1 = new Rectangle(50, 50, 100, 100);
                    Rectangle rect2 = new Rectangle(200, 50, 100, 100);
                    Rectangle rect3 = new Rectangle(50, 200, 100, 100);
                    Rectangle rect4 = new Rectangle(200, 200, 100, 100);

                    drawFramed3DBox(g2d, rect1);
                    drawSunkenFramed3DWindow(g2d, rect2);
                    draw3DFrame(g2d, rect3);
                    drawSunken3DFrame(g2d, rect4);
                }
            };

            frame.add(panel);
            frame.setSize(400, 400);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}
