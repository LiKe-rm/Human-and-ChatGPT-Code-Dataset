import java.util.Map;

public class QPoint {
    private int x;
    private int y;

    public QPoint() {
        this.x = 0;
        this.y = 0;
    }

    public QPoint(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public boolean isNull() {
        return x == 0 && y == 0;
    }

    public int manhattanLength() {
        return Math.abs(x) + Math.abs(y);
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public static QPoint fromLuaTable(Map<String, Integer> table) {
        if (table == null || table.isEmpty()) {
            throw new IllegalArgumentException("Point must be a non-empty table");
        }

        int x = table.getOrDefault("x", 0);
        int y = table.getOrDefault("y", 0);

        return new QPoint(x, y);
    }

    public Map<String, Integer> toLuaTable() {
        return Map.of("x", x, "y", y);
    }
}
