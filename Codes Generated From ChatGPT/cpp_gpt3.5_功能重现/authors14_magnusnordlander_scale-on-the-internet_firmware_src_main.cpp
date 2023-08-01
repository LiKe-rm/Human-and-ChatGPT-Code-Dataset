#include <Wire.h>         // 引入 Wire 库
#include <Adafruit_GFX.h> // 引入 Adafruit_GFX 库
#include <Adafruit_SSD1306.h> // 引入 Adafruit_SSD1306 库

// 定义 OLED 显示器的引脚
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// 定义数字秤的引脚
#define SCALE_DATA_PIN 3
#define SCALE_CLK_PIN 2

void setup() {
  Serial.begin(9600);

  // 配置 OLED 显示器
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);

  // 初始化数字秤
  pinMode(SCALE_DATA_PIN, INPUT);
  pinMode(SCALE_CLK_PIN, OUTPUT);

  // 设置数字秤的外部状态
  digitalWrite(SCALE_CLK_PIN, HIGH);
}

void loop() {
  // 检测数字秤按钮的状态
  int buttonState = digitalRead(SCALE_DATA_PIN);

  // 如果按钮被按下
  if (buttonState == LOW) {
    Serial.println("Button pressed");

    // 处理按钮按下事件的代码...

  // 如果按钮被松开
  } else {
    Serial.println("Button released");

    // 处理按钮松开事件的代码...
  }

  // 将当前的用户界面绘制到 OLED 显示器上
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Welcome to My Scale!");
  display.display();
}
