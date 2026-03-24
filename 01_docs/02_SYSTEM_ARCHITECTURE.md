# 02_SYSTEM_ARCHITECTURE
システム構成 / System Architecture

---

## 1. Overview
本システムは、USB電源ラインの電圧・電流・電力を測定し、
ESP32でデータ処理・表示・記録を行う電力測定装置である。

最大仕様（設計目標）:
- 最大電圧: 20V
- 最大電流: 5A
- 最大電力: 100W

主な機能:
- 電圧測定
- 電流測定
- 電力測定
- 積算電力量測定
- TFT表示
- microSDログ保存
- PCシリアル出力
- ロータリーエンコーダによるUI操作

---

## 2. System Block Diagram

### 電力ライン
[ USB-C PD Power ]
│
▼
[ Protection ]
│
▼
[ INA226 ]
│
▼
[ Load ]
│
▼
GND

※ INA226 は VBUS ラインの電流のみ測定する

---

### 制御・表示・記録ライン
        I2C                SPI
[ INA226 ] ───┐
├── [ ESP32 ] ───── [ TFT Display ]
[ DS3231 ] ───┘ │
├──── [ microSD ]
│
├──── [ PC Serial ]
│
└──── [ Rotary Encoder ]

---

## Ground System

All modules share common ground.

- USB Power GND
- INA226 GND
- ESP32 GND
- Display GND
- microSD GND
- RTC GND

All grounds must be connected together.

---

## 3. Interface Summary

| Device | Interface | Purpose |
|--------|-----------|---------|
| INA226 | I2C | Voltage / Current / Power measurement |
| DS3231 | I2C | Real Time Clock |
| TFT Display | SPI | Display |
| microSD | SPI | Data logging |
| Rotary Encoder | GPIO | User input |
| PC | USB Serial | Debug / Log output |

---

## 4. Data Flow

### Measurement Data Flow
INA226 → ESP32 → TFT Display
microSD
PC Serial
Energy Calculation
Graph Buffer

### Time Data Flow
DS3231 → ESP32 → Timestamp → Log file / Display

### User Input Flow
Rotary Encoder → ESP32 → UI Control

---

## 5. USB Pass-Through Structure

本装置は USB 電源ラインの途中に挿入して測定を行う。
USB Power Source → This Device → USB Device

### Internal Connection
| Signal | Connection |
|--------|-----------|
| VBUS | Protection → INA226 → USB-C OUT VBUS |
| GND | Direct |
| D+ | Direct |
| D- | Direct |
| CC | Direct |

※ 電流測定対象は VBUS のみ

---

## 6. Power Measurement Path

INA226 はシャント抵抗によるハイサイド電流測定を行う。
Power Source + ── V+ ──[ Shunt Resistor ]── V- ── Load ── GND

INA226 が測定するもの:
- Bus Voltage（V+ 対 GND）
- Shunt Voltage（シャント抵抗両端電圧）
- Current（Shunt Voltage / Rshunt）
- Power（Voltage × Current）

---

## 7. Current Implementation Scope（現段階）

現在実装対象:

| Function | Status |
|---------|--------|
| INA226 I2C communication | DONE |
| Bus Voltage measurement | TEST |
| Current measurement | TODO |
| Power calculation | TODO |
| TFT display | TODO |
| microSD logging | TODO |
| RTC timestamp | TODO |
| UI control | TODO |

---

## 8. Planned Full Repository Structure（最終構成予定）
01_docs/
README.md
00_PROJECT_RULES.md
01_HARDWARE_PROFILE.md
02_SYSTEM_ARCHITECTURE.md
03_PIN_ASSIGNMENT.md
04_PROGRESS_LOG.md
05_SOFTWARE_ARCHITECTURE.md
06_DATA_FORMAT.md
07_CALCULATION.md
08_TEST_PLAN.md

02_hardware/
schematic/
wiring/
photos/

03_arduino/
checker_main/
checker_main.ino
config.h
pins.h
ina226.cpp
ina226.h
display.cpp
display.h
logger.cpp
logger.h
ui.cpp
ui.h

04_data/
log/
calibration/

05_lib/
external/

06_tools/
scripts/

---

## 9. System Responsibility Separation

| Module | Responsibility |
|-------|----------------|
| INA226 | Measurement |
| ESP32 | Control / Calculation |
| DS3231 | Time |
| TFT | Display |
| microSD | Storage |
| Encoder | User Interface |

---

## 10. Design Policy

設計方針:
- 測定系と制御系を分離する
- 電力ラインとロジックラインを分離する
- 計算ロジックはソフトウェア側で管理する
- 段階的に機能を追加する
- 各機能はモジュールとして分離する
Measurement → Calculation → Display → Logging → UI

段階開発:
1. INA226通信
2. 電圧測定
3. 電流測定
4. 電力測定
5. 表示
6. ログ
7. UI
8. 校正