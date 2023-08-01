import java.awt.*;
import java.awt.event.KeyEvent;
import javax.swing.*;
import java.util.concurrent.TimeUnit;

public class ExternalWindowTracker {
    private Window activeWindow;
    private Component focusedComponent;
    private boolean dittoHasFocus;

    public ExternalWindowTracker() {
        activeWindow = null;
        focusedComponent = null;
        dittoHasFocus = false;
    }

    public boolean trackActiveWindow(Component focus) {
        Window newFocus = SwingUtilities.getWindowAncestor(focus);
        Window newActive = KeyboardFocusManager.getCurrentKeyboardFocusManager().getActiveWindow();

        if (newFocus == null) {
            newFocus = newActive;
        }

        if (newFocus == null || newActive == null) {
            System.out.println("TargetActiveWindow values invalid");
            return false;
        }

        if (newActive == activeWindow) {
            System.out.println("TargetActiveWindow window the same");
            return false;
        }

        if (isAppWindow(newFocus) || isAppWindow(newActive)) {
            if (!dittoHasFocus) {
                System.out.printf("Ditto has focus - Active: %s, Focus: %s\n",
                        activeWindow, focusedComponent);
            }

            dittoHasFocus = true;
            return false;
        }

        focusedComponent = focus;
        activeWindow = newActive;
        dittoHasFocus = false;

        System.out.printf("TargetActiveWindow Active: %s, Focus: %s\n",
                activeWindow, focusedComponent);

        return true;
    }

    // Additional methods based on the C++ code
    // ...

    public static void main(String[] args) {
        // Test the implementation
    }
}
