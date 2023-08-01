import javax.swing.*;
import java.awt.*;

public class AlphaBlend {
    private Window window;
    private int opacity;
    private boolean transparent;

    public AlphaBlend() {
        window = null;
        opacity = 0;
        transparent = false;
    }

    public AlphaBlend(Window window, int opacity) {
        this.window = null;
        this.opacity = 0;
        this.transparent = false;

        setWindow(window);
        setOpacity(opacity);
    }

    public boolean setWindow(Window window) {
        if (window != null) {
            this.window = window;
            return true;
        } else {
            return false;
        }
    }

    public boolean setOpacity(int opacity) {
        if (opacity >= 0 && opacity <= 255) {
            this.opacity = opacity;
            if (transparent) {
                updateTransparency();
            }
            return true;
        }
        return false;
    }

    private void updateTransparency() {
        if (window != null) {
            float newOpacity = opacity / 255.0f;
            window.setOpacity(newOpacity);
        }
    }

    public void setTransparent(boolean transparent) {
        if (transparent) {
            updateTransparency();
            this.transparent = true;
        } else {
            if (window != null) {
                window.setOpacity(1.0f);
            }
            this.transparent = false;
        }
    }

    public boolean setTransparent(Window window, int opacity, boolean transparent) {
        if (!setWindow(window)) {
            return false;
        }

        if (!setOpacity(opacity)) {
            return false;
        }

        setTransparent(transparent);

        return true;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("AlphaBlend Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

        AlphaBlend alphaBlend = new AlphaBlend(frame, 128);
        alphaBlend.setTransparent(true);
    }
}
