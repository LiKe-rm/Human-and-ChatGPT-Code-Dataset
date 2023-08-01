import java.sql.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class DataTable {

    private long lID;
    private long lDataID;
    private String strClipBoardFormat;
    private byte[] ooData;
    private Connection connection;

    public DataTable(Connection connection) {
        this.connection = connection;
    }

    public String getDefaultDBName() {
        return "jdbc:sqlite:database.db";
    }

    public String getDefaultSQL() {
        return "SELECT * FROM Data";
    }

    public void addNew() throws SQLException {
        PreparedStatement stmt = connection.prepareStatement("INSERT INTO Data (lDataID, strClipBoardFormat, ooData) VALUES (?, ?, ?)", Statement.RETURN_GENERATED_KEYS);
        stmt.setLong(1, lDataID);
        stmt.setString(2, strClipBoardFormat);
        stmt.setBinaryStream(3, new ByteArrayInputStream(ooData));
        stmt.executeUpdate();

        ResultSet rs = stmt.getGeneratedKeys();
        if (rs.next()) {
            lID = rs.getLong(1);
        }
    }

    public byte[] takeData() {
        byte[] data = ooData;
        ooData = null;
        return data;
    }

    public boolean replaceData(byte[] newData) {
        ooData = newData;
        return true;
    }

    public boolean setData(byte[] newData, int size) {
        ooData = new byte[size];
        System.arraycopy(newData, 0, ooData, 0, size);
        return true;
    }

    public byte[] loadData() {
        return ooData.clone();
    }

    public void copyRec(DataTable src) {
        strClipBoardFormat = src.strClipBoardFormat;
        setData(src.ooData, src.ooData.length);
    }

    public boolean deleteAll() {
        boolean result = false;
        try {
            Statement stmt = connection.createStatement();
            stmt.execute("DELETE FROM Data");
            result = true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    public void open(String format, Object... args) throws SQLException {
        String sql = String.format(format, args);
        open(sql);
    }

    public void open(String sql) throws SQLException {
        Statement stmt = connection.createStatement();
        ResultSet rs = stmt.executeQuery(sql);
        while (rs.next()) {
            lID = rs.getLong("lID");
            lDataID = rs.getLong("lDataID");
            strClipBoardFormat = rs.getString("strClipBoardFormat");
            ooData = rs.getBytes("ooData");
        }
    }

    public boolean dataEqual(byte[] data) {
        if (data.length != ooData.length) {
            return false;
        }
        for (int i = 0; i < data.length; i++) {
            if (data[i] != ooData[i]) {
                return false;
            }
        }
        return true;
    }
}
