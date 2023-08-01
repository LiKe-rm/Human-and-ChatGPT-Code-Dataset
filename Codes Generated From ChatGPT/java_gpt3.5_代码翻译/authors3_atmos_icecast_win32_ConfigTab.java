import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;

public class ConfigTab extends JPanel {
    private JTextArea configArea;
    private String config;
    private String configFile;

    public ConfigTab(String configFile) {
        this.configFile = configFile;

        setLayout(new BorderLayout());
        configArea = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(configArea);
        add(scrollPane, BorderLayout.CENTER);

        configArea.addFocusListener(new FocusAdapter() {
            @Override
            public void focusLost(FocusEvent e) {
                saveConfiguration();
            }
        });

        loadConfiguration();
    }

    private void loadConfiguration() {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(configFile));
            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
            }
            configArea.setText(sb.toString());
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveConfiguration() {
        config = configArea.getText();
        if (config != null && !config.isEmpty()) {
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(configFile));
                writer.write(config);
                writer.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
