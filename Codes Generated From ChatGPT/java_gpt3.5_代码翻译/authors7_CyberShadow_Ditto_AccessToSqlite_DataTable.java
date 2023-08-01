import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DataTable {

    private final AccessToSqlite accessToSqlite;
    private long lID;
    private long lDataID;
    private String strClipBoardFormat;
    private byte[] ooData;

    public DataTable() {
        accessToSqlite = new AccessToSqlite();
    }

    public ResultSet getDefaultSQL() throws SQLException {
        return accessToSqlite.query("SELECT * FROM Data");
    }

    public void loadFields(ResultSet resultSet) throws SQLException {
        lID = resultSet.getLong("lID");
        lDataID = resultSet.getLong("lDataID");
        strClipBoardFormat = resultSet.getString("strClipBoardFormat");
        ooData = resultSet.getBytes("ooData");
    }

    public byte[] takeData() {
        byte[] data = ooData;
        ooData = null;
        return data;
    }

    public byte[] loadData() {
        if (ooData == null || ooData.length == 0) {
            return null;
        }

        byte[] data = new byte[ooData.length];
        System.arraycopy(ooData, 0, data, 0, ooData.length);
        return data;
    }

    public void open(Connection connection, String sqlFormat, Object... parameters) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(sqlFormat);

        for (int i = 0; i < parameters.length; i++) {
            preparedStatement.setObject(i + 1, parameters[i]);
        }

        ResultSet resultSet = preparedStatement.executeQuery();

        if (resultSet.next()) {
            loadFields(resultSet);
        }
    }

    // Getters and setters
    public long getLID() {
        return lID;
    }

    public long getLDataID() {
        return lDataID;
    }

    public String getStrClipBoardFormat() {
        return strClipBoardFormat;
    }

    public byte[] getOoData() {
        return ooData;
    }

    public void setLID(long lID) {
        this.lID = lID;
    }

    public void setLDataID(long lDataID) {
        this.lDataID = lDataID;
    }

    public void setStrClipBoardFormat(String strClipBoardFormat) {
        this.strClipBoardFormat = strClipBoardFormat;
    }

    public void setOoData(byte[] ooData) {
        this.ooData = ooData;
    }
}
