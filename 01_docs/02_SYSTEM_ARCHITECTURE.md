# 02_システム構成 (02_System Architecture)

## 1. Overview

This project is an ESP32-based USB Power Logger that measures voltage, current, and power,
displays the values on a TFT screen, logs data to microSD, and outputs logs to a PC.

Maximum measurement specification:
- Voltage: 20V
- Current: 5A
- Power: 100W

---

## 2. System Block Diagram

### Power Line

電源 + → INA226 → 負荷 → GND

[ USB-C PD ]
       │
       ▼
[ INA226 ]──I2C──[ ESP32 ]──SPI──[ TFT ]
       │
       ▼
     負荷

This line carries actual load current (up to 5A).

### Control & Logging Line

ESP32 is the central controller.

ESP32 connections:

| Device | Interface | Purpose |
|--------|-----------|---------|
| INA226 | I2C | Voltage/Current/Power measurement |
| DS3231 | I2C | RTC |
| ST7796 TFT | SPI | Display |
| microSD | SPI | Data logging |
| Rotary Encoder | GPIO | User input |
| PC | USB Serial | Data logging / Debug |

---

## 3. Interface Summary

### I2C Bus
Shared by:
- INA226
- DS3231

Signal lines:
- SDA
- SCL

### SPI Bus
Shared by:
- TFT Display
- microSD

Shared signals:
- SCK
- MOSI
- MISO (used by SD)

Individual signals:
- TFT_CS
- TFT_DC
- TFT_RST
- SD_CS

### GPIO
- Encoder A
- Encoder B
- Encoder Switch

### USB
- PC Serial Communication
- Log output
- Debug

---

## 4. Data Flow

INA226 → ESP32 → 
    ├ TFT Display
    ├ microSD (CSV log)
    ├ PC Serial
    ├ Energy Calculation (Wh/Ah)
    └ Graph Buffer

RTC → ESP32 → Timestamp → SD / PC Log

Rotary Encoder → ESP32 → UI Control

---

## 5. Timing Concept

| Task | Interval |
|------|----------|
| INA226 Read | 0.5 sec |
| Display Update | 0.5 sec |
| SD Write | 1 sec |
| PC Serial Output | 1 sec |
| Graph Average | 60 sec |
| Graph Width | 60 points (1 hour) |

---

## 6. System Role Summary

| Module | Role |
|--------|------|
| INA226 | Measurement |
| ESP32 | Control / Calculation |
| TFT | Display |
| microSD | Logging |
| DS3231 | Timekeeping |
| Encoder | User Interface |
| PC | External Logging |
---

## 7. USB Pass-Through Structure

This device is installed between USB power supply and USB device.

Connection structure:

USB Power Source → This Device → USB Device

### Internal Power Line

VBUS line:
USB-C IN VBUS → Protection Circuit → INA226 → USB-C OUT VBUS

GND line:
USB-C IN GND → USB-C OUT GND (Direct connection)

### Data Line Connection
- D+ → Direct connection
- D- → Direct connection
- CC → Direct connection

Only VBUS current is measured by INA226.

## 8. Repository Structure

01_esp32-ina226-st7796-checker/
├─ README.md
├─ 01_docs/
├─ 02_hardware/
├─ 03_arduino/
│   └─ checker_main/
│       ├─ checker_main.ino
│       ├─ config.h
│       ├─ pins.h
│       ├─ ina226.cpp
│       ├─ ina226.h
│       ├─ display.cpp
│       ├─ display.h
│       ├─ logger.cpp
│       ├─ logger.h
│       └─ ui.cpp
│
├─ 04_data/
├─ 05_lib/
└─ 06_tools/

Each directory role:

| Directory | Role |
|----------|------|
| 01_docs | Documentation |
| 02_hardware | Hardware information |
| 03_arduino | Firmware source code |
| 04_data | Measurement data |
| 05_lib | External / custom libraries |
| 06_tools | PC tools / scripts |
