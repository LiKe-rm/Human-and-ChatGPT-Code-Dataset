#include <Scheduler.h>

const int LED1_PIN = 2;
const int LED2_PIN = 3;
const int LED3_PIN = 4;

int led3_state = LOW;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  Serial.begin(9600);
  Scheduler.startLoop(loop);
  Scheduler.startLoop(loop2);
  Scheduler.startLoop(loop3);
}

void loop() {
  digitalWrite(LED1_PIN, HIGH);
  delay(1000);
  digitalWrite(LED1_PIN, LOW);
  delay(1000);
  yield();
}

void loop2() {
  digitalWrite(LED2_PIN, HIGH);
  delay(100);
  digitalWrite(LED2_PIN, LOW);
  delay(100);
  yield();
}

void loop3() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '0') {
      led3_state = LOW;
    } else if (c == '1') {
      led3_state = HIGH;
    }
  }
  digitalWrite(LED3_PIN, led3_state);
  yield();
}
