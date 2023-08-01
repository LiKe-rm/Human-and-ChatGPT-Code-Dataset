import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ProgressWindow extends JFrame {
    private static final long serialVersionUID = 1L;
    private JProgressBar progressBar;
    private JButton cancelButton;
    private JLabel textLabel;
    private int minValue, maxValue, step;
    private boolean cancelled;

    public ProgressWindow() {
        setTitle("Progress");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 390, 130);
        getContentPane().setLayout(new BorderLayout(0, 0));

        progressBar = new JProgressBar();
        getContentPane().add(progressBar, BorderLayout.NORTH);

        textLabel = new JLabel("");
        getContentPane().add(textLabel, BorderLayout.CENTER);

        cancelButton = new JButton("Cancel");
        getContentPane().add(cancelButton, BorderLayout.SOUTH);
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                cancelled = true;
                setVisible(false);
            }
        });

        minValue = 0;
        maxValue = 100;
        step = 1;
        cancelled = false;
    }

    public void setRange(int minValue, int maxValue, int step) {
        this.minValue = minValue;
        this.maxValue = maxValue;
        this.step = step;
        progressBar.setMinimum(minValue);
        progressBar.setMaximum(maxValue);
    }

    public int getMinValue() {
        return minValue;
    }

    public int getMaxValue() {
        return maxValue;
    }

    public int getStep() {
        return step;
    }

    public boolean isCancelled() {
        return cancelled;
    }

    public void setCancelled(boolean cancelled) {
        this.cancelled = cancelled;
    }

    public void setText(String text) {
        textLabel.setText(text);
    }

    public void setProgress(int value) {
        progressBar.setValue(value);
    }

    public int offsetProgress(int value) {
        int newPosition = progressBar.getValue() + value;
        progressBar.setValue(newPosition);
        return newPosition;
    }

    public int stepProgress() {
        int newPosition = progressBar.getValue() + step;
        progressBar.setValue(newPosition);
        return newPosition;
    }

    public void showProgressWindow() {
        setVisible(true);
    }

    public void hideProgressWindow() {
        setVisible(false);
    }
}
