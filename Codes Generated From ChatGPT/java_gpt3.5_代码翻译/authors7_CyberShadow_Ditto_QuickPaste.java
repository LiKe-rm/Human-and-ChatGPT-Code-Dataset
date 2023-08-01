import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class QuickPaste {

    private QuickPasteWindow quickPasteWindow;

    public QuickPaste() {
        quickPasteWindow = null;
    }

    public void create(JFrame parent) {
        Point point = GetSetOptions.getQuickPastePoint();
        Dimension size = GetSetOptions.getQuickPasteSize();

        if (quickPasteWindow == null) {
            quickPasteWindow = new QuickPasteWindow(parent);
            quickPasteWindow.setLocation(point);
            quickPasteWindow.setSize(size);
            quickPasteWindow.setVisible(true);
        }
    }

    public void closeQPasteWindow() {
        if (quickPasteWindow != null) {
            if (quickPasteWindow.isVisible()) {
                System.out.println("CloseQPasteWindow called but the window is visible");
                return;
            }

            quickPasteWindow.dispose();
            quickPasteWindow = null;
        }
    }

    public void showQPasteWindow(JFrame parent, boolean atPrevPos, boolean fromKeyboard, boolean refillList) {
        System.out.println("Start of ShowQPasteWindow, AtPrevPos: " + atPrevPos + ", FromKeyboard: " + fromKeyboard + ", RefillList: " + refillList);

        if (!fromKeyboard && (Toolkit.getDefaultToolkit().getLockingKeyState(KeyEvent.VK_SHIFT)) && (Toolkit.getDefaultToolkit().getLockingKeyState(KeyEvent.VK_CONTROL))) {
            if (quickPasteWindow != null) {
                quickPasteWindow.dispose();
                quickPasteWindow = null;
            }

            System.out.println("CloseQPasteWindow called closing QuickPasteWindow from keyboard");
            return;
        }

        if (GetSetOptions.getShowPersistent() && quickPasteWindow != null) {
            quickPasteWindow.setVisible(true);
            quickPasteWindow.toFront();
            return;
        }

        if (quickPasteWindow == null) {
            quickPasteWindow = new QuickPasteWindow(parent);
        }

        int position = GetSetOptions.getQuickPastePosition();
        Point point = GetSetOptions.getQuickPastePoint();
        Dimension size = GetSetOptions.getQuickPasteSize();

        if (atPrevPos) {
            point = GetSetOptions.getQuickPastePoint();
            size = GetSetOptions.getQuickPasteSize();
        } else if (position == Position.AT_CARET) {
            point = App.getActiveWindow().getFocusCaret();
        } else if (position == Position.AT_CURSOR) {
            point = MouseInfo.getPointerInfo().getLocation();
        } else if (position == Position.AT_PREVIOUS) {
            point = GetSetOptions.getQuickPastePoint();
        }

        quickPasteWindow.setLocation(point);
        quickPasteWindow.setSize(size);
        quickPasteWindow.setVisible(true);
        quickPasteWindow.toFront();

        if (refillList) {
            quickPasteWindow.showQuickPasteWindow(refillList);
        }

        System.out.println("End of ShowQPasteWindow, AtPrevPos: " + atPrevPos + ", FromKeyboard: " + fromKeyboard + ", RefillList: " + refillList);
    }

    public void moveSelection(boolean down) {
        if (quickPasteWindow != null) {
            quickPasteWindow.moveSelection(down);
        }
    }

    public void onKeyStateUp() {
        if (quickPasteWindow != null) {
            quickPasteWindow.onKeyStateUp();
        }
    }

    public void setKeyModifierState(boolean active) {
        if (quickPasteWindow != null) {
            quickPasteWindow.setKeyModifierState(active);
        }
    }

    public void hideQPasteWindow() {
        if (quickPasteWindow != null) {
            quickPasteWindow.hideQuickPasteWindow();
        }
    }

    public boolean isWindowVisible() {
        if (quickPasteWindow != null) {
            return quickPasteWindow.isVisible();
        }
        return false;
    }

    public static void main(String[] args) {
        JFrame parent = new JFrame("Parent Frame");
        parent.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        parent.setSize(300, 300);
        parent.setVisible(true);

        QuickPaste quickPaste = new QuickPaste();
        quickPaste.create(parent);
    }
}
