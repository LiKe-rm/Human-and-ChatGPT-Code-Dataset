import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class RREToolbar extends JToolBar {
    private JComboBox<String> fontComboBox;
    private JComboBox<Integer> fontSizeComboBox;
    private JButton fontColorButton;
    private JColorChooser fontColorChooser;
    private Color currentFontColor;

    public RREToolbar() {
        initializeComponents();
        setupListeners();
    }

    private void initializeComponents() {
        fontComboBox = new JComboBox<>();
        fontSizeComboBox = new JComboBox<>();
        fontColorButton = new JButton("Font Color");
        fontColorChooser = new JColorChooser();
        currentFontColor = Color.BLACK;

        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        String[] fontNames = ge.getAvailableFontFamilyNames();
        for (String fontName : fontNames) {
            fontComboBox.addItem(fontName);
        }

        for (int i = 8; i <= 72; i += 2) {
            fontSizeComboBox.addItem(i);
        }

        add(fontComboBox);
        add(fontSizeComboBox);
        add(fontColorButton);
    }

    private void setupListeners() {
        fontComboBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    String selectedFont = (String) e.getItem();
                    getParent().dispatchEvent(new FontChangeEvent(RREToolbar.this, selectedFont, null, null));
                }
            }
        });

        fontSizeComboBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    int selectedSize = (int) e.getItem();
                    getParent().dispatchEvent(new FontChangeEvent(RREToolbar.this, null, selectedSize, null));
                }
            }
        });

        fontColorButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color newColor = JColorChooser.showDialog(RREToolbar.this, "Choose Font Color", currentFontColor);
                if (newColor != null) {
                    currentFontColor = newColor;
                    getParent().dispatchEvent(new FontChangeEvent(RREToolbar.this, null, null, currentFontColor));
                }
            }
        });
    }
}

class FontChangeEvent extends ActionEvent {
    private final String fontName;
    private final Integer fontSize;
    private final Color fontColor;

    public FontChangeEvent(Object source, String fontName, Integer fontSize, Color fontColor) {
        super(source, ActionEvent.ACTION_PERFORMED, null);
        this.fontName = fontName;
        this.fontSize = fontSize;
        this.fontColor = fontColor;
    }

    public String getFontName() {
        return fontName;
    }

    public Integer getFontSize() {
        return fontSize;
    }

    public Color getFontColor() {
        return fontColor;
    }
}
