import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class About extends JFrame {
    private static final long serialVersionUID = 1L;

    private JList<String> list;
    private DefaultListModel<String> listModel;
    private JButton emailButton;
    private JButton websiteButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            About frame = new About();
            frame.setVisible(true);
        });
    }

    public About() {
        setTitle("About");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 450, 300);

        listModel = new DefaultListModel<>();
        list = new JList<>(listModel);
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(list);
        getContentPane().add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        getContentPane().add(buttonPanel, BorderLayout.SOUTH);
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

        emailButton = new JButton("Email");
        emailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    Desktop.getDesktop().mail(new URI("mailto:sabrogden@users.sourceforge.net"));
                } catch (IOException | URISyntaxException ex) {
                    ex.printStackTrace();
                }
            }
        });
        buttonPanel.add(emailButton);

        websiteButton = new JButton("Website");
        websiteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    Desktop.getDesktop().browse(new URI("https://ditto-cp.sourceforge.io/"));
                } catch (IOException | URISyntaxException ex) {
                    ex.printStackTrace();
                }
            }
        });
        buttonPanel.add(websiteButton);

        initList();
    }

    private void initList() {
        listModel.addElement("Ditto");

        String version = "1.0.0"; // Replace with your application's version
        listModel.addElement("    Version " + version);

        String sqliteVersion = "3.8.11.2"; // Replace with your SQLite version
        listModel.addElement("    SQLite Version " + sqliteVersion);

        File exePath = new File(System.getProperty("user.dir"));
        listModel.addElement("    Exe Path " + exePath.getAbsolutePath());

        File dbPath = new File(System.getProperty("user.home"), "database.db"); // Replace with your database path
        listModel.addElement("    DB Path " + dbPath.getAbsolutePath());

        listModel.addElement("");

        listModel.addElement("Credits");

        listModel.addElement("    Authors - Scott Brogden, sabrogden@users.sourceforge.net");
        listModel.addElement("            - Kevin Edwards, ingenuus@users.sourceforge.net");

        listModel.addElement("");

        listModel.addElement("Addins");

        // Add addins information here
        listModel.addElement("    Addin 1");
        listModel.addElement("    Addin 2");
    }
}
