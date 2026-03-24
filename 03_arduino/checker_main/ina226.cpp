#include "ina226.h"
#include "pins.h"

#include <Wire.h>
#include <INA226_WE.h>

static INA226_WE ina226 = INA226_WE(INA226_I2C_ADDR);

bool initIna226() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  if (!ina226.init()) {
    return false;
  }

  // 必要に応じて後で calibration 設定を明示化する
  // まずは通信成立と基本値取得を優先する

  return true;
}

void readIna226Values(float &busVoltage_V,
                      float &shuntVoltage_mV,
                      float &current_mA,
                      float &power_mW) {
  busVoltage_V = ina226.getBusVoltage_V();
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  current_mA = ina226.getCurrent_mA();
  power_mW = ina226.getBusPower();
}

void printIna226Values() {
  float busVoltage_V = 0.0f;
  float shuntVoltage_mV = 0.0f;
  float current_mA = 0.0f;
  float power_mW = 0.0f;

  readIna226Values(busVoltage_V, shuntVoltage_mV, current_mA, power_mW);

  Serial.print("Bus Voltage [V]: ");
  Serial.println(busVoltage_V, 6);

  Serial.print("Shunt Voltage [mV]: ");
  Serial.println(shuntVoltage_mV, 6);

  Serial.print("Current [mA]: ");
  Serial.println(current_mA, 6);

  Serial.print("Power [mW]: ");
  Serial.println(power_mW, 6);

  Serial.println("---");
}