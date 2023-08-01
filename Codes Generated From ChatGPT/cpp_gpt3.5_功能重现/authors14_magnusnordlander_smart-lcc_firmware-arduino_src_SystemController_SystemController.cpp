#include <iostream>
#include <vector>
#include <string>

// 咖啡机组件头文件
#include "CoffeePot.h"
#include "WaterPump.h"
#include "Boiler.h"
#include "ControlPanel.h"
#include "TemperatureSensor.h"

using namespace std;

// SystemController 类
class SystemController {
public:
	// 构造函数
	SystemController() {
		// 初始化各个组件
		coffeePot = new CoffeePot();
		waterPump = new WaterPump();
		serviceBoiler = new Boiler();
		controlPanel = new ControlPanel();
		temperatureSensor = new TemperatureSensor();
	}

	// 析构函数
	~SystemController() {
		// 释放各个组件的内存
		delete coffeePot;
		delete waterPump;
		delete serviceBoiler;
		delete controlPanel;
		delete temperatureSensor;
	}

	// 主循环函数
	void loop() {
		while (true) {
			// 处理从控制板发送来的数据
			processControlPanelData();

			// 处理从温度传感器发送来的数据
			processTemperatureSensorData();

			// 更新咖啡机各个组件的状态
			updateComponentStatus();

			// 控制咖啡锅炉和服务锅炉的温度
			controlBoilerTemperature();

			// 控制泵和锅炉的开关
			controlPumpAndBoilerSwitch();

			// 处理外部命令
			processExternalCommand();

			// 暂停一段时间后再继续执行
			delay(1000);
		}
	}

	// 处理从控制板发送来的数据
	void processControlPanelData() {
		vector<string> data = controlPanel->receiveData();
		for (string command : data) {
			if (command == "start") {
				coffeePot->startBrewing();
			}
			else if (command == "stop") {
				coffeePot->stopBrewing();
			}
			else if (command == "set_temperature") {
				int temperature = controlPanel->getTemperatureSetting();
				serviceBoiler->setTemperature(temperature);
			}
			else if (command == "set_eco_mode") {
				bool ecoMode = controlPanel->getEcoModeSetting();
				coffeePot->setEcoMode(ecoMode);
			}
		}
	}

	// 处理从温度传感器发送来的数据
	void processTemperatureSensorData() {
		int temperature = temperatureSensor->readTemperature();
		coffeePot->setTemperature(temperature);
		serviceBoiler->setTemperature(temperature);
	}

	// 更新咖啡机各个组件的状态
	void updateComponentStatus() {
		coffeePot->updateStatus();
		waterPump->updateStatus();
		serviceBoiler->updateStatus();
	}

	// 控制咖啡锅炉和服务锅炉的温度
	void controlBoilerTemperature() {
		int coffeePotTemperature = coffeePot->getTemperature();
		int serviceBoilerTemperature = serviceBoiler->getTemperature();

		if (coffeePotTemperature < coffeePotTemperatureThreshold) {
			coffeePot->turnOnHeatingElement();
		}
		else {
			coffeePot->turnOffHeatingElement();
		}
		if (serviceBoilerTemperature < serviceBoilerTemperatureThreshold) {
			serviceBoiler->turnOnHeatingElement();
		}
		else {
			serviceBoiler->turnOffHeatingElement();
		}
	}

	// 控制泵和锅炉的开关
	void controlPumpAndBoilerSwitch() {
		if (coffeePot->isBrewing()) {
			waterPump->turnOn();
			serviceBoiler->turnOn();
		}
		else {
			waterPump->turnOff();
			serviceBoiler->turnOff();
		}
	}

	// 处理外部命令
	void processExternalCommand() {
		// TODO: 实现处理外部命令的代码
	}
private:
	// 咖啡机组件
	CoffeePot* coffeePot;
	WaterPump* waterPump;
	Boiler* serviceBoiler;
	ControlPanel* controlPanel;
	TemperatureSensor* temperatureSensor;

	// 常量
	const int coffeePotTemperatureThreshold = 90;
	const int serviceBoilerTemperatureThreshold = 95;

	// 延时函数
	void delay(int milliseconds) {
		// TODO: 实现延时函数的代码
	}
};

int main() {
	// 创建 SystemController 对象并启动主循环
	SystemController systemController;
	systemController.loop();
	return 0;
}
