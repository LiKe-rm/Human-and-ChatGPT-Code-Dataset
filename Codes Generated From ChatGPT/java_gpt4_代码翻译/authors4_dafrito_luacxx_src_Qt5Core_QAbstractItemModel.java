import io.qt.core.*;
import io.qt.gui.*;

public class CustomAbstractTableModel extends QAbstractTableModel {
    @Override
    public int columnCount(QModelIndex parent) {
        return 0;
    }

    @Override
    public QVariant data(QModelIndex index, int role) {
        return new QVariant();
    }

    @Override
    public boolean hasChildren(QModelIndex parent) {
        return false;
    }

    public boolean hasIndex(int row, int column, QModelIndex parent) {
        return false;
    }

    public QVariant headerData(int section, Qt.Orientation orientation, int role) {
        return new QVariant();
    }

    @Override
    public QModelIndex index(int row, int column, QModelIndex parent) {
        return new QModelIndex();
    }

    public boolean insertColumn(int column, QModelIndex parent) {
        return false;
    }

    public boolean insertColumns(int column, int count, QModelIndex parent) {
        return false;
    }

    public boolean insertRow(int row, QModelIndex parent) {
        return false;
    }

    public boolean insertRows(int row, int count, QModelIndex parent) {
        return false;
    }

    public QModelIndexList match(QModelIndex start, int role, QVariant value, int hits, Qt.MatchFlags flags) {
        return new QModelIndexList();
    }

    public QModelIndex parent(QModelIndex index) {
        return new QModelIndex();
    }

    public boolean removeColumn(int column, QModelIndex parent) {
        return false;
    }

    public boolean removeColumns(int column, int count, QModelIndex parent) {
        return false;
    }

    public boolean removeRow(int row, QModelIndex parent) {
        return false;
    }

    public boolean removeRows(int row, int count, QModelIndex parent) {
        return false;
    }

    @Override
    public int rowCount(QModelIndex parent) {
        return 0;
    }

    public boolean setData(QModelIndex index, QVariant value, int role) {
        return false;
    }

    public boolean setHeaderData(int section, Qt.Orientation orientation, QVariant value, int role) {
        return false;
    }

    public void sort(int column, Qt.SortOrder order) {
    }
}
