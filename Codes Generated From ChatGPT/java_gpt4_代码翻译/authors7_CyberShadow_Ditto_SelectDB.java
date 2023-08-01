import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.File;
import javax.swing.filechooser.FileNameExtensionFilter;

public class SelectDB extends JDialog {

    private static final long serialVersionUID = 1L;

    private JTextField pathTextField;
    private JButton selectButton;
    private JButton useDefaultButton;
    private JButton okButton;
    private JButton cancelButton;

    public SelectDB(JFrame parent) {
        super(parent, true);
        setTitle("Select Database");

        pathTextField = new JTextField();
        selectButton = new JButton("Select");
        useDefaultButton = new JButton("Use Default");
        okButton = new JButton("OK");
        cancelButton = new JButton("Cancel");

        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5, 5, 5, 5);
        add(pathTextField, gbc);

        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.weightx = 0;
        gbc.fill = GridBagConstraints.NONE;
        add(selectButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        add(useDefaultButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridwidth = 1;
        add(okButton, gbc);

        gbc.gridx = 1;
        gbc.gridy = 2;
        add(cancelButton, gbc);

        pathTextField.setText(GetSetOptions.getDbPath(false));

        selectButton.addActionListener(this::onSelect);
        useDefaultButton.addActionListener(this::onUseDefault);
        okButton.addActionListener(e -> onOk());
        cancelButton.addActionListener(e -> onCancel());

        pack();
        setLocationRelativeTo(parent);
    }

    private void onOk() {
        String path = pathTextField.getText();
        GetSetOptions.setDbPath(path);
        dispose();
    }

    private void onCancel() {
        dispose();
    }

    private void onSelect(ActionEvent e) {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Open Database");
        fileChooser.setFileFilter(new FileNameExtensionFilter("Database Files (.MDB)", "mdb"));
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

        int returnValue = fileChooser.showOpenDialog(this);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            String path = selectedFile.getAbsolutePath();
            if (!validDb(path)) {
                JOptionPane.showMessageDialog(this, "Invalid Database", "Ditto", JOptionPane.ERROR_MESSAGE);
                pathTextField.requestFocus();
            } else {
                pathTextField.setText(path);
            }
        }
    }

    private void onUseDefault(ActionEvent e) {
        GetSetOptions.setDbPath("");
        String defaultPath = GetSetOptions.getDbPath();
        if (!validDb(defaultPath)) {
            new File(defaultPath).delete();
        }
        if (checkDbExists(GetSetOptions.getDbPath())) {
            dispose();
        }
    }

    private boolean validDb(String path) {
        // Add logic to validate the database file
        return true;
    }

    private boolean checkDbExists(String path) {
        // Add logic to check if the database file exists
        return true;
    }

    public static class GetSetOptions {
        public static String getDbPath(boolean useDefault) {
            return ""; // Add logic to get the database path
        }

        public static void setDbPath(String path) {
            // Add logic to set the database
            path
        }
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame parent = new JFrame();
            parent.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            parent.setSize(300, 200);
            parent.setLocationRelativeTo(null);
            SelectDB selectDb = new SelectDB(parent);
            selectDb.setVisible(true);
        });
    }
}