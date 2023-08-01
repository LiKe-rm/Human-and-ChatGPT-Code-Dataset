#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>

using namespace std;

const int SECOND = 1000;

class Sensor {
public:
    string name;
    int id;
};

class SensorEvent {
public:
    Sensor sensor;
    vector<float> values;
};

class SensorManager {
public:
    SensorManager() {}

    Sensor getDefaultSensor(int sensorType) {
        // Here we just simulate the behavior of this function
        Sensor sensor;
        sensor.id = sensorType;
        sensor.name = "ProximitySensor";
        return sensor;
    }

    bool registerListener(Sensor sensor, int delay) {
        // Here we just simulate the behavior of this function
        cout << "Register listener for " << sensor.name << endl;
        return true;
    }

    void unregisterListener(Sensor sensor) {
        // Here we just simulate the behavior of this function
        cout << "Unregister listener for " << sensor.name << endl;
    }
};

class SensorEventListener {
public:
    virtual void onAccuracyChanged(Sensor sensor, int accuracy) = 0;
    virtual void onSensorChanged(SensorEvent event) = 0;
};

class Test : public SensorEventListener {
public:
    string name;
    string id;
    bool updateFlag;
    SensorManager sensorManager;
    Sensor proximitySensor;
    int far2neer = 0;
    int near2far = -1;

    Test(string id, string name) : id(id), name(name) {}

    Test(string id, string name, bool updateFlag) : id(id), name(name), updateFlag(updateFlag) {}

    void setUp() {
        cout << "Start test" << endl;
        proximitySensor = sensorManager.getDefaultSensor(1);
        if (!sensorManager.registerListener(proximitySensor, 1)) {
            cout << "Register listener for ProximitySensor " << proximitySensor.name << " failed" << endl;
        }
        startTestCountDownTimer(10);
    }

    void startTestCountDownTimer(int duration) {
        this_thread::sleep_for(chrono::seconds(duration));
        onTestFinish();
    }

    virtual void onTestFinish() {
        cout << "Test finished" << endl;
    }

    void destroy() {
        sensorManager.unregisterListener(proximitySensor);
        far2neer = 0;
        near2far = -1;
    }

    void onAccuracyChanged(Sensor sensor, int accuracy) override {}

    void onSensorChanged(SensorEvent event) override {
        float distance = event.values[0];
        if (distance == 0) {
            far2neer++;
        }
        if (distance == 1) {
            near2far++;
        }
        cout << "ProximitySensor detected" << endl;
        cout << "near->far:" << near2far << endl;
        cout << "far->near:" << far2neer << endl;
        if ((near2far != 0) && (far2neer != 0)) {
            cout << "Test pass" << endl;
        }
    }

    string readPsRawData(string path) {
        ifstream inFile(path);
        stringstream buffer;
        buffer << inFile.rdbuf();
        return buffer.str();
    }
};

int main() {
    Test test("1", "AlsPsTest");
    test.setUp();
    return 0;
}
