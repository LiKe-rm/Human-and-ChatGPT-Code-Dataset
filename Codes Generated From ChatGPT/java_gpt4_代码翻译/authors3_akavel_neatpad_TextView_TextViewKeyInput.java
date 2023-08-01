import javax.swing.*;
import javax.swing.undo.*;
import java.awt.*;
import java.awt.event.*;

public class TextViewKeyInput extends JPanel {
    private JTextArea textArea;
    private JScrollPane scrollPane;
    private UndoManager undoManager;

    public TextViewKeyInput() {
        setLayout(new BorderLayout());

        textArea = new JTextArea();
        scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        undoManager = new UndoManager();
        textArea.getDocument().addUndoableEditListener(undoManager);

        textArea.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_Z) {
                    undo();
                } else if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_Y) {
                    redo();
                } else if (e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
                    backDelete();
                } else if (e.getKeyCode() == KeyEvent.VK_DELETE) {
                    forwardDelete();
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("TextViewKeyInput");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(600, 400);

            TextViewKeyInput textViewKeyInput = new TextViewKeyInput();
            frame.add(textViewKeyInput);

            frame.setVisible(true);
        });
    }

    public void forwardDelete() {
        if (textArea.isEditable()) {
            textArea.replaceSelection("");
        }
    }

    public void backDelete() {
        if (textArea.isEditable() && textArea.getCaretPosition() > 0) {
            int currentPosition = textArea.getCaretPosition();
            textArea.select(currentPosition - 1, currentPosition);
            textArea.replaceSelection("");
        }
    }

    public void undo() {
        if (textArea.isEditable() && undoManager.canUndo()) {
            undoManager.undo();
        }
    }

    public void redo() {
        if (textArea.isEditable() && undoManager.canRedo()) {
            undoManager.redo();
        }
    }
}
