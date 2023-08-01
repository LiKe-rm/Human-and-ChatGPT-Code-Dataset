#include <SPI.h>

#define A7105_REG_MODE 0x00
#define A7105_REG_MODE_CONTROL1 0x01
#define A7105_REG_MODE_CONTROL2 0x02

#define A7105_DEFAULT_MODE 0x14
#define A7105_DEFAULT_MODE_CONTROL1 0x12
#define A7105_DEFAULT_MODE_CONTROL2 0x02

enum A7105Mode {
  A7105_MODE_IDLE,
  A7105_MODE_STANDBY,
  A7105_MODE_FS,
  A7105_MODE_TX,
  A7105_MODE_RX,
  A7105_MODE_UNKNOWN
};

enum A7105PowerLevel {
  A7105_POWER_LEVEL_0,
  A7105_POWER_LEVEL_1,
  A7105_POWER_LEVEL_2,
  A7105_POWER_LEVEL_3,
  A7105_POWER_LEVEL_4,
  A7105_POWER_LEVEL_5,
  A7105_POWER_LEVEL_6,
  A7105_POWER_LEVEL_7,
  A7105_POWER_LEVEL_UNKNOWN
};

enum A7105TxMode {
  A7105_TX_MODE_NORMAL,
  A7105_TX_MODE_DIRECT,
  A7105_TX_MODE_DIRECT_FIFO,
  A7105_TX_MODE_PREAMBLE,
  A7105_TX_MODE_RANDOM,
  A7105_TX_MODE_UNKNOWN
};

byte readA7105Reg(byte addr) {
  byte data;
  digitalWrite(SS, LOW);
  SPI.transfer(addr & 0x7F); // 发送寄存器地址，最高位为0表示读取操作
  data = SPI.transfer(0x00); // 发送一个0x00，读取寄存器数据
  digitalWrite(SS, HIGH);
  return data;
}

void writeA7105Reg(byte addr, byte value) {
  digitalWrite(SS, LOW);
  SPI.transfer(addr | 0x80); // 发送寄存器地址，最高位为1表示写入操作
  SPI.transfer(value); // 发送寄存器数据
  digitalWrite(SS, HIGH);
}

void sendA7105Data(byte* data, int length) {
  // 先禁止接收，避免冲突
  writeA7105Reg(A7105_REG_MODE, A7105_MODE_IDLE);
  while (readA7105Reg(A7105_REG_MODE) != A7105_MODE_IDLE) {}

  // 写入数据到发送FIFO
  writeA7105Reg(A7105_REG_MODE, A7105_MODE_TX);
  for (int i = 0; i < length; i++) {
    writeA7105Reg(0x20 + i, data[i]);
  }

  // 启动发送
  writeA7105Reg(A7105_REG_MODE, A7105_MODE_TX);
  while (readA7105Reg(A7105_REG_MODE) == A7105_MODE_TX) {}
}

int receiveA7105Data(byte* buffer, int bufferSize) {
  // 先禁止发送，避免冲突
  writeA7105Reg(A7105_REG_MODE, A7105_MODE_IDLE);
  while (readA7105Reg(A7105_REG_MODE) != A7105_MODE_IDLE) {}

  // 切换到接收模式
  writeA7105Reg(A7105_REG_MODE, A7105_MODE_RX);
  while (readA7105Reg(A7105_REG_MODE) != A7105_MODE_RX) {}

  // 等待接收到数据
  while (readA7105Reg(0x30) == 0) {}

  // 读取接收FIFO中的数据
  int length = readA7105Reg(0x30);
  if (length > bufferSize) {
    length = bufferSize;
  }
  for (int i = 0; i < length; i++) {
    buffer[i] = readA7105Reg(0x31 + i);
  }

  return length;
}

void initA7105() {
  // 初始化寄存器，包括频率校准、功率级别和发送模式等
  writeA7105Reg(A7105_REG_MODE, A7105_DEFAULT_MODE);
  writeA7105Reg(A7105_REG_MODE_CONTROL1, A7105_DEFAULT_MODE_CONTROL1);
  writeA7105Reg(A7105_REG_MODE_CONTROL2, A7105_DEFAULT_MODE_CONTROL2);
  // ... 其他寄存器初始化
  // 频率校准
  writeA7105Reg(0x3E, 0x00);
  writeA7105Reg(0x3F, 0x08);
  writeA7105Reg(0x40, 0x00);
  // 设置功率级别
  setA7105PowerLevel(A7105_POWER_LEVEL_7);
  // 设置发送模式
  setA7105TxMode(A7105_TX_MODE_NORMAL);
}

void setA7105PowerLevel(A7105PowerLevel powerLevel) {
  byte data = readA7105Reg(A7105_REG_MODE_CONTROL1);
  data &= 0xF8; // 将低三位清零
  switch (powerLevel) {
    case A7105_POWER_LEVEL_0:
      data |= 0x00;
      break;
    case A7105_POWER_LEVEL_1:
      data |= 0x01;
      break;
    case A7105_POWER_LEVEL_2:
      data |= 0x02;
      break;
    case A7105_POWER_LEVEL_3:
      data |= 0x03;
      break;
    case A7105_POWER_LEVEL_4:
      data |= 0x04;
      break;
    case A7105_POWER_LEVEL_5:
      data |= 0x05;
      break;
    case A7105_POWER_LEVEL_6:
      data |= 0x06;
      break;
    case A7105_POWER_LEVEL_7:
      data |= 0x07;
      break;
    default:
      data |= 0x07; // 默认为最高功率级别
      break;
  }
  writeA7105Reg(A7105_REG_MODE_CONTROL1, data);
}

void setA7105TxMode(A7105TxMode txMode) {
  byte data = readA7105Reg(A7105_REG_MODE_CONTROL1);
  switch (txMode) {
    case A7105_TX_MODE_NORMAL:
      data &= 0xFC; // 将低两位清零
      break;
    case A7105_TX_MODE_DIRECT:
      data &= 0xFC; // 将低两位清零
      data |= 0x01;
      break;
    case A7105_TX_MODE_DIRECT_FIFO:
      data &= 0xFC; // 将低两位清零
      data |= 0x02;
      break;
    case A7105_TX_MODE_PREAMBLE:
      data &= 0xFC; // 将低两位清零
      data |= 0x03;
      break;
    case A7105_TX_MODE_RANDOM:
      data &= 0xFC; // 将低两位清零
      data |= 0x04;
      break;
    default:
      data &= 0xFC; // 默认为正常发送模式
      break;
  }
  writeA7105Reg(A7105_REG_MODE_CONTROL1, data);
}

int convertSafetyValueToPPM(int safetyValue) {
  int ppmValue = map(safetyValue, 0, 1023, 1000, 2000); // 将安全值映射到1000-2000的PPM值范围
  return ppmValue;
}

void setup() {
  SPI.begin(); // 初始化SPI总线
  pinMode(SS, OUTPUT); // 设置Slave Select引脚为输出模式
  initA7105(); // 初始化A7105芯片
}

void loop() {
  int safetyValue = analogRead(A0); // 读取故障安全值
  int ppmValue = convertSafetyValueToPPM(safetyValue); // 将故障安全值转换为PPM值
}