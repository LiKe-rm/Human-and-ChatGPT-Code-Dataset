import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class OptionsUtilities extends JPanel {
    private JTextField pathTextField;
    private JButton compactDBButton;
    private JButton repairButton;
    private JButton getPathButton;

    public OptionsUtilities() {
        setLayout(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();

        // Initialize components
        pathTextField = new JTextField(20);
        compactDBButton = new JButton("Compact DB");
        repairButton = new JButton("Repair");
        getPathButton = new JButton("Get Path");

        // Add components to panel
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.gridwidth = 2;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        add(pathTextField, constraints);

        constraints.gridx = 2;
        constraints.gridy = 0;
        constraints.gridwidth = 1;
        constraints.fill = GridBagConstraints.NONE;
        add(getPathButton, constraints);

        constraints.gridx = 0;
        constraints.gridy = 1;
        constraints.gridwidth = 1;
        add(compactDBButton, constraints);

        constraints.gridx = 1;
        constraints.gridy = 1;
        add(repairButton, constraints);

        // Set up event listeners
        compactDBButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onCompactDB();
            }
        });

        repairButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onRepair();
            }
        });

        getPathButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onGetPath();
            }
        });

        initializePath();
    }

    private void initializePath() {
        // TODO: Get the current database path from the application
        // Example: String currentDBPath = getCurrentDBPath();

        String currentDBPath = ""; // Replace this with the actual path
        pathTextField.setText(currentDBPath);
    }

    private void onCompactDB() {
        // TODO: Compact the database
        // Example: compactDatabase();
    }

    private void onRepair() {
        // TODO: Repair the database
        // Example: repairDatabase();
    }

    private void onGetPath() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Open Database");
        fileChooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Database Files (.MDB)", "mdb"));
        int result = fileChooser.showOpenDialog(this);

        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            pathTextField.setText(selectedFile.getAbsolutePath());
        }
    }

    public boolean applyChanges() {
        String newPath = pathTextField.getText();
        // TODO: Get the old database path from the application
        // Example: String oldPath = getOldDBPath();

        String oldPath = ""; // Replace this with the actual path

        if (!oldPath.equals(newPath)) {
            // TODO: Set the new database path in the application
            // Example: setNewDBPath(newPath);
        }

        return true;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Options Utilities");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(new OptionsUtilities());
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
