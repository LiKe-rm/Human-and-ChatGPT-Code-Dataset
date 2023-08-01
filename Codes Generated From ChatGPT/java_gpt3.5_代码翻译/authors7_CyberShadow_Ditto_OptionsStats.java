import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Date;

public class OptionsStats extends JPanel {
    private final JTextField allCopiesField;
    private final JTextField allPastesField;
    private final JTextField allDateField;
    private final JTextField tripCopiesField;
    private final JTextField tripDateField;
    private final JTextField tripPastesField;
    private final JTextField savedCopiesField;
    private final JTextField savedCopyDataField;
    private final JTextField databaseSizeField;
    private final JTextField clipsSentField;
    private final JTextField clipsReceivedField;
    private final JTextField lastStartedField;

    public OptionsStats() {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        // Add labels and text fields
        allCopiesField = createLabelAndTextField("All Copies", 0);
        allPastesField = createLabelAndTextField("All Pastes", 1);
        allDateField = createLabelAndTextField("All Date", 2);
        tripCopiesField = createLabelAndTextField("Trip Copies", 3);
        tripDateField = createLabelAndTextField("Trip Date", 4);
        tripPastesField = createLabelAndTextField("Trip Pastes", 5);
        savedCopiesField = createLabelAndTextField("Saved Copies", 6);
        savedCopyDataField = createLabelAndTextField("Saved Copy Data", 7);
        databaseSizeField = createLabelAndTextField("Database Size", 8);
        clipsSentField = createLabelAndTextField("Clips Sent", 9);
        clipsReceivedField = createLabelAndTextField("Clips Received", 10);
        lastStartedField = createLabelAndTextField("Last Started", 11);

        // Add buttons
        c.gridx = 0;
        c.gridy = 12;
        c.gridwidth = 1;
        c.fill = GridBagConstraints.HORIZONTAL;
        JButton resetCountsButton = new JButton("Reset Counts");
        resetCountsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onResetCounts();
            }
        });
        add(resetCountsButton, c);

        c.gridx = 1;
        c.gridy = 12;
        c.gridwidth = 1;
        c.fill = GridBagConstraints.HORIZONTAL;
        JButton removeAllButton = new JButton("Remove All");
        removeAllButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onRemoveAll();
            }
        });
        add(removeAllButton, c);

        updateFields();
    }

    private JTextField createLabelAndTextField(String labelText, int gridY) {
        GridBagConstraints c = new GridBagConstraints();

        c.gridx = 0;
        c.gridy = gridY;
        c.gridwidth = 1;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.weightx = 0.0;
        JLabel label = new JLabel(labelText);
        add(label, c);

        c.gridx = 1;
        c.gridy = gridY;
        c.gridwidth = 1;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.weightx = 1.0;
        JTextField textField = new JTextField();
        textField.setEditable(false);
        add(textField, c);

        return textField;
    }

    private void updateFields() {
        // TODO: Update fields with data from the application or database.
        // Example: allCopiesField.setText(Integer.toString(getAllCopies()));
    }

    private void onResetCounts() {
        // TODO: Reset trip counts in the application or database.
        // Example: setTripCopyCount(0);
        // Example: setTripPasteCount(0);
        // Example: setTripDate(0);
    }
    tripDateField.setText("");
    tripCopiesField.setText("");
    tripPastesField.setText("");

    updateFields();
}

private void onRemoveAll() {
    int result = JOptionPane.showConfirmDialog(this,
            "This will remove all Copy Entries!\n\nContinue?",
            "Warning", JOptionPane.YES_NO_OPTION);

    if (result == JOptionPane.YES_OPTION) {
        // TODO: Remove all copy entries from the application or database.
        // Example: deleteAllIDs();

        savedCopiesField.setText("");
        savedCopyDataField.setText("");

        updateDatabaseSizeField();

        updateFields();
    }
}

private void updateDatabaseSizeField() {
    // TODO: Calculate the database size.
    // Example: int databaseSize = getDatabaseSize();

    // Assuming the database is a file:
    Path databasePath = Paths.get("path/to/your/database/file");
    long fileSizeInKB = 0;

    try {
        fileSizeInKB = Files.size(databasePath) / 1024;
    } catch (Exception e) {
        e.printStackTrace();
    }

    databaseSizeField.setText(fileSizeInKB + " KB");
}

public static void main(String[] args) {
    JFrame frame = new JFrame("Options Stats");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.getContentPane().add(new OptionsStats());
    frame.pack();
    frame.setLocationRelativeTo(null);
    frame.setVisible(true);
}
