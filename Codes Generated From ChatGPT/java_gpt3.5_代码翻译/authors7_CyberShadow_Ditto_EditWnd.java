import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class EditWindow extends JFrame {
    private JToolBar toolBar;
    private JTabbedPane tabbedPane;
    private JCheckBox updateDescriptionCheckbox;
    private ArrayList<CustomTextPane> textPanes;

    public EditWindow() {
        setTitle("Java Edit Window");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 600);
        initComponents();
    }

    private void initComponents() {
        toolBar = new JToolBar();
        tabbedPane = new JTabbedPane();
        updateDescriptionCheckbox = new JCheckBox("Update clip description on save?");
        textPanes = new ArrayList<>();

        setLayout(new BorderLayout());

        // Toolbar
        toolBar.setFloatable(false);
        toolBar.add(new JButton("New")).addActionListener(e -> addNewItem());
        toolBar.add(new JButton("Save")).addActionListener(e -> saveItem());
        toolBar.add(new JButton("Save All")).addActionListener(e -> saveAllItems());
        toolBar.add(new JButton("Close")).addActionListener(e -> closeItem());
        toolBar.add(new JButton("Save & Close")).addActionListener(e -> saveAndCloseItem());
        add(toolBar, BorderLayout.NORTH);

        // TabbedPane
        add(tabbedPane, BorderLayout.CENTER);

        // Update description checkbox
        JPanel southPanel = new JPanel(new BorderLayout());
        southPanel.add(updateDescriptionCheckbox, BorderLayout.WEST);
        add(southPanel, BorderLayout.SOUTH);
    }

    private void addNewItem() {
        CustomTextPane textPane = new CustomTextPane();
        textPanes.add(textPane);
        tabbedPane.addTab("New", new JScrollPane(textPane));
    }

    private void saveItem() {
        int selectedIndex = tabbedPane.getSelectedIndex();
        if (selectedIndex >= 0 && selectedIndex < textPanes.size()) {
            CustomTextPane textPane = textPanes.get(selectedIndex);
            textPane.saveToDB(updateDescriptionCheckbox.isSelected());
        }
    }

    private void saveAllItems() {
        for (CustomTextPane textPane : textPanes) {
            textPane.saveToDB(updateDescriptionCheckbox.isSelected());
        }
    }

    private void closeItem() {
        int selectedIndex = tabbedPane.getSelectedIndex();
        if (selectedIndex >= 0 && selectedIndex < textPanes.size()) {
            tabbedPane.remove(selectedIndex);
            textPanes.remove(selectedIndex);
        }
    }

    private void saveAndCloseItem() {
        saveItem();
        closeItem();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EditWindow window = new EditWindow();
            window.setVisible(true);
        });
    }
}

class CustomTextPane extends JTextPane {
    public void saveToDB(boolean updateDescription) {
        // Your implementation to save the text pane content to the database
        System.out.println("Saving content to database...");
    }
}
