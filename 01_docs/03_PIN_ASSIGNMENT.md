# 03_PIN_ASSIGNMENT.md
# ESP32 Pin Assignment

## 1. I2C Bus

| Signal | ESP32 GPIO | Device |
|--------|------------|--------|
| SDA | GPIO21 | INA226, DS3231 |
| SCL | GPIO22 | INA226, DS3231 |

---

## 2. SPI Bus (TFT + microSD)

| Signal | ESP32 GPIO | Device |
|--------|------------|--------|
| SCK | GPIO18 | TFT, microSD |
| MOSI | GPIO23 | TFT, microSD |
| MISO | GPIO19 | microSD |
| TFT_CS | GPIO15 | TFT |
| TFT_DC | GPIO2 | TFT |
| TFT_RST | GPIO4 | TFT |
| SD_CS | GPIO5 | microSD |

---

## 3. Rotary Encoder

| Signal | ESP32 GPIO |
|--------|------------|
| Encoder A | GPIO32 |
| Encoder B | GPIO33 |
| Encoder SW | GPIO25 |

---

## 4. PC Serial

| Function | Connection |
|----------|------------|
| USB Serial | ESP32 USB Port |

---

## 5. Free GPIO (Future Use)

| GPIO | Purpose |
|------|--------|
| GPIO26 | Buzzer |
| GPIO27 | Status LED |
| GPIO14 | Future expansion |
---

## 6. INA226 Connection

| INA226 Pin | ESP32 |
|-------------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

INA226 is connected via I2C bus.

I2C Address:
0x40 (Default)
