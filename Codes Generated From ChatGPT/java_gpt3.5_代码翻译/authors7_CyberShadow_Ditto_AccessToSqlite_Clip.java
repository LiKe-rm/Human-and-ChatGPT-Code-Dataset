import java.nio.charset.StandardCharsets;
import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.CRC32;

public class ProcessCopy {

    private static final String SQLITE_JDBC = "jdbc:sqlite:database.db";

    public static void main(String[] args) {
        // Example usage
        ProcessCopy processCopy = new ProcessCopy();
        processCopy.addClipToDatabase("Sample text");
    }

    public void addClipToDatabase(String text) {
        try (Connection connection = DriverManager.getConnection(SQLITE_JDBC)) {
            long clipId = addClipToMainTable(connection, text);
            addClipToDataTable(connection, clipId, text.getBytes(StandardCharsets.UTF_8));
        } catch (SQLException e) {
            System.err.println("SQLite exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private long addClipToMainTable(Connection connection, String text) throws SQLException {
        String sql = "INSERT INTO Main (lDate, mText, lShortcut, lDontAutoDelete, CRC, bIsGroup, lParentID, csQuickPaste) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
        LocalDateTime now = LocalDateTime.now();
        long crc = calculateCRC32(text.getBytes(StandardCharsets.UTF_8));

        try (PreparedStatement stmt = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            stmt.setLong(1, now.toEpochSecond(java.time.ZoneOffset.UTC));
            stmt.setString(2, text);
            stmt.setInt(3, 0);
            stmt.setInt(4, 0);
            stmt.setLong(5, crc);
            stmt.setInt(6, 0);
            stmt.setLong(7, -1);
            stmt.setString(8, "");

            stmt.executeUpdate();
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                return rs.getLong(1);
            } else {
                throw new SQLException("Failed to insert clip into Main table");
            }
        }
    }

    private void addClipToDataTable(Connection connection, long clipId, byte[] data) throws SQLException {
        String sql = "INSERT INTO Data (lParentID, strClipBoardFormat, ooData) VALUES (?, ?, ?)";

        try (PreparedStatement stmt = connection.prepareStatement(sql)) {
            stmt.setLong(1, clipId);
            stmt.setString(2, "CF_TEXT");

            stmt.setBytes(3, data);
            stmt.executeUpdate();
        }
    }

    private long calculateCRC32(byte[] data) {
        CRC32 crc32 = new CRC32();
        crc32.update(data);
        return crc32.getValue();
    }
}
