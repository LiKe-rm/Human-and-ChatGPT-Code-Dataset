import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ToolTipEx extends JDialog {
    private static final int MARGIN = 5;

    private JTextPane textPane;
    private Font toolTipFont;
    private ImageIcon imageIcon;

    public ToolTipEx(JFrame parent) {
        super(parent, false);
        setUndecorated(true);
        setAlwaysOnTop(true);

        textPane = new JTextPane();
        textPane.setEditable(false);
        textPane.setBackground(SystemColor.info);
        textPane.setContentType("text/html");

        JScrollPane scrollPane = new JScrollPane(textPane);
        getContentPane().add(scrollPane);

        toolTipFont = UIManager.getFont("ToolTip.font");

        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                updateTextPaneSize();
            }
        });

        addWindowFocusListener(new WindowAdapter() {
            @Override
            public void windowLostFocus(WindowEvent e) {
                setVisible(false);
            }
        });
    }

    public void show(Point location) {
        setLocation(location);
        pack();
        setVisible(true);
    }

    public void hideToolTip() {
        setVisible(false);
    }

    public void setText(String text) {
        textPane.setText(text);
    }

    public void setImageIcon(ImageIcon icon) {
        this.imageIcon = icon;
        updateTextPaneSize();
    }

    private void updateTextPaneSize() {
        int width = getWidth() - (imageIcon != null ? imageIcon.getIconWidth() : 0) - 2 * MARGIN;
        int height = getHeight() - 2 * MARGIN;

        textPane.setSize(new Dimension(width, height));
        textPane.setPreferredSize(new Dimension(width, height));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (imageIcon != null) {
            g.drawImage(imageIcon.getImage(), MARGIN, MARGIN, this);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame parentFrame = new JFrame("Test");
            parentFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            parentFrame.setSize(300, 200);
            parentFrame.setLocationRelativeTo(null);
            parentFrame.setVisible(true);

            ToolTipEx toolTipEx = new ToolTipEx(parentFrame);
            toolTipEx.setText("Sample tooltip text");
            toolTipEx.setImageIcon(new ImageIcon("path/to/your/image.png"));

            JButton showButton = new JButton("Show Tooltip");
            showButton.addActionListener(e -> {
                Point location = parentFrame.getLocationOnScreen();
                location.translate(50, 50);
                toolTipEx.show(location);
            });

            parentFrame.getContentPane().add(showButton, BorderLayout.CENTER);
        });
    }
}
