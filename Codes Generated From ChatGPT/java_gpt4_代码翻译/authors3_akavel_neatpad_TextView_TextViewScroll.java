import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TextView extends JScrollPane {
    private static final int LEFT_MARGIN_WIDTH = 32;
    private int fontWidth;
    private int lineHeight;
    private int windowLines;
    private int windowColumns;
    private int longestLine;
    private int lineCount;
    private int vScrollPos;
    private int hScrollPos;
    private JTextArea textArea;

    public TextView(JTextArea textArea) {
        super(textArea);
        this.textArea = textArea;
        FontMetrics fm = textArea.getFontMetrics(textArea.getFont());
        this.fontWidth = fm.charWidth('m');
        this.lineHeight = fm.getHeight();
        this.vScrollPos = 0;
        this.hScrollPos = 0;
        this.lineCount = textArea.getLineCount();
        this.longestLine = getLongestLineLength();

        setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);

        setupScrollbars();
    }

    private int getLongestLineLength() {
        int longest = 0;
        for (String line : textArea.getText().split("\n")) {
            if (line.length() > longest) {
                longest = line.length();
            }
        }
        return longest;
    }

    private void setupScrollbars() {
        JScrollBar vScrollBar = getVerticalScrollBar();
        JScrollBar hScrollBar = getHorizontalScrollBar();

        vScrollBar.setUnitIncrement(lineHeight);
        vScrollBar.setBlockIncrement(lineHeight * 5);
        vScrollBar.setMinimum(0);
        vScrollBar.setMaximum(lineCount * lineHeight);

        hScrollBar.setUnitIncrement(fontWidth);
        hScrollBar.setBlockIncrement(fontWidth * 5);
        hScrollBar.setMinimum(0);
        hScrollBar.setMaximum(longestLine * fontWidth);

        revalidate();
    }

    public void refreshView() {
        lineCount = textArea.getLineCount();
        longestLine = getLongestLineLength();
        setupScrollbars();
    }

    public void onSize(int width, int height) {
        windowLines = Math.min(height / lineHeight, lineCount);
        windowColumns = Math.min((width - LEFT_MARGIN_WIDTH) / fontWidth, longestLine);
        setupScrollbars();
    }

    public void onVScroll(int delta) {
        vScrollPos = Math.max(0, Math.min(lineCount * lineHeight - windowLines * lineHeight, vScrollPos + delta));
        getVerticalScrollBar().setValue(vScrollPos);
    }

    public void onHScroll(int delta) {
        hScrollPos = Math.max(0, Math.min(longestLine * fontWidth - windowColumns * fontWidth, hScrollPos + delta));
        getHorizontalScrollBar().setValue(hScrollPos);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JTextArea textArea = new JTextArea(100, 50);
            textArea.setText("This is a sample text with\nmultiple lines of varying\nlengths for demonstration purposes.");
            TextView textView = new TextView(textArea);
            JFrame frame = new JFrame("TextView Demo");
            frame.add(textView);
            frame.pack();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
        });
    }
}
