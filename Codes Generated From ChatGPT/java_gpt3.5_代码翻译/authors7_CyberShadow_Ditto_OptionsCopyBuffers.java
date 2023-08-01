import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CopyBufferOptions extends JFrame {
    private JCheckBox playSound1, playSound2, playSound3;
    private JTextField copyBuffer1, pasteBuffer1, cutBuffer1;
    private JTextField copyBuffer2, pasteBuffer2, cutBuffer2;
    private JTextField copyBuffer3, pasteBuffer3, cutBuffer3;
    private JButton applyButton;

    public CopyBufferOptions() {
        setTitle("Copy Buffer Options");
        setLayout(new GridLayout(4, 4));

        add(new JLabel("Copy Buffer"));
        add(new JLabel("Paste Buffer"));
        add(new JLabel("Cut Buffer"));
        add(new JLabel("Play Sound"));

        copyBuffer1 = new JTextField(10);
        pasteBuffer1 = new JTextField(10);
        cutBuffer1 = new JTextField(10);
        playSound1 = new JCheckBox();

        copyBuffer2 = new JTextField(10);
        pasteBuffer2 = new JTextField(10);
        cutBuffer2 = new JTextField(10);
        playSound2 = new JCheckBox();

        copyBuffer3 = new JTextField(10);
        pasteBuffer3 = new JTextField(10);
        cutBuffer3 = new JTextField(10);
        playSound3 = new JCheckBox();

        add(copyBuffer1);
        add(pasteBuffer1);
        add(cutBuffer1);
        add(playSound1);

        add(copyBuffer2);
        add(pasteBuffer2);
        add(cutBuffer2);
        add(playSound2);

        add(copyBuffer3);
        add(pasteBuffer3);
        add(cutBuffer3);
        add(playSound3);

        applyButton = new JButton("Apply");
        applyButton.addActionListener(new ApplyButtonListener());
        add(applyButton);

        pack();
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    private class ApplyButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            // Add your logic for applying changes to the copy, paste, and cut buffers.
            // For example, you can validate the input and save the configurations.

            // If there's a conflict or invalid input, show an error message:
            // JOptionPane.showMessageDialog(null, "Error message", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            CopyBufferOptions options = new CopyBufferOptions();
            options.setVisible(true);
        });
    }
}
