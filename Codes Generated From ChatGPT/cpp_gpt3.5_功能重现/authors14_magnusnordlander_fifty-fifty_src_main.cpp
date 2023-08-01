#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Encoder.h>

// 定义使用的引脚
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define SCALE_DATA_PIN A0
#define SCALE_CLK_PIN A1
#define SCALE_POWER_PIN 4
#define GRINDER_POWER_PIN 5
#define BUTTON_PIN 6
#define SCREEN_I2C_ADDRESS 0x3C

// 定义常量
const float SCALE_CALIBRATION_FACTOR = 0.1; // 校准系数
const float GRINDER_SPEED = 500; // 磨豆速度，单位为克/秒

// 创建对象
Encoder encoder(ENCODER_A_PIN, ENCODER_B_PIN);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
HX711 scale(SCALE_DATA_PIN, SCALE_CLK_PIN);
Button button(BUTTON_PIN);

// 全局变量
volatile int encoderCount = 0;
float targetWeight = 0;
float currentWeight = 0;

void setup() {
	// 设置引脚
	pinMode(GRINDER_POWER_PIN, OUTPUT);
	pinMode(SCALE_POWER_PIN, OUTPUT);
	digitalWrite(GRINDER_POWER_PIN, LOW);
	digitalWrite(SCALE_POWER_PIN, HIGH);
	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// 初始化对象
	screen.begin();
	scale.set_scale(SCALE_CALIBRATION_FACTOR);
	scale.tare();

	// 注册编码器中断
	attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), onEncoderChange, CHANGE);
}

void loop() {
	// 处理旋钮旋转事件
	int newEncoderCount = encoder.read();
	if (newEncoderCount != encoderCount) {
		encoderCount = newEncoderCount;
		targetWeight = map(encoderCount, 0, 100, 0, 500);
	}

	// 处理按钮按下和释放事件
	button.update();
	if (button.isPressed()) {
		startGrinding();
	}
	else if (button.isReleased()) {
		stopGrinding();
	}

	// 刷新视图
	screen.clearBuffer();
	drawWeight();
	drawTargetWeight();
	drawGrindingStatus();
	screen.sendBuffer();

	delay(10);
}

// 处理编码器中断
void onEncoderChange() {
	encoderCount++;
}

// 启动磨豆
void startGrinding() {
	digitalWrite(GRINDER_POWER_PIN, HIGH);
}

// 停止磨豆
void stopGrinding() {
	digitalWrite(GRINDER_POWER_PIN, LOW);
}

// 获取当前重量
float getWeight() {
	return scale.get_units();
}

// 绘制当前重量
void drawWeight() {
	currentWeight = getWeight();
	char weightString[10];
	dtostrf(currentWeight, 4, 1, weightString);
	screen.setCursor(0, 12);
	screen.print("Weight:");
	screen.setCursor(60, 12);
	screen.print(weightString);
	screen.setCursor(100, 12);
	screen.print("g");
}

// 绘制目标重量
void drawTargetWeight() {
	char targetWeightString[10];
	dtostrf(targetWeight, 4, 1, targetWeightString);
	screen.setCursor(0, 24);
	screen.print("Target:");
	screen.setCursor(60, 24);
	screen.print(targetWeightString);
	screen.setCursor(100, 24);
	screen.print("g");
}

// 绘制磨豆状态
void drawGrindingStatus() {
	if (currentWeight >= targetWeight) {
		screen.setCursor(100, 0);
		screen.print("Done");
		stopGrinding();
	}
	else {
		screen.setCursor(100, 0);
		screen.print("Grinding");
		startGrinding();
	}
}
