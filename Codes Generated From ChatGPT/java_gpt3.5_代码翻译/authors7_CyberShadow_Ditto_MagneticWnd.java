import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.util.ArrayList;
import java.util.List;

public class MagneticWindow extends JFrame {
    private boolean movedAttachedWindow = false;
    private Rectangle lastMove = new Rectangle();
    private boolean handleWindowPosChanging = true;
    private List<MagneticWindow> attachedWindows = new ArrayList<>();
    private List<MagneticWindow> snapToWindows = new ArrayList<>();

    public MagneticWindow() {
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentMoved(ComponentEvent e) {
                onMove(e);
            }
        });
    }

    private void onMove(ComponentEvent e) {
        if (movedAttachedWindow) {
            Rectangle thisRect = getBounds();

            for (MagneticWindow attachedWindow : attachedWindows) {
                if (attachedWindow != null) {
                    if (!lastMove.isEmpty()) {
                        Rectangle attachedRect = attachedWindow.getBounds();

                        int xDiff = thisRect.x - lastMove.x;
                        int yDiff = thisRect.y - lastMove.y;

                        attachedRect.x += xDiff;
                        attachedRect.y += yDiff;

                        attachedWindow.moveMagneticWindow(attachedRect);
                    }
                }
            }

            lastMove = thisRect;
        }

        for (MagneticWindow otherWindow : snapToWindows) {
            if (otherWindow != null &&
                    this.isVisible() &&
                    otherWindow.isVisible()) {

                if (movedAttachedWindow && isWindowAttached(otherWindow)) {
                    continue;
                }

                Rectangle parentRect = otherWindow.getBounds();
                boolean attached = false;

                // Snap left edge
                if (Math.abs(getX() - parentRect.x - parentRect.width) <= 15) {
                    setLocation(parentRect.x + parentRect.width, getY());
                    attached = true;
                }

                // Snap right edge
                if (Math.abs(getX() + getWidth() - parentRect.x) <= 15) {
                    setLocation(parentRect.x - getWidth(), getY());
                    attached = true;
                }

                // Snap to the bottom
                if (Math.abs(getY() + getHeight() - parentRect.y) <= 15) {
                    setLocation(getX(), parentRect.y - getHeight());
                    attached = true;
                }

                // Snap the top
                if (Math.abs(getY() - parentRect.y - parentRect.height) <= 15) {
                    setLocation(getX(), parentRect.y + parentRect.height);
                    attached = true;
                }

                otherWindow.setWindowAttached(this, attached);
                setWindowAttached(otherWindow, attached);

                if (movedAttachedWindow) {
                    lastMove.setBounds(getX(), getY(), getWidth(), getHeight());
                }
            }
        }
    }

    private void moveMagneticWindow(Rectangle rect) {
        handleWindowPosChanging = false;
        setBounds(rect);
        handleWindowPosChanging = true;
    }

    private void setWindowAttached(MagneticWindow otherWindow, boolean attach) {
        boolean found = false;

        for (MagneticWindow attachedWindow : attachedWindows) {
            if (attachedWindow == otherWindow) {
                found = true;
                if (!attach) {
                    attachedWindows.remove(attachedWindow);
                }
                break;
            }
        }

        if (attach && !found) {
            attachedWindows.add(otherWindow);
        }
    }

    private boolean isWindowAttached(MagneticWindow window) {
        for (MagneticWindow attachedWindow : attachedWindows) {
            if (attachedWindow == window) {
                return true;
            }
        }
        return false;
    }

    public void addSnapToWindow(MagneticWindow window) {
        if (!snapToWindows.contains(window)) {
            snapToWindows.add(window);
        }
    }

    public void removeSnapToWindow(MagneticWindow window) {
        snapToWindows.remove(window);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MagneticWindow window1 = new MagneticWindow();
            window1.setTitle("Window 1");
            window1.setSize(300, 200);
            window1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            window1.setLocationRelativeTo(null);
            window1.setVisible(true);

            MagneticWindow window2 = new MagneticWindow();
            window2.setTitle("Window 2");
            window2.setSize(300, 200);
            window2.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            window2.setLocation(window1.getX() + window1.getWidth(), window1.getY());
            window2.setVisible(true);

            window1.addSnapToWindow(window2);
            window2.addSnapToWindow(window1);
        });
    }
}
