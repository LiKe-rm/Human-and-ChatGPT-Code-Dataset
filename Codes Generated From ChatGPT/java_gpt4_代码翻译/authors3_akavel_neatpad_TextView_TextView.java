import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Comparator;

public class TextView extends JTextPane {

    private Font defaultFont;
    private ArrayList<Font> fontList;
    private int lineSpacingAbove;
    private int lineSpacingBelow;
    private int longestLine;
    private int numFonts;
    private int tabWidthChars;
    private ArrayList<LineInfo> lineInfoList;
    private int caretWidth;
    private int longLineLimit;
    private boolean hideCaret;
    private JPopupMenu userMenu;

    public TextView() {
        super();

        defaultFont = new Font("Monospaced", Font.PLAIN, 12);
        fontList = new ArrayList<>();
        fontList.add(defaultFont);

        lineSpacingAbove = 0;
        lineSpacingBelow = 0;

        numFonts = 1;
        longestLine = 0;
        tabWidthChars = 4;

        lineInfoList = new ArrayList<>();
        caretWidth = 2;
        longLineLimit = 80;

        hideCaret = false;

        userMenu = null;

        setFont(defaultFont);
        setMargin(new Insets(2, 2, 2, 2));

        addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                setCaretVisible(true);
            }

            @Override
            public void focusLost(FocusEvent e) {
                setCaretVisible(false);
            }
        });

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON3 && userMenu != null) {
                    userMenu.show(TextView.this, e.getX(), e.getY());
                }
            }
        });
    }

    public void addFont(Font font) {
        fontList.add(font);
    }

    public void setLineSpacing(int above, int below) {
        lineSpacingAbove = above;
        lineSpacingBelow = below;
    }

    public void setCaretWidth(int width) {
        caretWidth = width;
    }

    public void setLongLineLimit(int limit) {
        longLineLimit = limit;
    }

    public void setUserMenu(JPopupMenu menu) {
        userMenu = menu;
    }

    private void setCaretVisible(boolean visible) {
        if (!hideCaret) {
            getCaret().setVisible(visible);
        }
    }

    public static class LineInfo {
        public int lineNo;
        public int imageIndex;

        public LineInfo(int lineNo, int imageIndex) {
            this.lineNo = lineNo;
            this.imageIndex = imageIndex;
        }
    }

    public void setLineImage(int lineNo, int imageIndex) {
        LineInfo info = getLineInfo(lineNo);
        if (info != null) {
            info.imageIndex = imageIndex;
        } else {
            lineInfoList.add(new LineInfo(lineNo, imageIndex));
            lineInfoList.sort(Comparator.comparingInt(a -> a.lineNo));
        }
    }

    private LineInfo getLineInfo(int lineNo) {
        return lineInfoList.stream().filter(info -> info.lineNo == lineNo).findFirst().orElse(null);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("TextView Example");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.getContentPane().add(new TextView(), BorderLayout.CENTER);
            frame.setSize(800, 600);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}
