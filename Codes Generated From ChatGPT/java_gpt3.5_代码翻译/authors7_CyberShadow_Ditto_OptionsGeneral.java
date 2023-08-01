import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class OptionsGeneral extends JFrame {
    private JComboBox<String> languageComboBox;
    private JTextField maxClipSizeTextField;
    private JTextField expireAfterTextField;
    private JTextField maxSavedCopiesTextField;
    private JCheckBox runOnStartupCheckBox;
    private JCheckBox showIconInSysTrayCheckBox;
    private JCheckBox maximumCheckCheckBox;
    private JCheckBox expireCheckBox;
    private JCheckBox allowDuplicatesCheckBox;
    private JCheckBox updateTimeOnPasteCheckBox;
    private JCheckBox saveMultiPasteCheckBox;

    public OptionsGeneral() {
        setTitle("Options General");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        runOnStartupCheckBox = new JCheckBox("Run on startup");
        showIconInSysTrayCheckBox = new JCheckBox("Show icon in system tray");
        maximumCheckCheckBox = new JCheckBox("Maximum check");
        expireCheckBox = new JCheckBox("Expire");
        allowDuplicatesCheckBox = new JCheckBox("Allow duplicates");
        updateTimeOnPasteCheckBox = new JCheckBox("Update time on paste");
        saveMultiPasteCheckBox = new JCheckBox("Save multi-paste");

        maxClipSizeTextField = new JTextField(20);
        expireAfterTextField = new JTextField(20);
        maxSavedCopiesTextField = new JTextField(20);

        languageComboBox = new JComboBox<>();
        languageComboBox.addItem("English");
        languageComboBox.addItem("Spanish");
        languageComboBox.addItem("French");
        languageComboBox.addItem("German");
        languageComboBox.addItem("Russian");

        JButton compactAndRepairButton = new JButton("Compact and Repair");
        compactAndRepairButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                compactAndRepair();
            }
        });

        add(runOnStartupCheckBox);
        add(showIconInSysTrayCheckBox);
        add(maximumCheckCheckBox);
        add(expireCheckBox);
        add(allowDuplicatesCheckBox);
        add(updateTimeOnPasteCheckBox);
        add(saveMultiPasteCheckBox);
        add(maxClipSizeTextField);
        add(expireAfterTextField);
        add(maxSavedCopiesTextField);
        add(languageComboBox);
        add(compactAndRepairButton);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public void compactAndRepair() {
        // Implement your compact and repair functionality here.
        System.out.println("Compact and Repair executed");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new OptionsGeneral();
            }
        });
    }
}
