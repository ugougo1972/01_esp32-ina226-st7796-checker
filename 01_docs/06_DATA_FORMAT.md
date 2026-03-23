# 06_DATA_FORMAT.md
# Data Format (INA226)

## INA226 Register Map
| Register | Address | Description |
|---------|--------|-------------|
| Configuration | 0x00 | Config |
| Shunt Voltage | 0x01 | Shunt voltage |
| Bus Voltage | 0x02 | Bus voltage |
| Power | 0x03 | Power |
| Current | 0x04 | Current |
| Calibration | 0x05 | Calibration |

## Data Size
| Data | Bits |
|------|------|
| Shunt Voltage | 16 |
| Bus Voltage | 16 |
| Current | 16 |
| Power | 16 |
