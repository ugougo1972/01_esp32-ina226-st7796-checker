#include <Arduino.h>
#include "ina226.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 start");
  Serial.println("INA226 init start");

  if (!initIna226()) {
    Serial.println("INA226 init failed");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("INA226 init success");
}

void loop() {
  printIna226Values();
  delay(1000);
}