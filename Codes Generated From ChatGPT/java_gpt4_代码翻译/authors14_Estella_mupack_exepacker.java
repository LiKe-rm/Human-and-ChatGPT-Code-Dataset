import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("File Compressor");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(new Dimension(400, 300));

        JPanel panel = new JPanel(new BorderLayout());

        JTextArea consoleTextArea = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(consoleTextArea);
        panel.add(scrollPane, BorderLayout.CENTER);

        PrintStream consoleStream = new PrintStream(new CustomOutputStream(consoleTextArea));
        System.setOut(consoleStream);
        System.setErr(consoleStream);

        JButton button = new JButton("Select file to compress");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                int returnValue = fileChooser.showOpenDialog(null);
                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = fileChooser.getSelectedFile();
                    try {
                        compressFile(selectedFile);
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
            }
        });

        panel.add(button, BorderLayout.SOUTH);

        frame.setContentPane(panel);
        frame.setVisible(true);
    }

    public static void compressFile(File file) throws IOException {
        // Implement your file compression logic here
        System.out.println("Compressing file: " + file.getAbsolutePath());
    }
}

class CustomOutputStream extends OutputStream {
    private JTextArea textArea;

    public CustomOutputStream(JTextArea textArea) {
        this.textArea = textArea;
    }

    @Override
    public void write(int b) throws IOException {
        textArea.append(String.valueOf((char) b));
        textArea.setCaretPosition(textArea.getDocument().getLength());
    }
}
