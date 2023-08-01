import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;

public class TextView {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Text View");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(800, 600);

            JTextPane textPane = new JTextPane();
            frame.getContentPane().add(new JScrollPane(textPane));

            SimpleAttributeSet defaultAttr = new SimpleAttributeSet();
            StyleConstants.setForeground(defaultAttr, Color.BLACK);

            String text = "Example code for TextView in Java\n" +
                    "public class Main {\n" +
                    "   public static void main(String[] args) {\n" +
                    "       System.out.println(\"Hello, World!\");\n" +
                    "   }\n" +
                    "}\n";

            DefaultStyledDocument doc = new DefaultStyledDocument();
            doc.putProperty(DefaultStyledDocument.ParagraphAttribute, defaultAttr);
            textPane.setStyledDocument(doc);

            try {
                doc.insertString(0, text, defaultAttr);
                syntaxColor(doc);
            } catch (BadLocationException e) {
                e.printStackTrace();
            }

            frame.setVisible(true);
        });
    }

    private static void syntaxColor(StyledDocument doc) {
        AttributeSet keywordAttr = createAttribute(Color.BLUE, true);
        AttributeSet stringAttr = createAttribute(new Color(200, 100, 200), false);
        AttributeSet commentAttr = createAttribute(new Color(128, 110, 90), false);
        AttributeSet numberAttr = createAttribute(new Color(255, 80, 80), false);

        String[] keywords = {"public", "class", "void", "static", "for", "if", "else"};

        String content;
        try {
            content = doc.getText(0, doc.getLength());
        } catch (BadLocationException e) {
            return;
        }

        int start = 0;
        for (String line : content.split("\n")) {
            int lineStart = start;
            for (String token : line.split("\\s+")) {
                AttributeSet attr = null;
                if (token.startsWith("\"") && token.endsWith("\"")) {
                    attr = stringAttr;
                } else if (token.startsWith("//")) {
                    attr = commentAttr;
                } else if (isNumber(token)) {
                    attr = numberAttr;
                } else {
                    for (String keyword : keywords) {
                        if (token.equals(keyword)) {
                            attr = keywordAttr;
                            break;
                        }
                    }
                }

                if (attr != null) {
                    int tokenStart = content.indexOf(token, start);
                    int tokenEnd = tokenStart + token.length();
                    doc.setCharacterAttributes(tokenStart, tokenEnd - tokenStart, attr, false);
                }
            }
            start += line.length() + 1;
        }
    }

    private static AttributeSet createAttribute(Color color, boolean bold) {
        SimpleAttributeSet attr = new SimpleAttributeSet();
        StyleConstants.setForeground(attr, color);
        StyleConstants.setBold(attr, bold);
        return attr;
    }

    private static boolean isNumber(String token) {
        try {
            Integer.parseInt(token);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}
