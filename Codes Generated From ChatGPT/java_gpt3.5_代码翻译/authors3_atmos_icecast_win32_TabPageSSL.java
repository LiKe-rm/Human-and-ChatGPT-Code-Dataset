import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabPageSSL extends JPanel {

    private JLabel label;
    private JButton button;

    public TabPageSSL() {
        initComponents();
    }

    private void initComponents() {
        setLayout(new BorderLayout());

        // Initialize the label and add it to the panel
        label = new JLabel("Initial text");
        label.setHorizontalAlignment(SwingConstants.CENTER);
        add(label, BorderLayout.CENTER);

        // Initialize the button and add it to the panel
        button = new JButton("Update Text");
        button.addActionListener(new ButtonClickListener());
        add(button, BorderLayout.SOUTH);
    }

    private class ButtonClickListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            label.setText("Text updated by clicking the button");
            processActionEvent(e);
        }
    }

    @Override
    protected void processComponentEvent(ComponentEvent e) {
        // Forward ComponentEvent to the parent (if needed)
        Container parent = getParent();
        if (parent != null) {
            parent.dispatchEvent(e);
        } else {
            super.processComponentEvent(e);
        }
    }

    @Override
    protected void processActionEvent(ActionEvent e) {
        // Forward ActionEvent to the parent (if needed)
        Container parent = getParent();
        if (parent != null) {
            parent.dispatchEvent(e);
        } else {
            super.processActionEvent(e);
        }
    }

    // Add other event handlers if needed
}
