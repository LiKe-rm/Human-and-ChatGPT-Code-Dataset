import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class GroupCombo extends JComboBox<String> {
    private long skipGroupID;

    public GroupCombo() {
        this.skipGroupID = -1;
        fillCombo();
    }

    public void fillCombo() {
        removeAllItems();
        addItem("-No Group-");
        setItemData(-1);
        fillCombo(-1, 1);
    }

    private void fillCombo(long parentID, long spaces) {
        try {
            Connection conn = App.getDBConnection();
            PreparedStatement ps = conn.prepareStatement("SELECT lID, mText FROM Main WHERE bIsGroup = 1 AND lParentID = ?");
            ps.setLong(1, parentID);
            ResultSet rs = ps.executeQuery();
            String spacesStr = " ".repeat((int) spaces);

            while (rs.next()) {
                if (rs.getLong("lID") != skipGroupID) {
                    String text = spacesStr + rs.getString("mText");
                    addItem(text);
                    setItemData(rs.getLong("lID"));
                    fillCombo(rs.getLong("lID"), spaces + 1);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void setItemData(long itemData) {
        putClientProperty("ItemData_" + getSelectedIndex(), itemData);
    }

    public boolean setCurSelOnItemData(long itemData) {
        int itemCount = getItemCount();

        for (int i = 0; i < itemCount; i++) {
            if (getItemData(i) == itemData) {
                setSelectedIndex(i);
                return true;
            }
        }

        setSelectedIndex(-1);
        return false;
    }

    public long getItemData(int index) {
        Object data = getClientProperty("ItemData_" + index);
        return data != null ? (long) data : -1;
    }

    public long getItemDataFromCurSel() {
        return getItemData(getSelectedIndex());
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("GroupCombo");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(400, 200);

            JPanel panel = new JPanel();
            GroupCombo groupCombo = new GroupCombo();
            panel.add(groupCombo);
            frame.add(panel);

            frame.setVisible(true);
        });
    }
}
