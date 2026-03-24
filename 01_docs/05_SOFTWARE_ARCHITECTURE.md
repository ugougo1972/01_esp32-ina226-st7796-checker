# 05_ソフトウェア構成 (05_Software Architecture)

## 1. Main Functions

The ESP32 performs the following tasks:

- Read voltage/current from INA226
- Calculate power
- Integrate energy (Wh)
- Integrate charge (Ah)
- Update TFT display
- Store data to microSD
- Send log data to PC via Serial
- Read RTC time
- Read rotary encoder
- Update graph buffer

---

## 2. Task Timing

| Task | Interval |
|------|----------|
| INA226 Read | 0.5 sec |
| Display Update | 0.5 sec |
| Energy Calculation | 0.5 sec |
| SD Logging | 1 sec |
| PC Serial Output | 1 sec |
| Graph Data Update | 60 sec |

---

## 3. Main Loop Structure

Pseudo code:
loop()
{
read_INA226();
calculate_power();
integrate_Wh_Ah();
update_display();
read_encoder();
if (1 second passed)
{
    read_RTC();
    write_SD();
    send_serial();
    update_graph_1sec();
}

if (60 seconds passed)
{
    calculate_1min_average();
    update_graph_buffer();
}
}

---

## 4. Data Structure

### Measurement Data
- Voltage
- Current
- Power
- Energy (Wh)
- Charge (Ah)
- Timestamp

### Graph Buffer
- 60 points
- 1 point = 1 minute average
- Total = 1 hour graph

---

## 5. Log Format (CSV)
Date,Time,Voltage[V],Current[A],Power[W],Energy[Wh],Charge[Ah]
Example:
2026-04-01,12:00:00,19.85,1.42,28.2,0.015,0.0008

---

## 6. Screen Structure

| Screen | Content |
|--------|---------|
| Screen 1 | Main values |
| Screen 2 | Power graph |
| Screen 3 | Current graph |
| Screen 4 | Voltage graph |
| Screen 5 | Statistics |
| Screen 6 | Settings |

Screen switching is controlled by rotary encoder.

## 7. Software Module Structure

The firmware is divided into the following modules:

| Module | File | Role |
|--------|------|------|
| Main | checker_main.ino | Main loop control |
| Config | config.h | System configuration |
| Pins | pins.h | Pin assignment |
| INA226 | ina226.cpp / ina226.h | Sensor control |
| Display | display.cpp / display.h | TFT display control |
| Logger | logger.cpp / logger.h | SD / Serial logging |
| UI | ui.cpp / ui.h | Rotary encoder UI |
| RTC | rtc.cpp / rtc.h | Time management |
| Graph | graph.cpp / graph.h | Graph buffer |
| Calc | calc.cpp / calc.h | Power/Energy calculation |

### Main Program Policy
The .ino file should contain only setup() and loop().

All processing should be implemented in .cpp files.

---

## 8. INA226 Initial Implementation Policy

The first INA226 implementation will be managed in the existing `03_arduino/checker_main` sketch folder.

### File placement
- `checker_main.ino`
  - `setup()`
  - `loop()`
- `pins.h`
  - I2C pin definitions
  - INA226 I2C address definition
- `ina226.h`
  - INA226 function declarations
- `ina226.cpp`
  - INA226 initialization
  - INA226 read functions
  - Serial print helper for measurement values

### Initial scope
The first implementation scope is limited to:
- I2C initialization
- INA226 detection
- INA226 initialization
- Reading Bus Voltage
- Reading Shunt Voltage
- Reading Current
- Reading Power
- Output to Serial monitor

TFT display, SD logging, RTC linkage, graph buffer, and UI control are excluded from this first implementation step.

### Policy
The purpose of the first INA226 implementation is to confirm communication and measurement flow only.

The `.ino` file should remain minimal.
INA226-related processing should be separated into `ina226.cpp` and `ina226.h`.