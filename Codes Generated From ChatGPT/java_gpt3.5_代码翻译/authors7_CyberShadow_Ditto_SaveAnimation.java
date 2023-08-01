import java.awt.Rectangle;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.EventQueue;

public class SaveAnimation {
    private double leftPercent = 0;
    private double topPercent = 0;
    private double rightPercent = 0;
    private double bottomPercent = 0;
    private double speed = 40;

    public SaveAnimation() {
    }

    public void doAnimation(Rectangle startRect, Rectangle endRect, JPanel panel) {
        Rectangle currentRect = new Rectangle(startRect);
        Rectangle previousRect = new Rectangle(-1, -1, -1, -1);
        long maxDistance = getMaxDistance(startRect, endRect);
        getPercentages(maxDistance, startRect, endRect);

        double currentLeft = currentRect.getX();
        double currentTop = currentRect.getY();
        double currentRight = currentRect.getMaxX();
        double currentBottom = currentRect.getMaxY();

        for (int i = 0; i < maxDistance / speed; i++) {
            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Graphics g = panel.getGraphics();
            g.setXORMode(Color.WHITE);

            if (i > 0) {
                g.drawRect(previousRect.x, previousRect.y, previousRect.width, previousRect.height);
            }

            g.drawRect(currentRect.x, currentRect.y, currentRect.width, currentRect.height);
            g.setPaintMode();

            previousRect.setBounds(currentRect);

            currentLeft -= leftPercent * speed;
            currentTop -= topPercent * speed;
            currentRight -= rightPercent * speed;
            currentBottom -= bottomPercent * speed;

            currentRect.setBounds((int) currentLeft, (int) currentTop, (int) (currentRight - currentLeft), (int) (currentBottom - currentTop));
        }
    }

    private long getMaxDistance(Rectangle startRect, Rectangle endRect) {
        long max = 0;

        max = Math.max(max, Math.abs(startRect.x - endRect.x));
        max = Math.max(max, Math.abs(startRect.y - endRect.y));
        max = Math.max(max, Math.abs(startRect.width - endRect.width));
        max = Math.max(max, Math.abs(startRect.height - endRect.height));

        return max;
    }

    private void getPercentages(long maxDist, Rectangle startRect, Rectangle endRect) {
        if (maxDist > 0) {
            leftPercent = (double) (startRect.x - endRect.x) / maxDist;
            topPercent = (double) (startRect.y - endRect.y) / maxDist;
            rightPercent = (double) (startRect.width - endRect.width) / maxDist;
            bottomPercent = (double) (startRect.height - endRect.height) / maxDist;
        }
    }

    public static void main(String[] args) {
        SaveAnimation animation = new SaveAnimation();
        Rectangle startRect = new Rectangle(50, 50, 100, 100);
        Rectangle endRect = new Rectangle(200, 200, 50, 50);

        JFrame frame = new JFrame("Save Animation Example");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
            }
        };

        frame.add(panel);
        frame.setSize(400, 400);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

        EventQueue.invokeLater(() -> {
            animation.doAnimation(startRect, endRect, panel);
        });
    }
}
