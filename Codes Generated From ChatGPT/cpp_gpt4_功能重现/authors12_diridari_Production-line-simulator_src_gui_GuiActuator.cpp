#include <QWidget>
#include <QLabel>
#include <QResizeEvent>
#include "BaseActuator.h"
#include "BaseProductionStation.h"
#include "Placing.h"

class GuiActuator : public QWidget {
    Q_OBJECT

public:
    GuiActuator(BaseActuator *actuator, BaseProductionStation *station, QWidget *parent = nullptr);

    void update();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QPoint getPos() const;

    BaseActuator *actuator;
    BaseProductionStation *station;
    QLabel *imageLabel;
};

GuiActuator::GuiActuator(BaseActuator *actuator, BaseProductionStation *station, QWidget *parent)
    : QWidget(parent), actuator(actuator), station(station) {
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap::fromImage(actuator->getImage()));
    imageLabel->setScaledContents(true);

    update();
}

void GuiActuator::update() {
    actuator->update();

    // Update the position and size of the widget based on the device and station properties.
    QPoint pos = getPos();
    int width = actuator->getWidth();
    int height = actuator->getHeight();

    setGeometry(pos.x(), pos.y(), width, height);
    imageLabel->setGeometry(0, 0, width, height);
}

QPoint GuiActuator::getPos() const {
    int x, y;
    // Calculate the position of the widget within its parent based on the device's location and the station's output direction.
    Placing::calculatePos(x, y, actuator->getX(), actuator->getY(), station->getOutputDirection());

    return QPoint(x, y);
}

void GuiActuator::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update();
}
