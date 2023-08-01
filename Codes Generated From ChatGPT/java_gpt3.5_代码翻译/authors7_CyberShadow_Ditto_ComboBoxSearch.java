import javax.swing.*;
import java.awt.event.*;

public class ComboBoxSearch extends JComboBox<String> {

    private boolean showingDropDown;

    public ComboBoxSearch() {
        showingDropDown = false;
        initializeListeners();
    }

    private void initializeListeners() {
        addActionListener(e -> onSelectionChanged());

        addItemListener(e -> {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                onItemSelected();
            }
        });

        getEditor().getEditorComponent().addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                onKeyPressed(e);
            }
        });
    }

    private void onSelectionChanged() {
        showingDropDown = isPopupVisible();
    }

    private void onItemSelected() {
        showingDropDown = false;
    }

    private void onKeyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_ENTER && !showingDropDown) {
            String searchText = getEditor().getItem().toString();
            if (searchText.length() > 0 && !searchText.equals(getItemAt(0))) {
                insertItemAt(searchText, 0);
        }
        setSelectedItem(searchText);
        performSearch(searchText);

    } else if (e.getKeyCode() == KeyEvent.VK_DOWN ||
            e.getKeyCode() == KeyEvent.VK_UP ||
            e.getKeyCode() == KeyEvent.VK_F3) {

        if (isPopupVisible()) {
            showingDropDown = true;
        } else {
            showingDropDown = false;
            showPopup();
        }
    } else if ((e.getKeyCode() == KeyEvent.VK_C || e.getKeyCode() == KeyEvent.VK_X) &&
            (e.isControlDown()) || e.getKeyCode() == KeyEvent.VK_DELETE) {
            JTextComponent editorComponent = (JTextComponent) getEditor().getEditorComponent();
            if (editorComponent.getSelectionStart() == editorComponent.getSelectionEnd()) {
                handleCopyCutDelete(e.getKeyCode());
            }
        }
    }

    private void performSearch(String searchText) {
        // Implement your search logic here
        System.out.println("Performing search with text: " + searchText);
    }

    private void handleCopyCutDelete(int keyCode) {
        // Implement your handling for copy, cut, and delete operations here
        System.out.println("Handling key code: " + keyCode);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("ComboBoxSearch Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);

        ComboBoxSearch comboBoxSearch = new ComboBoxSearch();
        frame.add(comboBoxSearch);

        frame.setVisible(true);
    }
}