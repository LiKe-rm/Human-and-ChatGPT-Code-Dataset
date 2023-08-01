#include <QLabel>
#include <QRandomGenerator>
#include <QPainter>
#include <QHBoxLayout>
#include "fixWiring.h"
#include "../main.h"

constexpr int COLORS_NUMBER = 4;
constexpr int COLOR_UNDEFINED = -1;
constexpr int COLOR_FIXING = -2;
constexpr int FIX_WIRING_TOP_Y = 90;
constexpr int FIX_WIRING_DELTA_Y = 48;
constexpr int FIX_WIRING_LEFT_X = 96;
constexpr int FIX_WIRING_RIGHT_X = 330;
constexpr int FIX_WIRING_WIDTH = 24;
constexpr int FIX_WIRING_HEIGHT = 6;

enum WiringColor { Yellow, Blue, Red, Magenta };

WiringColor lefts[COLORS_NUMBER];
WiringColor rights[COLORS_NUMBER] = { Red, Blue, Yellow, Magenta };
int links[COLORS_NUMBER] = { COLOR_UNDEFINED, COLOR_UNDEFINED, COLOR_UNDEFINED, COLOR_UNDEFINED };

QPixmap* fixWiringBackgroundPixmap = nullptr;
QPixmap* currFixWiringPixmap = nullptr;
QLabel* currFixWiringLabel = nullptr;

WiringColor getColor(int colorIndex) {
    switch (colorIndex) {
    case 0:
        return Yellow;
    case 1:
        return Blue;
    case 2:
        return Red;
    default:
        return Magenta;
    }
}

int getIndex(WiringColor color) {
    switch (color) {
    case Yellow:
        return 0;
    case Blue:
        return 1;
    case Red:
        return 2;
    default:
        return 3;
    }
}

void randomWires(WiringColor* nodes) {
    QList<int> colors;
    for (int i = 0; i < COLORS_NUMBER; i++) {
        colors.append(i);
    }
    std::random_shuffle(colors.begin(), colors.end());
    for (int i = 0; i < COLORS_NUMBER; i++) {
        nodes[i] = getColor(colors[i]);
    }
}

QColor getQtColor(WiringColor color) {
    switch (color) {
    case Yellow:
        return Qt::yellow;
    case Blue:
        return Qt::blue;
    case Red:
        return Qt::red;
    default:
        return Qt::magenta;
    }
}

int getYForWiring(int nodesIndex) {
    return FIX_WIRING_TOP_Y + FIX_WIRING_DELTA_Y * nodesIndex;
}

void fillFixWire(QPainter* painter, int start, int y, int x) {
    int yLeft = getYForWiring(start);
    QPainterPath path;
    path.moveTo(FIX_WIRING_LEFT_X + FIX_WIRING_WIDTH, yLeft);
    path.lineTo(FIX_WIRING_LEFT_X + FIX_WIRING_WIDTH, yLeft + FIX_WIRING_HEIGHT);
    path.lineTo(x, y + FIX_WIRING_HEIGHT);
    path.lineTo(x, y);

    painter->setPen(Qt::NoPen);
    painter->fillPath(path, QBrush(getQtColor(lefts[start])));
}

void fillWire(QPainter* painter, int start) {
    int link = links[start];
    if (link == COLOR_UNDEFINED || link == COLOR_FIXING) {
        return;
    }
    int yRight = getYForWiring(link);
    fillFixWire(painter, start, yRight, FIX_WIRING_RIGHT_X);
}

QPixmap* getFixWiringPixmap() {
    if (!fixWiringBackgroundPixmap) {
        fixWiringBackgroundPixmap = getQPixmap("fixWiring.png");
    }
    QPixmap* pixmap = new QPixmap(*fixWiringBackgroundPixmap);
    QPainter painter(pixmap);
    for (int i = 0; i < COLORS_NUMBER; i++) {
        int y = getYForWiring(i);
        painter.fillRect(FIX_WIRING_LEFT_X, y, FIX_WIRING_WIDTH, FIX_WIRING_HEIGHT, getQtColor(lefts[i]));
        painter.fillRect(FIX_WIRING_RIGHT_X, y, FIX_WIRING_WIDTH, FIX_WIRING_HEIGHT, getQtColor(rights[i]));
    }
    return pixmap;
}

QLabel* getFixWiring() {
    playSound("fix_wiring_task_open");
    randomWires(lefts);
    resetFixWiring();
    QPixmap* pixmap = getFixWiringPixmap();
    QLabel* label = new QLabel;
    label->setPixmap(*pixmap);
    if (currFixWiringPixmap) {
        delete currFixWiringPixmap;
    }
    currFixWiringPixmap = pixmap;
    if (currFixWiringLabel) {
        delete currFixWiringLabel;
    }
    currFixWiringLabel = label;
    return label;
}

void onMouseEventFixWiring(QMouseEvent* mouseEvent) {
    int range = FIX_WIRING_DELTA_Y / 2;
    QPixmap* pixmap = getFixWiringPixmap();
    QPainter painter(pixmap);
    QPoint position = mouseEvent->pos();
    int mouseY = position.y() - FIX_WIRING_TOP_Y;
    if (mouseY < 0 || mouseY > FIX_WIRING_DELTA_Y * COLORS_NUMBER) {
        return;
    }
    int mouseX = position.x();
    bool isFixing = false;
    int fixingIndex = 0;
    for (int i = 0; i < COLORS_NUMBER; i++) {
        int link = links[i];
        if (link == COLOR_FIXING) {
            isFixing = true;
            fixingIndex = i;
            break;
        }
    }
    if (isFixing) {
        for (int i = 0; i < COLORS_NUMBER; i++) {
            int middleX = FIX_WIRING_RIGHT_X + FIX_WIRING_WIDTH / 2;
            int middleY = getYForWiring(i);
            if (abs(middleY - mouseY) <= range && abs(middleX - mouseX) <= range) {
                links[fixingIndex] = i;
                playSound(QString("fix_wiring_connect_wire_%1").arg(QRandomGenerator::global()->bounded(3)));
                break;
            }
        }
    }
    for (int i = 0; i < COLORS_NUMBER; i++) {
        int middleX = FIX_WIRING_LEFT_X + FIX_WIRING_WIDTH / 2;
        int middleY = getYForWiring(i);
        int d = sqrt(pow(middleX - mouseX, 2) + pow(middleY - mouseY, 2));
        bool isNearNode = d <= range;
        int link = links[i];
        if (link == COLOR_UNDEFINED) {
            if (isNearNode) {
                links[i] = COLOR_FIXING;
                i--;
            } else {
                fillWire(&painter, i);
            }
        } else if (link == COLOR_FIXING) {
            fillFixWire(&painter, i, mouseY, mouseX);
        } else if (!isFixing && isNearNode) {
            links[i] = COLOR_FIXING;
            i--;
        } else {
            fillWire(&painter, i);
        }
    }
    painter.end();
    if (currFixWiringLabel) {
        currFixWiringLabel->setPixmap(*pixmap);
    }
    delete pixmap;
    bool everythingMatch = true;
    for (int i = 0; i < COLORS_NUMBER; i++) {
        int link = links[i];
        if (link >= COLORS_NUMBER) {
            everythingMatch = false;
            break;
        }
        if (lefts[i] != rights[link]) {
            everythingMatch = false;
            break;
        }
    }
    if (everythingMatch) {
        playSound("task_completed");
        inGameUI->finishTask();
        inGameUI->closeTask();
        inGameUI->checkEndOfTheGame();
    }
}

void onCloseFixWiring() {
    playSound("fix_wiring_task_close");
    if (currFixWiringLabel) {
        delete currFixWiringLabel;
        currFixWiringLabel = nullptr;
    }
    if (currFixWiringPixmap) {
        delete currFixWiringPixmap;
        currFixWiringPixmap = nullptr;
    }
}

