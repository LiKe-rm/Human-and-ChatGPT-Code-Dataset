import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class GroupStatic extends JLabel {
    private Color textColor;
    private Color backgroundColor;

    public GroupStatic() {
        this.textColor = Color.BLACK;
        this.backgroundColor = Color.WHITE;
        setOpaque(false);
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentMoved(ComponentEvent e) {
                updateColors();
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        if (backgroundColor != null) {
            g.setColor(backgroundColor);
            g.fillRect(0, 0, getWidth(), getHeight());
        }
        super.paintComponent(g);
    }

    public void setTextColor(Color textColor) {
        this.textColor = textColor;
        setForeground(textColor);
    }

    public void setBackgroundColor(Color backgroundColor) {
        this.backgroundColor = backgroundColor;
        repaint();
    }

    private void updateColors() {
        Container parent = getParent();
        if (parent != null) {
            Point position = getLocation();
            SwingUtilities.convertPointToScreen(position, parent);
            Color parentBackground = new Color(Toolkit.getDefaultToolkit().getDesktopProperty("win.3d.backgroundColor").hashCode());
            setBackgroundColor(parentBackground);
        }
    }

    public void setFont(int pointSize, String faceName) {
        setFont(new Font(faceName, Font.PLAIN, pointSize));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("GroupStatic");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(300, 150);

            JPanel panel = new JPanel();
            GroupStatic groupStatic = new GroupStatic();
            groupStatic.setText("GroupStatic");
            groupStatic.setFont(12, "Arial");
            panel.add(groupStatic);
            frame.add(panel);

            frame.setVisible(true);
        });
    }
}
