# 07_計算式・変換式 (07_Calculation)

## Calculation (INA226)
## Shunt Voltage
Vshunt = Register * LSB

## Bus Voltage
Vbus = Register * LSB

## Current
Current = ShuntVoltage / Rshunt

## Power
Power = Current * BusVoltage

## Calibration Register
Calibration = (0.00512) / (Current_LSB * Rshunt)
