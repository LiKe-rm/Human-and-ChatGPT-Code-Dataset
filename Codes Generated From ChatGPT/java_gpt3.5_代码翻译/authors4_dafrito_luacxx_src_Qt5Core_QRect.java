import java.awt.Point;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.util.Map;

public class QRect extends Rectangle {

    public QRect() {
        super();
    }

    public QRect(int x, int y, int width, int height) {
        super(x, y, width, height);
    }

    public boolean isNull() {
        return this.isEmpty();
    }

    public boolean isValid() {
        return this.width >= 0 && this.height >= 0;
    }

    public Point bottomLeft() {
        return new Point(this.x, this.y + this.height);
    }

    public Point bottomRight() {
        return new Point(this.x + this.width, this.y + this.height);
    }

    public Point topRight() {
        return new Point(this.x + this.width, this.y);
    }

    // ... 更多方法的实现

    public static QRect fromLuaTable(Map<String, Integer> table) {
        if (table == null || table.isEmpty()) {
            throw new IllegalArgumentException("Rect must be a non-empty table");
        }

        int x = table.getOrDefault("x", 0);
        int y = table.getOrDefault("y", 0);
        int width = table.getOrDefault("width", 0);
        int height = table.getOrDefault("height", 0);

        return new QRect(x, y, width, height);
    }

    public Map<String, Integer> toLuaTable() {
        return Map.of("x", x, "y", y, "width", width, "height", height);
    }
}
