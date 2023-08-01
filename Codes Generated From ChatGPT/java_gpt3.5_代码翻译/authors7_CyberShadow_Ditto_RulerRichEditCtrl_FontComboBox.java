import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.util.Vector;

public class FontComboBox extends JComboBox<String> {

    private int maxWidth;

    public FontComboBox() {
        super();
        this.maxWidth = 0;
        fillCombo();
        setRenderer(new FontComboBoxRenderer());
        addItemListener(e -> {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                String selectedFont = (String) e.getItem();
                // Perform any action required when a font is selected
            }
        });
    }

    private void fillCombo() {
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        String[] fontNames = ge.getAvailableFontFamilyNames();
        Vector<String> fonts = new Vector<>();

        for (String fontName : fontNames) {
            Font font = new Font(fontName, Font.PLAIN, 12);
            FontMetrics metrics = getFontMetrics(font);
            int width = metrics.stringWidth(fontName + "0");
            setMaxWidth(Math.max(getMaxWidth(), width));
            fonts.add(fontName);
        }
        setModel(new DefaultComboBoxModel<>(fonts));
    }

    public int getMaxWidth() {
        return maxWidth;
    }

    public void setMaxWidth(int maxWidth) {
        this.maxWidth = maxWidth;
    }

    public void selectFontName(String fontName) {
        setSelectedItem(fontName);
    }

    class FontComboBoxRenderer extends DefaultListCellRenderer {
        @Override
        public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
            Component c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
            if (c instanceof JLabel && value instanceof String) {
                JLabel label = (JLabel) c;
                label.setFont(new Font((String) value, Font.PLAIN, 12));
            }
            return c;
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("FontComboBox Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FontComboBox fontComboBox = new FontComboBox();
        frame.add(fontComboBox);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
