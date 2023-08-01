#include <vector>
#include <QSize>
#include <QPoint>
#include "BaseProductionStation.h"
#include "BaseWorkpiece.h"

class Placing {
public:
    static bool canPlaceItem(BaseProductionStation *stationToPlace, BaseWorkpiece *wp, QPoint posToPlace);
    static bool canAcceptNewItem(BaseProductionStation *station, QSize sizeOfBox);
    static QPoint calculateGuiPosition(BaseWorkpiece *wp, BaseProductionStation *station);
    static QPoint calculateGuiPosition(QPoint pos, BaseProductionStation *station);
    static QPoint calculateProcessPosition(QPoint pos, BaseProductionStation *station);

private:
    Placing() {} // This class should not be instantiated.
};

bool Placing::canPlaceItem(BaseProductionStation *stationToPlace, BaseWorkpiece *wp, QPoint posToPlace) {
    // Step 1: Check if the position to place the item is valid.
    QSize stationSize = stationToPlace->getSize();
    QSize wpSize = wp->getSize();
    if (posToPlace.x() < 0 || posToPlace.y() < 0 ||
        posToPlace.x() + wpSize.width() > stationSize.width() ||
        posToPlace.y() + wpSize.height() > stationSize.height()) {
        return false;
    }

    // Step 2: Check if the item to place collides with any existing items in the station.
    for (BaseWorkpiece *existingWp : stationToPlace->getWorkpieces()) {
        QRect existingWpRect(existingWp->getPosition(), existingWp->getSize());
        QRect wpRect(posToPlace, wpSize);
        if (existingWpRect.intersects(wpRect)) {
            return false;
        }
    }

    return true;
}

bool Placing::canAcceptNewItem(BaseProductionStation *station, QSize sizeOfBox) {
    // Step 1: Check if there are too many items in the station.
    if (station->getWorkpieces().size() >= station->getMaxItemCount()) {
        return false;
    }

    // Step 2: Check if there is a big item on the left side of the station.
    for (BaseWorkpiece *existingWp : station->getWorkpieces()) {
        QRect existingWpRect(existingWp->getPosition(), existingWp->getSize());
        if (existingWpRect.left() < sizeOfBox.width()) {
            return false;
        }
    }

    return true;
}

QPoint Placing::calculateGuiPosition(BaseWorkpiece *wp, BaseProductionStation *station) {
    // Calculate the position of the workpiece in the GUI.
    QPoint processPosition = wp->getPosition();
    return calculateGuiPosition(processPosition, station);
}

QPoint Placing::calculateGuiPosition(QPoint pos, BaseProductionStation *station) {
    // Calculate the position in the GUI for the given position.
    int guiX = pos.x() * station->getGuiScaleFactor();
    int guiY = pos.y() * station->getGuiScaleFactor();
    return QPoint(guiX, guiY);
}

QPoint Placing::calculateProcessPosition(QPoint pos, BaseProductionStation *station) {
    // Calculate the position in the process for the given GUI position.
    int processX = pos.x() / station->getGuiScaleFactor();
    int processY = pos.y() / station->getGuiScaleFactor();
    return QPoint(processX, processY);
}
