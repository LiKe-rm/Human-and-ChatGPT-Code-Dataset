#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

class Test {
public:
    void updateView() { qDebug() << "Update view"; }
    void onResume() { qDebug() << "Resume"; }
    void onPause() { qDebug() << "Pause"; }
    void onStop() { qDebug() << "Stop"; }
    void onDestroy() { qDebug() << "Destroy"; }
    void setUp() { qDebug() << "Setup"; }
    void initView() { qDebug() << "Initialize view"; }
    bool onKeyDown(int keyCode) {
        qDebug() << "Key down: " << keyCode;
        return true;
    }
    bool onKeyUp(int keyCode) {
        qDebug() << "Key up: " << keyCode;
        return true;
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Test* currentTest;
    int position;
    static constexpr int FLAG_HOMEKEY_DISPATCHED = 0x80000000;
    static constexpr int FLAG_JRD_RECENTAPPKEY_DISPATCHED = 0x60000000;
public:
    static int temppositon;
    MainWindow(Test* test, QWidget* parent = nullptr)
        : QMainWindow(parent), currentTest(test) {
        this->setWindowState(Qt::WindowFullScreen);
        QTimer::singleShot(0, this, &MainWindow::init);
    }
    void init() {
        currentTest->setUp();
        currentTest->initView();
    }
    void showEvent(QShowEvent* event) override {
        QMainWindow::showEvent(event);
        currentTest->onResume();
    }
    void hideEvent(QHideEvent* event) override {
        QMainWindow::hideEvent(event);
        currentTest->onPause();
    }
    void closeEvent(QCloseEvent* event) override {
        QMainWindow::closeEvent(event);
        currentTest->onStop();
        currentTest->onDestroy();
    }
    void keyPressEvent(QKeyEvent* event) override {
        if (event->key() == Qt::Key_Home) {
            qDebug() << "Home key pressed";
            event->accept();
        } else {
            currentTest->onKeyDown(event->key());
        }
    }
    void keyReleaseEvent(QKeyEvent* event) override {
        currentTest->onKeyUp(event->key());
    }
};

int MainWindow::temppositon = 0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Test test;
    MainWindow window(&test);
    window.show();

    return app.exec();
}
