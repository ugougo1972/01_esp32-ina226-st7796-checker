# 01_esp32-ina226-st7796-checker

## Overview
ESP32 + INA226 + ST7796 を使用した電力測定・表示システムの開発プロジェクト。

## Project Structure
- 01_docs : Documentation
- 02_hardware : Hardware information
- 03_arduino : Arduino source code
- 04_data : Measurement data / logs
- 05_lib : Custom libraries

## Documents

| No | File | 日本語 |
|----|------|-------|
| 00 | PROJECT_RULES.md | プロジェクトルール |
| 01 | HARDWARE_PROFILE.md | ハードウェア構成 |
| 02 | SYSTEM_ARCHITECTURE.md | システム構成 |
| 03 | PIN_ASSIGNMENT.md | ピン配置 |
| 04 | PROGRESS_LOG.md | 進捗ログ |
| 05 | SOFTWARE_ARCHITECTURE.md | ソフトウェア構成 |
| 06 | DATA_FORMAT.md | データ形式 |
| 07 | CALCULATION.md | 計算式 |
| 08 | TEST_PLAN.md | テスト計画 |

## Current Status
Project initialized. Preparing development environment.

## Arduino Source Structure

All Arduino source code is stored under `03_arduino/checker_main`.

### File structure

- checker_main.ino  
  Main control (setup and loop)

- pins.h  
  Pin assignment and I2C address definitions

- ina226.h / ina226.cpp  
  INA226 sensor control and measurement functions

- display.h / display.cpp  
  TFT display control (planned)

- logger.h / logger.cpp  
  microSD logging (planned)

- rtc.h / rtc.cpp  
  RTC time management (planned)

- encoder.h / encoder.cpp  
  Rotary encoder input (planned)

### Design rule

The `.ino` file should remain minimal and act as the main controller only.  
All hardware control should be implemented in separate `.cpp` modules.