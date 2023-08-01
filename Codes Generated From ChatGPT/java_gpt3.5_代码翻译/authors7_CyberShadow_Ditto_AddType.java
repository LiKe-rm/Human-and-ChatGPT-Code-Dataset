import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;

public class AddTypeDialog extends JDialog {

    private final List<String> defaultTypes = Arrays.asList(
            "CF_TEXT", "CF_BITMAP", "CF_METAFILEPICT", "CF_SYLK", "CF_DIF", "CF_TIFF",
            "CF_OEMTEXT", "CF_DIB", "CF_PALETTE", "CF_PENDATA", "CF_RIFF", "CF_WAVE",
            "CF_UNICODETEXT", "CF_ENHMETAFILE", "CF_HDROP", "CF_LOCALE", "CF_OWNERDISPLAY",
            "CF_DSPTEXT", "CF_DSPBITMAP", "CF_DSPMETAFILEPICT", "CF_DSPENHMETAFILE",
            "CF_RTF", "CF_RTFNOOBJS", "CF_RETEXTOBJ", "HTML Format");

    private JList<String> defaultTypesList;
    private JList<String> onClipboardList;
    private JTextField customTypeField;
    private List<String> selectedTypes;

    public AddTypeDialog(JFrame parent) {
        super(parent, "Add Type", true);

        initComponents();
        initListeners();

        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        pack();
        setLocationRelativeTo(parent);
    }

    private void initComponents() {
        setLayout(new BorderLayout());

        defaultTypesList = new JList<>(defaultTypes.toArray(new String[0]));
        defaultTypesList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        JScrollPane defaultTypesScrollPane = new JScrollPane(defaultTypesList);
        add(defaultTypesScrollPane, BorderLayout.WEST);

        customTypeField = new JTextField(20);
        add(customTypeField, BorderLayout.NORTH);

        onClipboardList = new JList<>(new String[0]); // Assuming this will be populated with actual clipboard data
        onClipboardList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        JScrollPane onClipboardScrollPane = new JScrollPane(onClipboardList);
        add(onClipboardScrollPane, BorderLayout.EAST);

        JPanel buttonPanel = new JPanel();
        JButton addButton1 = new JButton("Add Default Types");
        addButton1.addActionListener(e -> onAdd1());
        buttonPanel.add(addButton1);

        JButton addButton2 = new JButton("Add Custom Type");
        addButton2.addActionListener(e -> onAdd2());
        buttonPanel.add(addButton2);

        JButton addButton3 = new JButton("Add Clipboard Types");
        addButton3.addActionListener(e -> onAdd3());
        buttonPanel.add(addButton3);

        add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initListeners() {
        defaultTypesList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    onAdd1();
                }
            }
        });

        onClipboardList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    onAdd3();
                }
            }
        });
    }

    private void onAdd1(){
        selectedTypes = new ArrayList<>();
        List<String> selectedDefaultTypes = defaultTypesList.getSelectedValuesList();
        if (!selectedDefaultTypes.isEmpty()) {
            selectedTypes.addAll(selectedDefaultTypes);
        }
        dispose();
    }

    private void onAdd2() {
        selectedTypes = new ArrayList<>();
        String customType = customTypeField.getText();
        if (!customType.isEmpty()) {
            selectedTypes.add(customType);
        }
        dispose();
    }

    private void onAdd3() {
        selectedTypes = new ArrayList<>();
        List<String> selectedClipboardTypes = onClipboardList.getSelectedValuesList();
        if (!selectedClipboardTypes.isEmpty()) {
            selectedTypes.addAll(selectedClipboardTypes);
        }
        dispose();
    }

    public List<String> getSelectedTypes() {
        return selectedTypes;
    }

    public static void main(String[] args) {
        JFrame parent = new JFrame();
        parent.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        parent.setSize(300, 200);
        parent.setLocationRelativeTo(null);
        parent.setVisible(true);

        AddTypeDialog addTypeDialog = new AddTypeDialog(parent);
        addTypeDialog.setVisible(true);
        System.out.println(addTypeDialog.getSelectedTypes());
    }
}
