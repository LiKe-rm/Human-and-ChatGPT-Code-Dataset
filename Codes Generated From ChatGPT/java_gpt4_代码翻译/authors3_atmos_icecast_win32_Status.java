import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Status extends JPanel {
    private JTable globalStatTable;
    private JLabel gsLabel;
    private JTextField runningForField;

    public Status() {
        setLayout(new BorderLayout());

        globalStatTable = new JTable();
        globalStatTable.setModel(new GlobalStatsTableModel());
        globalStatTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        globalStatTable.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON3) {
                    onGlobalStatTableRightClick(e.getPoint());
                }
            }
        });

        gsLabel = new JLabel("GS");
        // Set your desired font for the gsLabel

        runningForField = new JTextField();
        runningForField.setEditable(false);
        runningForField.setColumns(10);
        // Set your desired font for the runningForField

        JScrollPane globalStatTableScrollPane = new JScrollPane(globalStatTable);
        JPanel bottomPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        bottomPanel.add(new JLabel("Running for:"));
        bottomPanel.add(runningForField);

        add(gsLabel, BorderLayout.NORTH);
        add(globalStatTableScrollPane, BorderLayout.CENTER);
        add(bottomPanel, BorderLayout.SOUTH);
    }

    private void onGlobalStatTableRightClick(Point point) {
        JPopupMenu popupMenu = new JPopupMenu();

        JMenuItem deleteFromGlobalStatsMenuItem = new JMenuItem("Delete from global stats");
        deleteFromGlobalStatsMenuItem.addActionListener(e -> deleteFromGlobalStats());
        popupMenu.add(deleteFromGlobalStatsMenuItem);

        JMenuItem makeThisStatWindowTitleMenuItem = new JMenuItem("Make this stat the window title");
        makeThisStatWindowTitleMenuItem.addActionListener(e -> makeThisStatWindowTitle());
        popupMenu.add(makeThisStatWindowTitleMenuItem);

        popupMenu.show(globalStatTable, point.x, point.y);
    }

    private void deleteFromGlobalStats() {
        int selectedRow = globalStatTable.getSelectedRow();

        if (selectedRow == -1) {
            return;
        }

        String selectedSource = (String) globalStatTable.getModel().getValueAt(selectedRow, 0);
        String selectedName = (String) globalStatTable.getModel().getValueAt(selectedRow, 1);

        if ("Global Stat".equals(selectedSource)) {
            JOptionPane.showMessageDialog(this, "Sorry, but you can't delete this type of stat");
        } else {
            // Add your logic to remove from additional global stats
            ((GlobalStatsTableModel) globalStatTable.getModel()).removeRow(selectedRow);
        }
    }

    private void makeThisStatWindowTitle() {
        int selectedRow = globalStatTable.getSelectedRow();

        if (selectedRow == -1) {
            return;
        }

        String selectedSource = (String) globalStatTable.getModel().getValueAt(selectedRow, 0);
        String selectedName = (String) globalStatTable.getModel().getValueAt(selectedRow, 1);

        // Add your logic to handle making this stat the window title
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Status");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new Status());
        frame.setSize(800, 600);
        frame.setVisible(true);
    }

    private static class GlobalStatsTableModel extends AbstractTableModel {
        private final String[] columnNames = {"Stat Type", "Name", "Value"};
        private Object[][] data = {
                {"Global Stat", "Sample Stat 1", "123"},
		    {"Source 1", "Sample Stat 2", "456"},
       	    {"Source 2", "Sample Stat 3", "789"},
	};
    @Override
    public int getRowCount() {
        return data.length;
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return data[rowIndex][columnIndex];
    }

    @Override
    public String getColumnName(int column) {
        return columnNames[column];
    }

    public void removeRow(int rowIndex) {
        Object[][] newData = new Object[data.length - 1][getColumnCount()];

        for (int i = 0, j = 0; i < data.length; i++) {
            if (i == rowIndex) {
                continue;
            }
            newData[j++] = data[i];
        }

        data = newData;
        fireTableRowsDeleted(rowIndex, rowIndex);
    }
}
}
