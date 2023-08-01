import java.awt.*;
import java.awt.font.TextAttribute;
import java.text.AttributedString;
import javax.swing.*;

public class FormattedTextDraw {
    private String rtfText;
    private JTextPane textPane;

    public FormattedTextDraw() {
        textPane = new JTextPane();
        textPane.setOpaque(false);
        textPane.setEditable(false);
    }

    public String getRtfText() {
        return rtfText;
    }

    public void setRtfText(String rtfText) {
        this.rtfText = rtfText;
        textPane.setContentType("text/rtf");
        textPane.setText(rtfText);
    }

    public void draw(Graphics g, Rectangle bounds) {
        textPane.setBounds(bounds);
        textPane.paint(g);
    }

    public int getNaturalWidth(int height) {
        textPane.setSize(new Dimension(Integer.MAX_VALUE, height));
        return textPane.getPreferredSize().width;
    }

    public int getNaturalHeight(int width) {
        textPane.setSize(new Dimension(width, Integer.MAX_VALUE));
        return textPane.getPreferredSize().height;
    }

    public static void main(String[] args) {
        String exampleRtf = "{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\fnil\\fcharset0 Arial;}}{\\colortbl ;\\red0\\green0\\blue255;}\\pard\\cf1\\fs24 This is a test with blue color.\\par}";
        FormattedTextDraw formattedTextDraw = new FormattedTextDraw();
        formattedTextDraw.setRtfText(exampleRtf);

        JFrame frame = new JFrame("Formatted Text Draw Example");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                formattedTextDraw.draw(g, new Rectangle(50, 50, 300, 200));
            }
        };

        frame.add(panel);
        frame.setVisible(true);
    }
}
