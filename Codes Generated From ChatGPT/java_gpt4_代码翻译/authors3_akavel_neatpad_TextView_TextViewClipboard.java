import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.event.*;
import javax.swing.*;

public class TextViewClipboard extends JFrame {
    private JTextArea textArea;
    private JPopupMenu popupMenu;

    public TextViewClipboard() {
        setTitle("TextViewClipboard");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        textArea = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(textArea);
        add(scrollPane);

        popupMenu = new JPopupMenu();
        JMenuItem cutMenuItem = new JMenuItem("Cut");
        JMenuItem copyMenuItem = new JMenuItem("Copy");
        JMenuItem pasteMenuItem = new JMenuItem("Paste");
        JMenuItem clearMenuItem = new JMenuItem("Clear");

        cutMenuItem.addActionListener(e -> onCut());
        copyMenuItem.addActionListener(e -> onCopy());
        pasteMenuItem.addActionListener(e -> onPaste());
        clearMenuItem.addActionListener(e -> onClear());

        popupMenu.add(cutMenuItem);
        popupMenu.add(copyMenuItem);
        popupMenu.add(pasteMenuItem);
        popupMenu.add(clearMenuItem);

        textArea.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    popupMenu.show(e.getComponent(), e.getX(), e.getY());
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            TextViewClipboard frame = new TextViewClipboard();
            frame.setVisible(true);
        });
    }

    private void onPaste() {
        if (!textArea.isEditable()) {
            return;
        }

        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable transferable = clipboard.getContents(null);

        if (transferable != null && transferable.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            try {
                String text = (String) transferable.getTransferData(DataFlavor.stringFlavor);
                textArea.replaceSelection(text);
            } catch (UnsupportedFlavorException | IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void onCopy() {
        String selectedText = textArea.getSelectedText();

        if (selectedText != null && !selectedText.isEmpty()) {
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            StringSelection selection = new StringSelection(selectedText);
            clipboard.setContents(selection, selection);
        }
    }

    private void onCut() {
        if (!textArea.isEditable()) {
            return;
        }

        String selectedText = textArea.getSelectedText();

        if (selectedText != null && !selectedText.isEmpty()) {
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            StringSelection selection = new StringSelection(selectedText);
            clipboard.setContents(selection, selection);
            textArea.replaceSelection("");
        }
    }

    private void onClear() {
        if (!textArea.isEditable()) {
            return;
        }

        textArea.replaceSelection("");
    }
}
