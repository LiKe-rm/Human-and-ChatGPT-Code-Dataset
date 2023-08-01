import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MainTable {

    private final AccessToSqlite accessToSqlite;
    private long lID;
    private long lDate;
    private String strText;
    private long lShortCut;
    private long lDontAutoDelete;
    private long lTotalCopySize;
    private boolean bIsGroup;
    private long lParentID;
    private double dOrder;
    private long lDataID;
    private boolean bindFields;

    public MainTable() {
        accessToSqlite = new AccessToSqlite();
        bindFields = true;
    }

    public ResultSet getDefaultSQL() throws SQLException {
        return accessToSqlite.query("SELECT * FROM Main");
    }

    public void loadFields(ResultSet resultSet) throws SQLException {
        if (bindFields) {
            lID = resultSet.getLong("lID");
            lDate = resultSet.getLong("lDate");
            strText = resultSet.getString("mText");
            lShortCut = resultSet.getLong("lShortCut");
            lDontAutoDelete = resultSet.getLong("lDontAutoDelete");
            lTotalCopySize = resultSet.getLong("lTotalCopySize");
            bIsGroup = resultSet.getBoolean("bIsGroup");
            lParentID = resultSet.getLong("lParentID");
            dOrder = resultSet.getDouble("dOrder");
            lDataID = resultSet.getLong("lDataID");
        }
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

    public long getLDate() {
        return lDate;
    }

    public String getStrText() {
        return strText;
    }

    public long getLShortCut() {
        return lShortCut;
    }

    public long getLDontAutoDelete() {
        return lDontAutoDelete;
    }

    public long getLTotalCopySize() {
        return lTotalCopySize;
    }

    public boolean isBIsGroup() {
        return bIsGroup;
    }

    public long getLParentID() {
        return lParentID;
    }

    public double getDOrder() {
        return dOrder;
    }

    public long getLDataID() {
        return lDataID;
    }

    public void setLID(long lID) {
        this.lID = lID;
    }

    public void setLDate(long lDate) {
        this.lDate = lDate;
    }

    public void setStrText(String strText) {
        this.strText = strText;
    }

    public void setLShortCut(long lShortCut) {
        this.lShortCut = lShortCut;
    }

    public void setLDontAutoDelete(long lDontAutoDelete) {
        this.lDontAutoDelete = lDontAutoDelete;
    }

    public void setLTotalCopySize(long lTotalCopySize) {
        this.lTotalCopySize = lTotalCopySize;
    }

    public void setBIsGroup(boolean bIsGroup) {
        this.bIsGroup = bIsGroup;
    }

    public void setLParentID(long lParentID) {
        this.lParentID = lParentID
    }

    public void setDOrder(double dOrder) {
        this.dOrder = dOrder;
    }

    public void setLDataID(long lDataID) {
        this.lDataID = lDataID;
    }

    public boolean isBindFields() {
        return bindFields;
    }

    public void setBindFields(boolean bindFields) {
        this.bindFields = bindFields;
    }
}