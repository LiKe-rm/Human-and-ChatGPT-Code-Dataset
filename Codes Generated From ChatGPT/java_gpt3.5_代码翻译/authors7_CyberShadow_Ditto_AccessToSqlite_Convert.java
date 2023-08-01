import java.sql.*;
import java.util.HashMap;
import java.util.Map;

public class Convert {

    private final AccessToSqlite accessToSqlite;
    private final Map<Long, Long> parentMap;
    private final Progress progress;

    public Convert() {
        accessToSqlite = new AccessToSqlite();
        parentMap = new HashMap<>();
        progress = new Progress();
    }

    public boolean convertNonGroups() {
        try {
            ResultSet resultSet = accessToSqlite.getNonGroups();

            if (resultSet != null) {
                while (resultSet.next()) {
                    convertEntry(resultSet);
                    progress.step();
                }
            }
        } catch (SQLException e) {
            log("SQLException - " + e.getMessage());
            return false;
        }
        return true;
    }

    public boolean convertGroups(long parentId) {
        try {
            ResultSet resultSet = accessToSqlite.getGroups(parentId);

            while (resultSet.next()) {
                convertEntry(resultSet);
                convertGroups(resultSet.getLong("lID"));
                progress.step();
            }
        } catch (SQLException e) {
            log("SQLException - " + e.getMessage());
            return false;
        }
        return true;
    }

    public boolean convertEntry(ResultSet resultSet) {
        boolean result = false;

        try {
            Clip clip = new Clip();

            clip.setDesc(resultSet.getString("strText"));
            clip.setTime(resultSet.getLong("lDate"));
            clip.setShortCut(resultSet.getLong("lShortCut"));
            clip.setDontAutoDelete(resultSet.getLong("lDontAutoDelete"));
            clip.setIsGroup(resultSet.getBoolean("bIsGroup"));

            long parent;
            if (parentMap.containsKey(resultSet.getLong("lParentID"))) {
                parent = parentMap.get(resultSet.getLong("lParentID"));
                clip.setParent(parent);
            }

            if (clip.isGroup() || accessToSqlite.loadFormats(resultSet.getLong("lID"), clip.getFormats())) {
                clip.addToDB(false);

                if (clip.isGroup()) {
                    parentMap.put(resultSet.getLong("lID"), clip.getId());
                }

                result = true;
            } else {
                log("Error loading formats id = " + resultSet.getLong("lID"));
            }
        } catch (SQLException e) {
            log("SQLException - " + e.getMessage());
            result = false;
        }

        return result;
    }

    public boolean convertTypes() {
        try {
            ResultSet resultSet = accessToSqlite.getTypes();

            boolean foundCF_UNICODETEXT = false;
            boolean addedOne = false;

            while (resultSet.next()) {
                accessToSqlite.insertType(resultSet.getString("TypeText"));

                addedOne = true;

                if ("CF_UNICODETEXT".equals(resultSet.getString("TypeText"))) {
                    foundCF_UNICODETEXT = true;
                }
            }

            if (addedOne && !foundCF_UNICODETEXT) {
                accessToSqlite.insertType("CF_UNICODETEXT");
            }
        } catch (SQLException e) {
            log("SQLException - " + e.getMessage());
            return false;
        }

        return true;
    }

    public void setupProgressWnd() {
        ResultSet resultSet = accessToSqlite.getMainTable();
        int recordCount = 0;

        try {
            if (resultSet != null) {
                resultSet.last();
                recordCount = resultSet.getRow();
            }
        } catch (SQLException e) {
            log("SQLException - " + e.getMessage());
        }

        progress.create(recordCount);
    }

    private void log(String message) {
        // Implement logging logic
    }
}
