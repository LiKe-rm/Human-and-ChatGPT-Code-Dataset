import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class GlobalClips extends JFrame {
    private JTable table;
    private DefaultTableModel model;
    private ArrayList<HotKey> hotKeys;

    public GlobalClips() {
        setTitle("Global Clips");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 450, 300);
        getContentPane().setLayout(new BorderLayout(0, 0));

        JScrollPane scrollPane = new JScrollPane();
        getContentPane().add(scrollPane, BorderLayout.CENTER);

        hotKeys = new ArrayList<>();

        model = new DefaultTableModel();
        model.addColumn("Description");
        model.addColumn("Hot Key");
        model.addColumn("Registered");

        table = new JTable(model);
        scrollPane.setViewportView(table);
        table.setFillsViewportHeight(true);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        table.getColumnModel().getColumn(0).setPreferredWidth(200);
        table.getColumnModel().getColumn(1).setPreferredWidth(100);
        table.getColumnModel().getColumn(2).setPreferredWidth(100);

        loadItems();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                onClose();
            }
        });
    }

    public void loadItems() {
        model.setRowCount(0);
        int rowCount = 0;
        for (HotKey hotKey : hotKeys) {
            if (hotKey.getKey() <= 0) {
                continue;
            }

            Object[] rowData = new Object[3];
            rowData[0] = hotKey.getName();
            rowData[1] = hotKey.getHotKeyDisplay();
            rowData[2] = hotKey.isRegistered() ? "Yes" : "Error";

            model.addRow(rowData);
            rowCount++;
        }
    }

    public void onClose() {
        dispose();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                GlobalClips frame = new GlobalClips();
                frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}
