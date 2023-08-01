import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class ChooseDialog extends JDialog {
    private JTextField directoryEdit;

    public ChooseDialog(JFrame parent) {
        super(parent, "RPCEmu - Choose Data Directory", true);

        // Create preamble label
        String str = "<html><p>Before using RPCEmu for the first time, you must select the directory <br/>"
                + "that contains the folders and files required by the emulator, such as <br>"
                + "ROMs, hard drive images and the HostFS share.</p>"
                + "<p>You can show this dialogue again by holding down the Command key <br/>"
                + "whilst the application is loading.</p></html>";
        JLabel preambleLabel = new JLabel(str);

        // Create choose label
        JLabel chooseLabel = new JLabel("Please choose a directory below:");

        // Create directory line edit
        directoryEdit = new JTextField();
        directoryEdit.setEditable(false);

        // Create directory button
        JButton directoryButton = new JButton("Select...");
        directoryButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                directoryButtonPressed();
            }
        });

        // Create box for line edit and button
        JPanel directoryPanel = new JPanel(new BorderLayout(16, 0));
        directoryPanel.add(directoryEdit, BorderLayout.CENTER);
        directoryPanel.add(directoryButton, BorderLayout.EAST);

        // Create OK and Cancel buttons
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton okButton = new JButton("OK");
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogAccepted();
                dispose();
            }
        });
        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        buttonPanel.add(okButton);
        buttonPanel.add(cancelButton);

        // Set up layout
        JPanel mainPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        mainPanel.add(preambleLabel, gbc);
        gbc.gridy = 1;
        mainPanel.add(chooseLabel, gbc);
        gbc.gridy = 2;
        mainPanel.add(directoryPanel, gbc);
        gbc.gridy = 3;
        mainPanel.add(buttonPanel, gbc);

        Container contentPane = getContentPane();
        contentPane.add(mainPanel, BorderLayout.CENTER);

        pack();
        setLocationRelativeTo(parent);
    }

    private void directoryButtonPressed() {
        JFileChooser folderDialog = new JFileChooser();
        folderDialog.setDialogTitle("Choose Data Directory");
        folderDialog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        if (folderDialog.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File selectedFolder = folderDialog.getSelectedFile();
            directoryEdit.setText(selectedFolder.getAbsolutePath());
        }
    }

    private void dialogAccepted() {
        String selectedFolder = directoryEdit.getText();
        // Add code to save the selected directory path to preferences
    }
}
