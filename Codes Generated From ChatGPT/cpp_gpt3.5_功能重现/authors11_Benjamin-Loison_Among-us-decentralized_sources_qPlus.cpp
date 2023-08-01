#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtMultimedia>
#include <iostream>

// 事件过滤器
bool eventFilter(QObject *object, QEvent *event){
    std::cout << "Object type: " << object->metaObject()->className() << ", event type: " << event->type() << std::endl;
    return QObject::eventFilter(object, event);
}

// 计算两点之间的距离
double distance(QPointF p1, QPointF p2){
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));
}

// 从文件路径或宽度和高度中获取QPixmap对象
QPixmap getPixmap(QString path, int width = 0, int height = 0){
    QPixmap pixmap;
    if (!path.isEmpty()){
        pixmap.load(path);
    }
    else if (width > 0 && height > 0){
        pixmap = QPixmap(width, height);
    }
    return pixmap;
}

// 从文件路径中获取QImage对象
QImage getImage(QString path){
    QImage image;
    if (!path.isEmpty()){
        image.load(path);
    }
    return image;
}

// 将QImage对象的特定颜色替换为给定的颜色
void replaceColor(QImage &image, QColor from, QColor to){
    for (int x = 0; x < image.width(); x++){
        for (int y = 0; y < image.height(); y++){
            if (image.pixelColor(x, y) == from){
                image.setPixelColor(x, y, to);
            }
        }
    }
}

// 将QPixmap对象的特定颜色替换为给定的颜色
void replaceColor(QPixmap &pixmap, QColor from, QColor to){
    QImage image = pixmap.toImage();
    replaceColor(image, from, to);
    pixmap = QPixmap::fromImage(image);
}

// 获取禁用状态下的QPushButton的QPixmap对象
QPixmap getDisabledPixmap(QPushButton *button){
    QPixmap pixmap = button->pixmap();
    QColor color = qApp->palette().color(QPalette::Disabled, QPalette::ButtonText);
    replaceColor(pixmap, QColor(Qt::black), color);
    return pixmap;
}

// 播放给定音频文件
void playAudio(QString path){
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(50);
    player->play();
}

// 创建不同类型的消息框
int MessageBoxCross(QWidget *parent, QString text, QString informativeText = ""){
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle("Error");
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setText(text);
    messageBox.setInformativeText(informativeText);
    messageBox.setStandardButtons(QMessageBox::Ok);
    return messageBox.exec();
}

bool getBool(QWidget *parent, QString text, QString informativeText = ""){
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle("Question");
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setText(text);
    messageBox.setInformativeText(informativeText);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);
    return messageBox.exec() == QMessageBox::Yes;
    int getQUint8(QWidget * parent, QString text, QString informativeText = ""){
        bool ok;
        int value = QInputDialog::getInt(parent, "Input", text, 0, 0, 255, 1, &ok);
        if (!ok){
            return -1;
        }
        return value;
    }

    QString getText(QWidget * parent, QString text, QString value = ""){
        bool ok;
        QString result = QInputDialog::getText(parent, "Input", text, QLineEdit::Normal, value, &ok);
        if (!ok){
            return "";
        }
        return result;
    }

    void showWarningMessage(QWidget * parent, QString text, QString informativeText = ""){
        QMessageBox messageBox(parent);
        messageBox.setWindowTitle("Warning");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText(text);
        messageBox.setInformativeText(informativeText);
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
    }

    void showMessage(QWidget * parent, QString text, QString informativeText = ""){
        QMessageBox messageBox(parent);
        messageBox.setWindowTitle("Information");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText(text);
        messageBox.setInformativeText(informativeText);
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
    }

    // 与QThread::msleep()相似的函数，但同时处理Qt事件循环，以防止GUI挂起。
    void delay(int milliseconds){
        QTime dieTime = QTime::currentTime().addMSecs(milliseconds);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    // 生成随机的十六进制字符串
    QString randomHexString(int length){
        QString result;
        for (int i = 0; i < length; i++){
            result += QString::number(qrand() % 16, 16);
        }
        return result;
    }

    // 计算SHA-512散列
    QByteArray sha512(QByteArray data){
        return QCryptographicHash::hash(data, QCryptographicHash::Sha512);
    }

    // 创建QHBoxLayout，将一个QWidget对象在其中居中
    QHBoxLayout *createCenteredLayout(QWidget * widget){
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(widget, 0, Qt::AlignCenter);
        return layout;
    }

    // 判断字符串是否由数字组成
    bool isNumeric(QString string){
        QRegExp rx("^[0-9]*$");
        return rx.exactMatch(string);
    }

    // 将字符串的第一个字符转换为大写
    QString capitalize(QString string){
        if (!string.isEmpty())
        {
            string[0] = string[0].toUpper();
        }
        return string;
    }

    // 检查给定端口号是否已被使用
    bool isPortInUse(int port){
        QTcpSocket socket;
        socket.connectToHost(QHostAddress::LocalHost, port);
        bool result = socket.waitForConnected(1000);
        if (result)
        {
            socket.disconnectFromHost();
        }
        return result;
    }

    // 在给定的位置绘制中心对齐的文本
    void drawText(QPainter & painter, QPointF position, QString text){
        QFontMetrics fm(painter.font());
        QRectF rect = fm.boundingRect(text);
        QPointF offset(-rect.width() / 2, rect.height() / 2);
        painter.drawText(position + offset, text);
    }

        // 将磅值和像素值相互转换
    int pointsToPixels(int points) {
        return qRound(points * QApplication::primaryScreen()->logicalDotsPerInch() / 72.0);
    }

    int pixelsToPoints(int pixels) {
        return qRound(pixels * 72.0 / QApplication::primaryScreen()->logicalDotsPerInch());
    }

