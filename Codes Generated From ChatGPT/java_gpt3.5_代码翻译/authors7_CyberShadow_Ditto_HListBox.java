import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class HListBox extends JList<String> {
    private DefaultListModel<String> model;
    private int width;

    public HListBox() {
        width = 0;
        model = new DefaultListModel<>();
        setModel(model);
        setCellRenderer(new HListCellRenderer());
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                updateWidth();
            }
        });
    }

    public void addString(String s) {
        model.addElement(s);
        updateWidth(s);
    }

    public void insertString(int index, String s) {
        model.insertElementAt(s, index);
        updateWidth(s);
    }

    public void resetContent() {
        model.clear();
        width = 0;
    }

    public void deleteString(int index) {
        if (index >= 0 && index < model.size()) {
            model.remove(index);
            updateWidth();
        }
    }

    private void updateWidth() {
        width = 0;
        for (int i = 0; i < model.size(); i++) {
            String s = model.get(i);
            updateWidth(s);
        }
    }

    private void updateWidth(String s) {
        FontMetrics fm = getFontMetrics(getFont());
        int stringWidth = fm.stringWidth(s) + 3 * getFont().getSize();
        if (stringWidth > width) {
            width = stringWidth;
            setFixedCellWidth(width);
        }
    }

    static class HListCellRenderer extends JLabel implements ListCellRenderer<String> {
        @Override
        public Component getListCellRendererComponent(JList<? extends String> list, String value, int index, boolean isSelected, boolean cellHasFocus) {
            setText(value);

            if (isSelected) {
                setBackground(list.getSelectionBackground());
                setForeground(list.getSelectionForeground());
            } else {
                setBackground(list.getBackground());
                setForeground(list.getForeground());
            }

            setEnabled(list.isEnabled());
            setFont(list.getFont());
            setOpaque(true);

            return this;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("HListBox Example");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            HListBox listBox = new HListBox();
            listBox.addString("Hello, World!");
            listBox.addString("A longer string to demonstrate horizontal scrolling");
            listBox.insertString(1, "Inserted String");

            JScrollPane scrollPane = new JScrollPane(listBox);

            frame.getContentPane().add(scrollPane);
            frame.setSize(300, 200);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}
