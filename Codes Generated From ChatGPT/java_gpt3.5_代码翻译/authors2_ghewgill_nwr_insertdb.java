import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.TimeZone;

public class InsertDb {
    private static String station = null;

    private static String timestr(long timeInMillis, boolean seconds) {
        SimpleDateFormat formatter;
        if (seconds) {
            formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        } else {
            formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm");
        }
        formatter.setTimeZone(TimeZone.getTimeZone("UTC"));
        return formatter.format(timeInMillis);
    }

    public static void main(String[] args) throws SQLException {
        int argIndex = 0;
        while (argIndex < args.length && args[argIndex].startsWith("-")) {
            switch (args[argIndex].charAt(1)) {
                case 's':
                    if (args[argIndex].length() > 2) {
                        station = args[argIndex].substring(2);
                    } else {
                        argIndex++;
                        station = args[argIndex];
                    }
                    break;
                default:
                    System.err.printf("%s: unknown option %c\n", args[0], args[argIndex].charAt(1));
                    System.exit(1);
            }
            argIndex++;
        }

        if (args.length - argIndex < 2) {
            System.err.println("usage: insertdb code filename");
            System.exit(1);
        }

        EasMessage message = EasDecode.decode(args[argIndex]);
        if (message == null) {
            System.err.println("insertdb: bad code");
            System.exit(1);
        }

        String filename = new File(args[argIndex + 1]).getName();

        try (Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/nwr")) {
            connection.setAutoCommit(false);

            long id = System.currentTimeMillis(); // Not unique, but serves as an example

            String insertMessage = "INSERT INTO message (id, station, raw, originator, event, issued, received, purge, sender, filename) VALUES (?, UPPER(?), ?, ?, ?, ?, ?, ?, ?, ?)";
            try (PreparedStatement stmt = connection.prepareStatement(insertMessage)) {
                stmt.setLong(1, id);
                stmt.setString(2, station);
                stmt.setString(3, message.getRaw());
                stmt.setString(4, message.getOriginator());
                stmt.setString(5, message.getEvent());
                stmt.setString(6, timestr(message.getIssued(), false));
                stmt.setString(7, timestr(message.getReceived(), false));
                stmt.setString(8, timestr(message.getPurge(), false));
                stmt.setString(9, message.getSender());
                stmt.setString(10, filename);
                stmt.executeUpdate();
            }

            String insertArea = "INSERT INTO message_area (message_id, code, part, state, county) VALUES (?, ?, ?, ?, ?)";
            for (EasMessage.Area area : message.getAreas()) {
                try (PreparedStatement stmt = connection.prepareStatement(insertArea)) {
                    stmt.setLong(1, id);
                    stmt.setString(2, area.getCode());
                    stmt.setInt(3, area.getPart());
                    stmt.setInt(4, area.getState());
                    stmt.setInt(5, area.getCounty());
                    stmt.executeUpdate();
                }
            }

            connection.commit();
        }
    }
}
