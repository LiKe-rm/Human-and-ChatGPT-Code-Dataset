import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class OptionsTypes extends JPanel {
    private JList<String> typeList;
    private DefaultListModel<String> listModel;
    private JButton deleteButton;
    private JButton addButton;
    private boolean saveChanges;

    public OptionsTypes() {
        saveChanges = false;
        setLayout(new BorderLayout());

        listModel = new DefaultListModel<>();
        typeList = new JList<>(listModel);
        typeList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

        JScrollPane scrollPane = new JScrollPane(typeList);
        add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        deleteButton = new JButton("Delete");
        addButton = new JButton("Add");
        buttonPanel.add(deleteButton);
        buttonPanel.add(addButton);

        add(buttonPanel, BorderLayout.SOUTH);

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onDelete();
            }
        });

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onAdd();
            }
        });

        initializeTypeList();
    }

    private void initializeTypeList() {
        // TODO: Load types from the application or database.
        // Example: List<String> types = loadTypesFromDatabase();

        List<String> types = new ArrayList<>();
        types.add("CF_TEXT");
        types.add("CF_RTF");
        types.add("CF_UNICODETEXT");
        types.add("CF_HDROP");
        types.add("CF_DIB");

        for (String type : types) {
            listModel.addElement(type);
        }
    }

    private void onDelete() {
        List<String> selectedItems = typeList.getSelectedValuesList();

        if (!selectedItems.isEmpty()) {
            saveChanges = true;

            for (String item : selectedItems) {
                listModel.removeElement(item);
            }
        }
    }

    private void onAdd() {
        // TODO: Implement the add functionality.
        // Example: AddTypeDialog addDialog = new AddTypeDialog();
        // Example: List<String> newTypes = addDialog.showDialog();

        List<String> newTypes = new ArrayList<>(); // Replace this with the new types obtained from the AddTypeDialog.

        if (!newTypes.isEmpty()) {
            saveChanges = true;
            for (String type : newTypes) {
                if (!listModel.contains(type)) {
                    listModel.addElement(type);
                }
            }
        }
    }

    public boolean applyChanges() {
        if (saveChanges) {
            // TODO: Save the changes to the application or database.
            // Example: saveTypesToDatabase(listModel);

            // Refresh the local cache.
            // Example: reloadTypes();
        }

        return true;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Options Types");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(new OptionsTypes());
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
