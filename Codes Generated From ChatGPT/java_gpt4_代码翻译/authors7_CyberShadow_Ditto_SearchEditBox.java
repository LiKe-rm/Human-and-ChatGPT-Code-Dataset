import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class SearchEditBox extends JTextField {

    private static final long serialVersionUID = 1L;

    public SearchEditBox() {
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_ENTER:
                        if (Options.findAsYouType) {
                            getParent().dispatchEvent(new SearchEvent(SearchEvent.Type.SELECT, ""));
                        } else {
                            getParent().dispatchEvent(new SearchEvent(SearchEvent.Type.SEARCH, ""));
                        }
                        break;
                    case KeyEvent.VK_DOWN:
                    case KeyEvent.VK_UP:
                    case KeyEvent.VK_F3:
                        if (Options.findAsYouType) {
                            getParent().dispatchEvent(new SearchEvent(SearchEvent.Type.UPDOWN, e.getKeyCode()));
                        }
                        break;
                    case KeyEvent.VK_C:
                    case KeyEvent.VK_X:
                    case KeyEvent.VK_DELETE:
                        if ((e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) != 0) {
                            int selectionStart = getSelectionStart();
                            int selectionEnd = getSelectionEnd();
                            if (selectionStart == selectionEnd) {
                                getParent().dispatchEvent(new SearchEvent(SearchEvent.Type.UPDOWN, e.getKeyCode()));
                            }
                        }
                        break;
                }
            }
        });
    }

    public static class SearchEvent extends AWTEvent {
        public enum Type {
            SELECT, SEARCH, UPDOWN
        }

        private final Type type;
        private final Object data;

        public SearchEvent(Type type, Object data) {
            super(type, RESERVED_ID_MAX + 1);
            this.type = type;
            this.data = data;
        }

        public Type getType() {
            return type;
        }

        public Object getData() {
            return data;
        }
    }

    public static class Options {
        public static boolean findAsYouType = true;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Search Edit Box");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel(new BorderLayout());
        SearchEditBox searchEditBox = new SearchEditBox();
        panel.add(searchEditBox, BorderLayout.NORTH);
        frame.add(panel);

        frame.setVisible(true);
    }
}
