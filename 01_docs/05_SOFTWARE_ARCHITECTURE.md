# 05_SOFTWARE_ARCHITECTURE.md
# Software Architecture

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
