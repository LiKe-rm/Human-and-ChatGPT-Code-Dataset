// Import necessary libraries
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class AboutDialog extends JDialog {
    private static final String VERSION = "1.0.0";

    public AboutDialog(JFrame parent) {
        super(parent, "About RPCEmu", true);

        // Image label
        JLabel imageLabel = new JLabel();
        ImageIcon icon = new ImageIcon(getClass().getResource("/rpcemu_icon.png"));
        imageLabel.setIcon(new ImageIcon(icon.getImage().getScaledInstance(48, -1, Image.SCALE_SMOOTH)));
        imageLabel.setAlignmentX(Component.TOP_ALIGNMENT);

        // Date string based on build date
        String dateStr = "2023 Apr 15"; // Replace with build date

        // Text label string containing year from dateStr
        String str = String.format("<html><h1>RPCEmu</h1>"
                + "<h2>%s</h2>"
                + "<p>Copyright 2005-%s RPCEmu Developers</p>"
                + "<p>RPCEmu is released under the terms of the "
                + "GNU General Public License, Version 2. Please see the file "
                + "COPYING for more details.</p></html>", VERSION, dateStr.substring(dateStr.length() - 4));

        // Text label
        JLabel textLabel = new JLabel(str);
        textLabel.setOpaque(false);

        // Create Buttons
        JButton okButton = new JButton("OK");
        okButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        // Set up layout
        JPanel mainPanel = new JPanel(new BorderLayout(16, 0));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(16, 16, 16, 16));
        mainPanel.add(imageLabel, BorderLayout.WEST);
        mainPanel.add(textLabel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(okButton);

        Container contentPane = getContentPane();
        contentPane.add(mainPanel, BorderLayout.CENTER);
        contentPane.add(buttonPanel, BorderLayout.SOUTH);

        pack();
        setResizable(false);
        setLocationRelativeTo(parent);
    }
}
