import javax.swing.*;
import java.awt.*;

public class TextViewFont extends JPanel {
    private JTextArea textArea;
    private JScrollPane scrollPane;
    private Font defaultFont;
    private int lineHeight;
    private int maxAscent;
    private int heightAbove;
    private int heightBelow;

    public TextViewFont() {
        setLayout(new BorderLayout());

        textArea = new JTextArea();
        scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        defaultFont = textArea.getFont();
        heightAbove = 0;
        heightBelow = 0;
        recalcLineHeight();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("TextViewFont");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(600, 400);

            TextViewFont textViewFont = new TextViewFont();
            frame.add(textViewFont);

            frame.setVisible(true);
        });
    }

    private void recalcLineHeight() {
        FontMetrics fm = textArea.getFontMetrics(defaultFont);
        lineHeight = fm.getHeight();
        maxAscent = fm.getAscent();

        lineHeight += heightAbove + heightBelow;
    }

    public void setFont(Font font) {
        defaultFont = font;
        textArea.setFont(defaultFont);
        recalcLineHeight();
        updateMarginWidth();
    }

    public void addFont(Font font) {
        setFont(font);
        updateMetrics();
    }

    private void updateMarginWidth() {
        // Implement any additional logic related to margin width updates
    }

    private void updateMetrics() {
        recalcLineHeight();
    }

    public void setLineSpacing(int above, int below) {
        heightAbove = above;
        heightBelow = below;
        recalcLineHeight();
    }
}
