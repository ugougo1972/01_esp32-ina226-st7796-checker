#ifndef INA226_H
#define INA226_H

#include <Arduino.h>

bool initIna226();
void readIna226Values(float &busVoltage_V,
                      float &shuntVoltage_mV,
                      float &current_mA,
                      float &power_mW);
void printIna226Values();

#endif