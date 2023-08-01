#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>

class Canvas: public QLabel {
public:
    Canvas(QWidget *parent = nullptr) : QLabel(parent) {
        setMouseTracking(true);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            startPoint = event->pos();
            drawing = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (drawing) {
            endPoint = event->pos();
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            drawing = false;
            QRect rect(startPoint, endPoint);
            rectangles.append(rect);
            update();
        }
    }

    void paintEvent(QPaintEvent *event) override {
        QLabel::paintEvent(event);
        QPainter painter(this);
        painter.setPen(Qt::red);
        for (const QRect &rect : rectangles) {
            painter.drawRect(rect);
        }
        if (drawing) {
            painter.drawRect(QRect(startPoint, endPoint));
        }
    }

    void removeLastRectangle() {
        if (!rectangles.isEmpty()) {
            rectangles.removeLast();
            update();
        }
    }

private:
    QPoint startPoint;
    QPoint endPoint;
    bool drawing = false;
    QVector<QRect> rectangles;
};

class ImageAnnotator: public QWidget {
public:
    ImageAnnotator(QWidget *parent = nullptr) : QWidget(parent) {
        QHBoxLayout *mainLayout = new QHBoxLayout(this);

        QVBoxLayout *leftLayout = new QVBoxLayout();
        mainLayout->addLayout(leftLayout);

        QPushButton *loadImageButton = new QPushButton(tr("Load Image"));
        leftLayout->addWidget(loadImageButton);
        connect(loadImageButton, &QPushButton::clicked, this, &ImageAnnotator::loadImage);

        canvas = new Canvas();
        leftLayout->addWidget(canvas);

        QVBoxLayout *rightLayout = new QVBoxLayout();
        mainLayout->addLayout(rightLayout);

        QLabel *labelListLabel = new QLabel(tr("Labels"));
        rightLayout->addWidget(labelListLabel);

        labelListView = new QListView();
        rightLayout->addWidget(labelListView);

        QPushButton *removeRectButton = new QPushButton(tr("Remove Last Rectangle"));
        rightLayout->addWidget(removeRectButton);
        connect(removeRectButton, &QPushButton::clicked, canvas, &Canvas::removeLastRectangle);
    }

private slots:
    void loadImage() {
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.jpg *.bmp)"));
        if (!imagePath.isEmpty()) {
            QImage image(imagePath);
            canvas->setPixmap(QPixmap::fromImage(image));
            canvas->setFixedSize(image.size());
        }
    }

private:
    Canvas *canvas;
    QListView *labelListView;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ImageAnnotator annotator;
    annotator.show();

    return app.exec();
}
