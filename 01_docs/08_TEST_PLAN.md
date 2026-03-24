# 08_テスト計画 (08_Test Plan)

## Purpose
Define test procedures for each module.

## Test Items
| Test | Method | Expected Result |
|------|-------|----------------|
| I2C scan | Scanner | INA226 detected |
| Register read | Read register | Value obtained |
| Shunt voltage | Measure | Correct value |
| Bus voltage | Measure | Correct value |
| Current calc | Calculate | Correct |
| Power calc | Calculate | Correct |
| TFT display | Text display | Visible |
| Integration | Full system | Stable |

## Test Procedure Order
1. Power test
2. I2C detection
3. Register read test
4. Calculation test
5. TFT display test
6. Integration test
