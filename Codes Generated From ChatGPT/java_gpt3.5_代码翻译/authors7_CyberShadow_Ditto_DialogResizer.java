import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.util.ArrayList;
import java.util.List;

public class DialogResizer {
    private JFrame parent;
    private List<ControlData> controls = new ArrayList<>();
    private Dimension dialogSize;

    public DialogResizer(JFrame parent) {
        this.parent = parent;
        this.dialogSize = parent.getSize();
        parent.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                moveControls(parent.getSize());
            }
        });
    }

    public void addControl(JComponent component, int flags) {
        controls.add(new ControlData(component, flags));
    }

    public void moveControls(Dimension newSize) {
        int deltaX = newSize.width - dialogSize.width;
        int deltaY = newSize.height - dialogSize.height;

        if (deltaX == 0 && deltaY == 0) {
            return;
        }

        dialogSize = newSize;

        for (ControlData controlData : controls) {
            Rectangle bounds = controlData.component.getBounds();

            if ((controlData.flags & ControlFlags.MOVE_LEFT) != 0) {
                bounds.x += deltaX;
            }

            if ((controlData.flags & ControlFlags.MOVE_TOP) != 0) {
                bounds.y += deltaY;
            }

            if ((controlData.flags & ControlFlags.SIZE_WIDTH) != 0) {
                bounds.width += deltaX;
            }

            if ((controlData.flags & ControlFlags.SIZE_HEIGHT) != 0) {
                bounds.height += deltaY;
            }

            controlData.component.setBounds(bounds);
        }
    }

    private static class ControlData {
        private JComponent component;
        private int flags;

        public ControlData(JComponent component, int flags) {
            this.component = component;
            this.flags = flags;
        }
    }

    public static class ControlFlags {
        public static final int MOVE_LEFT = 1;
        public static final int MOVE_TOP = 1 << 1;
        public static final int SIZE_WIDTH = 1 << 2;
        public static final int SIZE_HEIGHT = 1 << 3;
    }
}
