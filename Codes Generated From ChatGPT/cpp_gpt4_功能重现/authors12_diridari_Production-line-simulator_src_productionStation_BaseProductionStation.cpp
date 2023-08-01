#include <vector>
#include <string>
#include "BaseActuator.h"
#include "BaseSensor.h"
#include "BaseWorkpiece.h"

class BaseProductionStation {
public:
    void addActuator(BaseActuator *actuator);
    void addSensor(BaseSensor *sensor);
    std::string getStationName() const;
    void runSimulationStep();
    void insertWorkpiece(BaseWorkpiece *wp);
    std::vector<BaseWorkpiece *> getWorkpieces() const;
    std::vector<BaseActuator *> getActuators() const;
    std::vector<BaseSensor *> getSensors() const;
    BaseProductionStation *getNextConnectedStation() const;
    int getInputDirection() const;
    int getOutputDirection() const;
    void setInputOutputDirection(int inputDirection, int outputDirection);
    void setInputDirection(int inputDirection);
    void setOutputDirection(int outputDirection);
    void checkSensors();
    bool canAcceptNewItem(BaseWorkpiece *wp) const;
    void removeWorkpiece(BaseWorkpiece *wp);
    bool hasWorkpiece(BaseWorkpiece *wp) const;
    std::string getDetailedInfo() const;

private:
    std::string stationName;
    std::vector<BaseActuator *> actuators;
    std::vector<BaseSensor *> sensors;
    std::vector<BaseWorkpiece *> workpieces;
    BaseProductionStation *nextConnectedStation;
    int inputDirection;
    int outputDirection;
};

void BaseProductionStation::addActuator(BaseActuator *actuator) {
    actuators.push_back(actuator);
}

void BaseProductionStation::addSensor(BaseSensor *sensor) {
    sensors.push_back(sensor);
}

std::string BaseProductionStation::getStationName() const {
    return stationName;
}

void BaseProductionStation::runSimulationStep() {
    // Implement your simulation step logic here
}

void BaseProductionStation::insertWorkpiece(BaseWorkpiece *wp) {
    workpieces.push_back(wp);
}

std::vector<BaseWorkpiece *> BaseProductionStation::getWorkpieces() const {
    return workpieces;
}

std::vector<BaseActuator *> BaseProductionStation::getActuators() const {
    return actuators;
}

std::vector<BaseSensor *> BaseProductionStation::getSensors() const {
    return sensors;
}

BaseProductionStation *BaseProductionStation::getNextConnectedStation() const {
    return nextConnectedStation;
}

int BaseProductionStation::getInputDirection() const {
    return inputDirection;
}

int BaseProductionStation::getOutputDirection() const {
    return outputDirection;
}

void BaseProductionStation::setInputOutputDirection(int inputDirection, int outputDirection) {
    setInputDirection(inputDirection);
    setOutputDirection(outputDirection);
}

void BaseProductionStation::setInputDirection(int inputDirection) {
    this->inputDirection = inputDirection;
}

void BaseProductionStation::setOutputDirection(int outputDirection) {
    this->outputDirection = outputDirection;
}

void BaseProductionStation::checkSensors() {
    // Implement your sensor checking logic here
}

bool BaseProductionStation::canAcceptNewItem(BaseWorkpiece *wp) const {
    // Implement your logic for checking if the station can accept a new item here
}

void BaseProductionStation::removeWorkpiece(BaseWorkpiece *wp) {
    workpieces.erase(std::remove(workpieces.begin(), workpieces.end(), wp), workpieces.end());
}
