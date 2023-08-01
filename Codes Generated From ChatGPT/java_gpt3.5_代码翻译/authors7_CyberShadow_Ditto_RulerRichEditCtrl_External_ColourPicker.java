import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class ColourPicker extends JButton {
    private Color backgroundColor;
    private Color textColor;
    private String defaultText;
    private String customText;
    private boolean isActive;

    public ColourPicker() {
        super();
        setBackground(SystemColor.control);
        setForeground(SystemColor.controlText);
        setText("Colour Picker");

        isActive = false;
        defaultText = "Automatic";
        customText = "More Colors...";

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                onButtonClicked();
            }
        });
    }

    public Color getBackgroundColor() {
        return backgroundColor;
    }

    public void setBackgroundColor(Color backgroundColor) {
        this.backgroundColor = backgroundColor;
        repaint();
    }

    public Color getTextColor() {
        return textColor;
    }

    public void setTextColor(Color textColor) {
        this.textColor = textColor;
        repaint();
    }

    public String getDefaultText() {
        return defaultText;
    }

    public void setDefaultText(String defaultText) {
        this.defaultText = defaultText;
    }

    public String getCustomText() {
        return customText;
    }

    public void setCustomText(String customText) {
        this.customText = customText;
    }

    private void onButtonClicked() {
        isActive = true;
        Rectangle rect = getBounds();
        ColorPopup colorPopup = new ColorPopup(new Point(rect.x, rect.y + rect.height),
                getBackgroundColor(), this, defaultText, customText);
        colorPopup.show();
    }
}
import javax.swing.*;
import java.awt.*;

public class ColorPopup extends JDialog {
    private Color selectedColor;
    private ColourPicker parent;
    private String defaultText;
    private String customText;

    public ColorPopup(Point location, Color initialColor, ColourPicker parent,
                      String defaultText, String customText) {
        super(parent != null ? parent.getTopLevelAncestor() : null, true);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setUndecorated(true);

        this.selectedColor = initialColor;
        this.parent = parent;
        this.defaultText = defaultText;
        this.customText = customText;

        setLocation(location);
        setSize(200, 200);
        setLayout(new BorderLayout());

        // TODO: Add UI components to select colors, handle events, and set the selected color.
    }

    public Color getSelectedColor() {
        return selectedColor;
    }

    public void setSelectedColor(Color selectedColor) {
        this.selectedColor = selectedColor;
        parent.setBackgroundColor(selectedColor);
    }
}
