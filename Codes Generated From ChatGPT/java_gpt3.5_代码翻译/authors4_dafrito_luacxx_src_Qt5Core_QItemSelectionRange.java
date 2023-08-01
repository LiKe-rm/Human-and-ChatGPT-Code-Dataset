import java.util.ArrayList;
import java.util.List;

public class QModelIndex {
    private int row;
    private int column;

    public QModelIndex(int row, int column) {
        this.row = row;
        this.column = column;
    }

    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }
}

public class ItemSelectionRange {
    private QModelIndex topLeft;
    private QModelIndex bottomRight;

    public ItemSelectionRange() {
        // 默认构造函数
    }

    public ItemSelectionRange(QModelIndex topLeft, QModelIndex bottomRight) {
        this.topLeft = topLeft;
        this.bottomRight = bottomRight;
    }

    public ItemSelectionRange(QModelIndex index) {
        this.topLeft = index;
        this.bottomRight = index;
    }

    public ItemSelectionRange(ItemSelectionRange other) {
        this.topLeft = other.topLeft;
        this.bottomRight = other.bottomRight;
    }

    public int bottom() {
        return bottomRight.getRow();
    }

    public QModelIndex bottomRight() {
        return bottomRight;
    }

    public boolean contains(QModelIndex index) {
        return index.getRow() >= topLeft.getRow() && index.getRow() <= bottomRight.getRow()
                && index.getColumn() >= topLeft.getColumn() && index.getColumn() <= bottomRight.getColumn();
    }

    public boolean contains(int row, int column, QModelIndex parentIndex) {
        return row >= topLeft.getRow() && row <= bottomRight.getRow()
                && column >= topLeft.getColumn() && column <= bottomRight.getColumn();
    }

    public int height() {
        return bottomRight.getRow() - topLeft.getRow() + 1;
    }

    public List<QModelIndex> indexes() {
        List<QModelIndex> result = new ArrayList<>();
        for (int row = topLeft.getRow(); row <= bottomRight.getRow(); row++) {
            for (int column = topLeft.getColumn(); column <= bottomRight.getColumn(); column++) {
                result.add(new QModelIndex(row, column));
            }
        }
        return result;
    }

    public boolean isEmpty() {
        return topLeft.getRow() > bottomRight.getRow() || topLeft.getColumn() > bottomRight.getColumn();
    }

    public boolean isValid() {
        return topLeft.getRow() <= bottomRight.getRow() && topLeft.getColumn() <= bottomRight.getColumn();
    }

    public int left() {
        return topLeft.getColumn();
    }

    // ...其他方法，如 model() 和 parent()，取决于您的数据模型实现

    public int right() {
        return bottomRight.getColumn();
    }

    public int top() {
        return topLeft.getRow();
    }

    public QModelIndex topLeft() {
        return topLeft;
    }

    public int width() {
        return bottomRight.getColumn() - topLeft.getColumn() + 1;
    }
}
