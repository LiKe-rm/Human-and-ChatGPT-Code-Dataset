import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class TypesTable {
    private static final String DB_URL = "jdbc:ucanaccess://C:/Projects/Ditto/CP_Shared/Release_DLL/97.mdb";
    private Connection conn;
    private int ID;
    private String typeText;

    public TypesTable() {
        try {
            conn = DriverManager.getConnection(DB_URL);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        TypesTable typesTable = new TypesTable();
        typesTable.open();
    }

    public void open() {
        try {
            Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
            ResultSet resultSet = stmt.executeQuery("SELECT * FROM Types");

            while (resultSet.next()) {
                ID = resultSet.getInt("ID");
                typeText = resultSet.getString("TypeText");
                System.out.println("ID: " + ID + ", TypeText: " + typeText);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public boolean deleteAll() {
        try {
            PreparedStatement pstmt = conn.prepareStatement("DELETE FROM Types");
            pstmt.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
