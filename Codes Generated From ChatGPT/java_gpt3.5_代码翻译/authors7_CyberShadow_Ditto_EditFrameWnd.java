import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class EditFrameWnd extends JFrame {
    private EditWnd editWnd;
    private DittoWindow dittoWindow;
    private Rectangle iconRect;

    public EditFrameWnd() {
        super("Ditto Editor");
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        setResizable(false);

        editWnd = new EditWnd();
        getContentPane().add(editWnd);

        dittoWindow = new DittoWindow();
        dittoWindow.setCaptionOn(this, DittoWindow.CAPTION_TOP, true);
        dittoWindow.setCaptionColors(Color.YELLOW, Color.RED);

        iconRect = new Rectangle(-2, -15, 15, 0);

        setupListeners();
        pack();
    }

    private void setupListeners() {
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                onSize();
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                onClose();
            }
        });

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                onNcLButtonDblClk(e.getPoint());
            }
        });

        addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                onSetFocus();
            }
        });
    }

    private void onSize() {
        if (editWnd != null) {
            editWnd.setBounds(getContentPane().getBounds());
        }
    }

    private boolean editIds(ClipIds ids) {
        return editWnd.editIds(ids);
    }

    private void onDummy() {
        // Dummy method for unused actions
    }

    private void onSetFocus() {
        editWnd.requestFocus();
    }

    private void onClose() {
        if (editWnd.closeEdits(true)) {
            dispose();
        }
    }

    private void onNcLButtonDblClk(Point point) {
        if (iconRect.contains(point)) {
            if (editWnd.closeEdits(true)) {
                onClose();
            }
            return;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EditFrameWnd frame = new EditFrameWnd();
            frame.setVisible(true);
        });
    }
}
