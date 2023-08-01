#include <QApplication>
#include <QScintilla>
#include <QListWidget>
#include <QMouseEvent>

class ListBoxQt: public QListWidget {
    Q_OBJECT

public:
    explicit ListBoxQt(QWidget *parent = nullptr);

    void create(QWidget *parent);
    void clear();
    void setValue(const QString &text, int index);
    void setVisibleRows(int numRows);
    void registerImage(int type, const QPixmap &image);
    void setDoubleClickCallback(void (*callback)(const QString &));

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void (*doubleClickCallback)(const QString &) = nullptr;
};

ListBoxQt::ListBoxQt(QWidget *parent) : QListWidget(parent) {
}

void ListBoxQt::create(QWidget *parent) {
    setParent(parent);
    show();
}

void ListBoxQt::clear() {
    QListWidget::clear();
}

void ListBoxQt::setValue(const QString &text, int index) {
    if (index < 0 || index >= count()) {
        return;
    }
    item(index)->setText(text);
}

void ListBoxQt::setVisibleRows(int numRows) {
    setFixedHeight(fontMetrics().height() * numRows + 2 * frameWidth());
}

void ListBoxQt::registerImage(int type, const QPixmap &image) {
    QIcon icon(image);
    QListWidgetItem *listItem = new QListWidgetItem(icon, "", this);
    listItem->setData(Qt::UserRole, type);
}

void ListBoxQt::setDoubleClickCallback(void (*callback)(const QString &)) {
    doubleClickCallback = callback;
}

void ListBoxQt::mouseDoubleClickEvent(QMouseEvent *event) {
    if (!doubleClickCallback) {
        return;
    }

    QModelIndex index = indexAt(event->pos());
    if (!index.isValid()) {
        return;
    }

    QString itemText = item(index.row())->text();
    doubleClickCallback(itemText);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ListBoxQt listBox;
    listBox.create(nullptr);

    listBox.addItem("Item 1");
    listBox.addItem("Item 2");
    listBox.addItem("Item 3");
    listBox.setVisibleRows(5);

    listBox.setDoubleClickCallback([](const QString &itemText) {
        qDebug() << "Double clicked on:" << itemText;
    });

    return app.exec();
}
