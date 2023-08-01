import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FileTransferProgressDlg extends JDialog {
    private boolean cancelled;
    private final JProgressBar progressSingleFile;
    private final JProgressBar progressAllFiles;
    private final JLabel message;
    private final JLabel copyingFile;
    private final JButton cancelButton;

    public FileTransferProgressDlg(Frame parent) {
        super(parent, true);

        setTitle("File Transfer Progress");

        cancelled = false;

        progressSingleFile = new JProgressBar();
        progressAllFiles = new JProgressBar();
        message = new JLabel();
        copyingFile = new JLabel();
        cancelButton = new JButton("Cancel");

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        setLayout(new GridLayout(6, 1));

        add(new JLabel("Status:"));
        add(message);
        add(new JLabel("Copying:"));
        add(copyingFile);
        add(progressSingleFile);
        add(progressAllFiles);
        add(cancelButton);

        pack();

        setLocationRelativeTo(parent);
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    }

    public boolean isCancelled() {
        return cancelled;
    }

    private void onCancel() {
        cancelled = true;
    }

    public void setMessage(String msg) {
        message.setText(msg);
    }

    public void setFileMessage(String msg) {
        copyingFile.setText(msg);
    }

    public void setNumFiles(int numFiles) {
        progressAllFiles.setMinimum(0);
        progressAllFiles.setMaximum(numFiles);
        progressAllFiles.setValue(0);

        progressSingleFile.setMinimum(0);
        progressSingleFile.setMaximum(100);
        progressSingleFile.setValue(0);
    }

    public void resetSingleFileProgress() {
        progressSingleFile.setValue(0);
    }

    public void stepAllFiles() {
        progressAllFiles.setValue(progressAllFiles.getValue() + 1);
    }

    public void setSingleFilePos(int pos) {
        progressSingleFile.setValue(pos);
    }

    public void pumpMessages() {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                // This will process pending events in the Swing event queue.
            }
        });
    }
}
