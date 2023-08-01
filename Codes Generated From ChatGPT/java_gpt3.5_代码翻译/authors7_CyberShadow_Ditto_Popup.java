import javax.swing.*;
import java.awt.*;

public class Popup {
    private JToolTip tooltip;
    private JComponent owner;
    private boolean isShowing;
    private boolean allowShow;
    private String tooltipText;
    private Point position;
    private boolean top, centerY, left, centerX;
    private Rectangle screenBounds;

    public Popup() {
        init();
    }

    public Popup(int x, int y, JComponent owner) {
        init();
        this.owner = owner;
        setPosition(new Point(x, y));
    }

    private void init() {
        tooltip = new JToolTip();
        isShowing = false;
        allowShow = true;
        position = new Point(0, 0);
        top = true;
        centerY = false;
        left = true;
        centerX = false;
        screenBounds = new Rectangle(Toolkit.getDefaultToolkit().getScreenSize());
    }

    public void setTimeout(int timeout) {
        ToolTipManager.sharedInstance().setInitialDelay(timeout);
    }

    public void setPosition(Point pos) {
        position = pos;
    }

    public void setPositionInfo(boolean top, boolean centerY, boolean left, boolean centerX) {
        this.top = top;
        this.centerY = centerY;
        this.left = left;
        this.centerX = centerX;
    }

    public void adjustPosition(Point pos) {
        if (owner != null) {
            Rectangle ownerBounds = owner.getBounds();
            Rectangle tooltipBounds = tooltip.getPreferredSize();
            int x = pos.x - (centerX ? tooltipBounds.width / 2 : (left ? 0 : tooltipBounds.width));
            int y = pos.y - (centerY ? tooltipBounds.height / 2 : (top ? 0 : tooltipBounds.height));
            pos.setLocation(x, y);
            pos = SwingUtilities.convertPoint(owner, pos, owner.getParent());
        }
    }

    public void setTooltipText(String text) {
        tooltipText = text;
        tooltip.setTipText(text);
    }

    public void show(String text, Point pos, boolean adjustPosition) {
        if (tooltip == null) {
            return;
        }
        tooltipText = text;
        if (!isShowing) {
            tooltip.setLocation(-10000, -10000);
        }
        setTooltipText(text);
        if (adjustPosition) {
            adjustPosition(pos);
        }
        position = pos;
        tooltip.setSize(tooltip.getPreferredSize());
        tooltip.setLocation(pos);
        tooltip.setVisible(true);
        isShowing = true;
    }

    public void show(String text) {
        tooltipText = text;
        show(text, position);
    }

    public void allowShow(String text) {
        tooltipText = text;
        if (allowShow) {
            show(text, position);
        }
    }

    public void hide() {
        if (tooltip == null) {
            return;
        }
        tooltip.setVisible(false);
        isShowing = false;
    }

    public void show(String text, Point pos) {
        show(text, pos, true);
    }
}
