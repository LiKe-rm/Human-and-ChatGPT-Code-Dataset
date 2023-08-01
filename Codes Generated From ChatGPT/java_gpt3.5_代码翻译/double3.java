import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import javax.swing.*;

public class RulerPanel extends JPanel implements MouseListener, MouseMotionListener {
    private static final long serialVersionUID = 1L;

    public static final int MODE_INCH = 0;
    public static final int MODE_METRIC = 1;

    private int mode;
    private int margin;
    private int physicalInch;
    private ArrayList<Integer> tabStops;

    public RulerPanel() {
        mode = MODE_METRIC;
        margin = 0;
        tabStops = new ArrayList<>();
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    public void setMode(int mode) {
        this.mode = mode;
        repaint();
    }

    public int getMode() {
        return mode;
    }

    public void setMargin(int margin) {
        this.margin = margin;
        repaint();
    }

    public void setTabStops(ArrayList<Integer> tabStops) {
        this.tabStops = new ArrayList<>(tabStops);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g.create();
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        Rectangle bounds = getBounds();
        physicalInch = Toolkit.getDefaultToolkit().getScreenResolution();

        g2d.setColor(Color.WHITE);
        g2d.fillRect(bounds.x, bounds.y, bounds.width, bounds.height);

        g2d.setColor(Color.BLACK);
        g2d.setFont(new Font("SansSerif", Font.PLAIN, 10));

        drawRuler(g2d, bounds);
        g2d.dispose();
    }

    private void drawRuler(Graphics2D g2d, Rectangle bounds) {
        int startPoint = margin - 2;
        int midPoint = bounds.height / 2;

        if (mode == MODE_INCH) {
            // Implement inch ruler drawing
        } else {
            int cm = (int) (physicalInch / 2.54 + 0.5);
            int cmHalf = (int) (cm / 2.0);

            for (int i = startPoint + cmHalf; i < bounds.width - margin; i += cmHalf) {
                g2d.drawLine(i, midPoint - 1, i, midPoint + 2);
            }

            for (int i = startPoint + cm, count = 1; i < bounds.width - margin; i += cm, count++) {
                String num = String.valueOf(count);
                Rectangle2D rect = g2d.getFontMetrics().getStringBounds(num, g2d);
                g2d.drawString(num, i - (int) rect.getWidth() / 2, midPoint - 6);
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {
        getParent().dispatchEvent(new RulerActionEvent(this, RulerActionEvent.ACTION_DOWN, e.getPoint()));
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        getParent().dispatchEvent(new RulerActionEvent(this, RulerActionEvent.ACTION_UP, e.getPoint()));
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseDragged(MouseEvent e) {
    }

    @Override
    public void mouseMoved(MouseEvent e){
    }
}