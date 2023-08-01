// 设置宏定义的常量
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
#define BUTTON_UP_PIN 4
#define BUTTON_DOWN_PIN 5
#define BUTTON_WAKE_PIN 6
#define TARGET_TEMP_MIN 20
#define TARGET_TEMP_MAX 100

#include <U8g2lib.h>

// 在XBMs文件中定义一些预设图标
#include "icons/brewing.xbm"
#include "icons/sleep.xbm"
#include "icons/heating.xbm"
#include "icons/cooling.xbm"
#include "icons/thermometer.xbm"
#include "icons/clock.xbm"
#include "icons/up.xbm"
#include "icons/down.xbm"

// 实现UIController类
class UIController {
public:
	UIController() {
		// 初始化U8g2库
		u8g2 = new U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);
	}

	// 启动UI控制器
	void begin() {
		u8g2->begin();
		// 设置按钮引脚为输入
		pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
		pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
		pinMode(BUTTON_WAKE_PIN, INPUT_PULLUP);
	}

	// 在显示器上绘制各种状态和图标
	void update(bool isSleeping, bool isHeating, bool isCooling, int targetTemp, int currentTemp, int remainingTime) {
		// 清空显示器
		u8g2->clearBuffer();

		// 绘制图标和状态
		if (isSleeping) {
			drawIcon(sleepIcon);
		}
		else {
			if (isHeating) {
				drawIcon(heatingIcon);
			}
			else if (isCooling) {
				drawIcon(coolingIcon);
			}
			else {
				drawIcon(brewingIcon);
			}
			drawTemperature(targetTemp, currentTemp);
			drawTime(remainingTime);
		}

		// 更新显示器缓冲区
		u8g2->sendBuffer();
	}

	// 根据按钮按下调整目标酿造温度
	void handleButtons(int& targetTemp) {
		if (digitalRead(BUTTON_WAKE_PIN) == LOW) {
			// 唤醒屏幕
			u8g2->setPowerSave(false);
		}
		if (digitalRead(BUTTON_UP_PIN) == LOW) {
			// 按下“向上”按钮，目标温度增加
			targetTemp = min(targetTemp + 1, TARGET_TEMP_MAX);
		}
		else if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
			// 按下“向下”按钮，目标温度减少
			targetTemp = max(targetTemp - 1, TARGET_TEMP_MIN);
		}
	}

private:
	U8G2_SSD1306_128X64_NONAME_F_SW_I2C* u8g2;
	// 定义各种图标
	const uint8_t* brewingIcon = brewing_bits;

	const uint8_t* heatingIcon = heating_bits;
	const uint8_t* coolingIcon = cooling_bits;
	const uint8_t* thermometerIcon = thermometer_bits;
	const uint8_t* clockIcon = clock_bits;
	const uint8_t* upIcon = up_bits;
	const uint8_t* downIcon = down_bits;

	// 绘制图标
	void drawIcon(const uint8_t* icon) {
		u8g2->drawXBMP(0, 0, 32, 32, icon);
	}

	// 绘制目标温度和当前温度
	void drawTemperature(int targetTemp, int currentTemp) {
		u8g2->setFont(u8g2_font_helvR14_tf);
		u8g2->drawXBMP(36, 0, 16, 16, thermometerIcon);
		u8g2->setCursor(52, 15);
		u8g2->print(targetTemp);
		u8g2->setCursor(96, 15);
		u8g2->print(currentTemp);
	}

	// 绘制剩余时间
	void drawTime(int remainingTime) {
		u8g2->setFont(u8g2_font_helvR08_tf);
		u8g2->drawXBMP(0, 34, 16, 16, clockIcon);
		u8g2->setCursor(20, 49);
		u8g2->print("Time:");
		u8g2->setCursor(65, 49);
		u8g2->print(remainingTime);
	}
};

// 主程序
void setup() {
	// 初始化UIController
	UIController uiController;
	uiController.begin();

	// 初始化目标温度和当前温度
	int targetTemp = TARGET_TEMP_MIN;
	int currentTemp = 25;

	// 初始化其它变量
	int remainingTime = 60; // 剩余时间，单位：秒
	bool isSleeping = false; // 是否处于休眠模式
	bool isHeating = false; // 是否正在加热
	bool isCooling = false; // 是否正在冷却

	// 进入主循环
	while (true) {
		// 更新UI
		uiController.update(isSleeping, isHeating, isCooling, targetTemp, currentTemp, remainingTime);
		// 处理按钮
		uiController.handleButtons(targetTemp);
		// 模拟温度变化
		if (isHeating) {
			currentTemp = min(currentTemp + 1, targetTemp);
		}
		else if (isCooling) {
			currentTemp = max(currentTemp - 1, TARGET_TEMP_MIN);
		}

		// 模拟剩余时间减少
		remainingTime--;

		// 如果剩余时间为0，则重新开始酿造过程
		if (remainingTime == 0) {
			remainingTime = 60;
			isHeating = true;
			isCooling = false;
		}

		// 如果当前温度等于目标温度，则开始冷却
		if (currentTemp == targetTemp) {
			isHeating = false;
			isCooling = true;
		}

		// 如果处于休眠模式，等待按钮唤醒
		if (isSleeping) {
			while (digitalRead(BUTTON_WAKE_PIN) == HIGH) {
				delay(50);
			}
			isSleeping = false;
			// 恢复显示器
			uiController.update(isSleeping, isHeating, isCooling, targetTemp, currentTemp, remainingTime);
		}
		// 如果目标温度超出范围，重置为最小值
		if (targetTemp < TARGET_TEMP_MIN || targetTemp > TARGET_TEMP_MAX) {
			targetTemp = TARGET_TEMP_MIN;
		}

		// 如果按钮同时按下，则恢复出厂设置
		if (digitalRead(BUTTON_UP_PIN) == LOW && digitalRead(BUTTON_DOWN_PIN) == LOW) {
			targetTemp = TARGET_TEMP_MIN;
			currentTemp = 25;
			remainingTime = 60;
			isSleeping = false;
			isHeating = false;
			isCooling = false;
		}

		// 如果按钮长按，则进入休眠模式
		if (digitalRead(BUTTON_WAKE_PIN) == LOW) {
			int buttonPressedTime = 0;
			while (digitalRead(BUTTON_WAKE_PIN) == LOW) {
				delay(50);
				buttonPressedTime += 50;
			}
			if (buttonPressedTime >= 3000) {
				isSleeping = true;
				// 熄灭显示器
				uiController.u8g2->setPowerSave(true);
			}
		}

		// 等待50毫秒，避免过于频繁的更新UI
		delay(50);
	}
}

void loop() {
	// 主程序只在setup中运行，loop为空函数
}
