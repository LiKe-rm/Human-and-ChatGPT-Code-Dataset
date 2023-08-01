import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class StatsTab extends JPanel {
    private JList<String> sourceList;
    private JTable statsTable;
    private JLabel slsLabel;

    public StatsTab() {
        setLayout(new BorderLayout());

        sourceList = new JList<>();
        sourceList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        sourceList.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                onSourceListSelectionChanged();
            }
        });

        statsTable = new JTable();
        statsTable.setModel(new StatsTableModel());
        statsTable.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON3) {
                    onStatsTableRightClick(e.getPoint());
                }
            }
        });

        slsLabel = new JLabel("SLS");
        // set your desired font for the slsLabel

        JScrollPane sourceListScrollPane = new JScrollPane(sourceList);
        JScrollPane statsTableScrollPane = new JScrollPane(statsTable);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, sourceListScrollPane, statsTableScrollPane);
        splitPane.setDividerLocation(200);

        add(slsLabel, BorderLayout.NORTH);
        add(splitPane, BorderLayout.CENTER);
    }

    private void onSourceListSelectionChanged() {
        // Add your logic to handle source list selection change
    }

    private void onStatsTableRightClick(Point point) {
        JPopupMenu popupMenu = new JPopupMenu();

        JMenuItem addToGlobalStatsMenuItem = new JMenuItem("Add to global stat list");
        addToGlobalStatsMenuItem.addActionListener(e -> addToGlobalStats());
        popupMenu.add(addToGlobalStatsMenuItem);

        popupMenu.show(statsTable, point.x, point.y);
    }

    private void addToGlobalStats() {
        int selectedRow = statsTable.getSelectedRow();
        int selectedSourceIndex = sourceList.getSelectedIndex();

        if (selectedRow == -1 || selectedSourceIndex == -1) {
            return;
        }

        String selectedSource = sourceList.getModel().getElementAt(selectedSourceIndex);
        String selectedStat = (String) statsTable.getModel().getValueAt(selectedRow, 0);

        // Add your logic to handle adding to global stats
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Stats Tab");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new StatsTab());
        frame.setSize(800, 600);
        frame.setVisible(true);
    }

    private static class StatsTableModel extends AbstractTableModel {
        private final String[] columnNames = {"Statistic", "Value"};
        private final Object[][] data = {
                {"Sample Stat 1", "Sample Value 1"},
                {"Sample Stat 2", "Sample Value 2"},
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
    }
}
