import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;

public class OptionFriendsPanel extends JPanel {

    private JTable table;
    private DefaultTableModel tableModel;
    private JButton editButton, removeButton;
    private JCheckBox logSendReceiveErrors, disableReceive;
    private JTextField placeOnClipboard, password, additionalPasswords;

    public OptionFriendsPanel() {
        setLayout(new BorderLayout());

        createTable();
        createButtons();
        createForm();

        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(new JScrollPane(table), BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(editButton);
        buttonPanel.add(removeButton);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        add(mainPanel, BorderLayout.CENTER);
        add(createForm(), BorderLayout.SOUTH);
    }

    private void createTable() {
        tableModel = new DefaultTableModel(new String[]{"#", "Send All Copies", "IP/Name", "Description"}, 0);
        table = new JTable(tableModel);
        table.setFillsViewportHeight(true);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        table.getColumnModel().getColumn(0).setMaxWidth(40);
        table.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    editSelectedItem();
                }
            }
        });
    }

    private void createButtons() {
        editButton = new JButton("Edit");
        editButton.addActionListener(e -> editSelectedItem());

        removeButton = new JButton("Remove");
        removeButton.addActionListener(e -> removeSelectedItem());
    }

    private JPanel createForm() {
        JPanel formPanel = new JPanel();
        formPanel.setLayout(new GridLayout(4, 2));

        logSendReceiveErrors = new JCheckBox("Log Send/Receive Errors");
        disableReceive = new JCheckBox("Disable Receive");
        placeOnClipboard = new JTextField(20);
        password = new JTextField(20);
        additionalPasswords = new JTextField(20);

        formPanel.add(new JLabel("Place on Clipboard:"));
        formPanel.add(placeOnClipboard);
        formPanel.add(new JLabel("Password:"));
        formPanel.add(password);
        formPanel.add(new JLabel("Additional Passwords:"));
        formPanel.add(additionalPasswords);
        formPanel.add(logSendReceiveErrors);
        formPanel.add(disableReceive);

        return formPanel;
    }

    private void editSelectedItem() {
        int selectedRow = table.getSelectedRow();
        if (selectedRow >= 0) {
            FriendDetailsDialog dialog = new FriendDetailsDialog();
            dialog.setFriendDetails(new FriendDetails(
                    (boolean) tableModel.getValueAt(selectedRow, 1),
                    (String) tableModel.getValueAt(selectedRow, 2),
                    (String) tableModel.getValueAt(selectedRow, 3)
            ));
            if (dialog.showDialog()) {
                tableModel.setValueAt(dialog.getFriendDetails().sendAll, selectedRow, 1);
                tableModel.setValueAt(dialog.getFriendDetails().ip, selectedRow, 2);
                tableModel.setValueAt(dialog.getFriendDetails().description, selectedRow, 3);
            }
        }
    }

    private void removeSelectedItem() {
        int selectedRow = table.getSelectedRow();
        if (selectedRow >= 0) {
            tableModel.removeRow(selectedRow);
        }
    }

    public void addFriend(FriendDetails friendDetails) {
        tableModel.addRow(new Object[]{
                tableModel.getRowCount() + 1,
                friendDetails.sendAll,
                friendDetails.ip,
                friendDetails.description
    });
}

public static void main(String[] args) {
    JFrame frame = new JFrame("Option Friends");
    OptionFriendsPanel optionFriendsPanel = new OptionFriendsPanel();
    frame.add(optionFriendsPanel);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.pack();
    frame.setLocationRelativeTo(null);
    frame.setVisible(true);
}
}

class FriendDetails {
    boolean sendAll;
    String ip;
    String description;
    public FriendDetails(boolean sendAll, String ip, String description) {
        this.sendAll = sendAll;
        this.ip = ip;
        this.description = description;
    }
    public FriendDetailsDialog() {
        setTitle("Friend Details");
        setModal(true);

        ipField = new JTextField(20);
        descriptionField = new JTextField(20);
        sendAllBox = new JCheckBox("Send All Copies");

        JPanel formPanel = new JPanel(new GridLayout(3, 2));
        formPanel.add(new JLabel("IP/Name:"));
        formPanel.add(ipField);
        formPanel.add(new JLabel("Description:"));
        formPanel.add(descriptionField);
        formPanel.add(sendAllBox);

        JButton okButton = new JButton("OK");
        okButton.addActionListener(e -> {
            confirmed = true;
            setVisible(false);
        });

        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(e -> setVisible(false));

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(okButton);
        buttonPanel.add(cancelButton);

        setLayout(new BorderLayout());
        add(formPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
        pack();
    }

    public void setFriendDetails(FriendDetails friendDetails) {
        ipField.setText(friendDetails.ip);
        descriptionField.setText(friendDetails.description);
        sendAllBox.setSelected(friendDetails.sendAll);
    }

    public FriendDetails getFriendDetails() {
        return new FriendDetails(sendAllBox.isSelected(), ipField.getText(), descriptionField.getText());
    }

    public boolean showDialog() {
        confirmed = false;
        setLocationRelativeTo(null);
        setVisible(true);
        return confirmed;
    }
}