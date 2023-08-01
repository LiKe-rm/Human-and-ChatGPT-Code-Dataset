import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class TextViewFile extends JPanel {
    private JTextArea textArea;
    private JScrollPane scrollPane;
    private File currentFile;

    public TextViewFile() {
        setLayout(new BorderLayout());

        textArea = new JTextArea();
        scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("TextViewFile");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(600, 400);

            TextViewFile textViewFile = new TextViewFile();
            frame.add(textViewFile);

            frame.setVisible(true);
        });
    }

    public boolean openFile(String fileName) {
        Path path = Paths.get(fileName);
        if (Files.exists(path)) {
            currentFile = path.toFile();

            List<String> lines;
            try {
                lines = Files.readAllLines(path, StandardCharsets.UTF_8);
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }

            clearFile();

            for (String line : lines) {
                textArea.append(line);
                textArea.append("\n");
            }

            updateMetrics();
            return true;
        }

        return false;
    }

    public boolean clearFile() {
        textArea.setText("");
        updateMetrics();
        return true;
    }

    private void updateMetrics() {
        int lineCount = textArea.getLineCount();
        int longestLine = getLongestLineLength();

        // Perform additional processing if needed
    }

    private int getLongestLineLength() {
        String[] lines = textArea.getText().split("\n");
        int longestLine = 0;

        for (String line : lines) {
            if (line.length() > longestLine) {
                longestLine = line.length();
            }
        }

        return longestLine;
    }
}
