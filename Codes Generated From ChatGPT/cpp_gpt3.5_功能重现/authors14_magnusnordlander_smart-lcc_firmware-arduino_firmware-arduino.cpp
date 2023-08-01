#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

// 自定义库
#include "AutomationController.h"
#include "NetworkController.h"
#include "SafePacketSender.h"
#include "UIController.h"

// 常量定义
#define OLED_RESET 4
#define OLED_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define WIFI_TIMEOUT 30000
#define MQTT_PORT 1883
#define MQTT_KEEPALIVE 60
#define MAX_PACKET_SIZE 256

// 变量定义
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
WiFiUDP udpClient;
SafePacketSender safePacketSender(mqttClient, udpClient);
AutomationController automationController(mqttClient);
NetworkController networkController(wifiClient, mqttClient, safePacketSender);
UIController uiController(display);

// 队列定义
QueueHandle_t systemStatusQueue;

// 函数声明
void loop1();

void setup() {
	// 初始化 OLED 显示器
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
	display.clearDisplay();
	display.display();

	// 初始化文件系统
	if (!SD.begin()) {
		Serial.println("Failed to initialize SD card");
		while (1) {}
	}

	// 初始化按键
	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// 初始化 GPIO
	pinMode(LED_PIN, OUTPUT);

	// 根据按键状态设置网络连接模式
	if (digitalRead(BUTTON_PIN) == LOW) {
		networkController.setConnectionMode(NetworkController::WIFI_AP_MODE);
	}
	else {
		networkController.setConnectionMode(NetworkController::WIFI_STA_MODE);
	}

	// 启动自动化控制器和系统控制器
	automationController.begin();
	xTaskCreatePinnedToCore(loop1, "System Controller", 8192, NULL, 1, NULL, 1);

	// 启用看门狗定时器
	esp_task_wdt_init(WDT_TIMEOUT, true);
	esp_task_wdt_add(NULL);
}

void loop() {
	// 判断网络连接模式
	if (networkController.getConnectionMode() != NetworkController::NORMAL_MODE) {
		// 发送安全数据包
		safePacketSender.loop();
	}
	else {
		// 执行自动化控制器循环
		automationController.loop();
	}

	// 获取系统状态信息并更新设备状态
	SystemStatus systemStatus;
	if (xQueueReceive(systemStatusQueue, &systemStatus, 0) == pdTRUE) {
		// 更新设备状态
		digitalWrite(LED_PIN, systemStatus.isLedOn ? HIGH : LOW);
	}

	// 执行网络循环
	networkController.loop();

	// 执行用户界面循环
	uiController.loop();

	//
}

void loop1() {
	while (1) {
		// 执行系统控制器循环
		SystemStatus systemStatus;
		systemStatus.isLedOn = digitalRead(LED_PIN) == HIGH;
		xQueueSend(systemStatusQueue, &systemStatus, 0);
		// 刷新看门狗定时器
		esp_task_wdt_reset();
	}
}