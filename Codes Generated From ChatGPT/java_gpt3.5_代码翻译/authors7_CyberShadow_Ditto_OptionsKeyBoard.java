import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class OptionsKeyboardDialog extends JDialog {
    private JPanel contentPane;
    private JButton buttonOK;
    private JButton buttonCancel;
    private List<JCheckBox> checkBoxList;
    private List<JTextField> textFieldList;

    public OptionsKeyboardDialog() {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonOK);

        buttonOK.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });

        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        pack();
        setLocationRelativeTo(null);

        initUI();
    }

    private void initUI() {
        checkBoxList = new ArrayList<>();
        textFieldList = new ArrayList<>();

        for (int i = 1; i <= 10; i++) {
            JCheckBox checkBox = new JCheckBox("Win " + i);
            checkBoxList.add(checkBox);
            JTextField textField = new JTextField(10);
            textFieldList.add(textField);
        }

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.anchor = GridBagConstraints.WEST;

        for (int i = 0; i < checkBoxList.size(); i++) {
            contentPane.add(checkBoxList.get(i), gbc);
            gbc.gridx++;
            contentPane.add(textFieldList.get(i), gbc);
            gbc.gridx = 0;
            gbc.gridy++;
        }
    }

    private void onOK() {
        // Save settings and close the dialog
        dispose();
    }

    private void onCancel() {
        // Close the dialog without saving changes
        dispose();
    }

    public static void main(String[] args) {
        OptionsKeyboardDialog dialog = new OptionsKeyboardDialog();
        dialog.setVisible(true);
    }
}
