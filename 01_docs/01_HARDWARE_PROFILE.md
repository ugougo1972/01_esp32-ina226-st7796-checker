# 01_HARDWARE_PROFILE

## 目的
本ファイルは、本プロジェクトで使用するハードウェアと、その現時点の状態を整理するためのファイルである。

---

## プロジェクト名
- `esp32-ina226-st7796-checker`

---

## 使用予定マイコン
### ESP32-WROOM
- 本プロジェクトの主制御用マイコンとして使用予定
- Arduino IDE での基本動作確認は完了
- 最小スケッチでコンパイルおよびシリアル出力を確認済み

---

## 使用予定センサ
### INA226
- 電圧・電流計測用として使用予定
- 現時点では未半田付け
- まだ接続していない
- Arduino IDE のライブラリ候補を確認済み
- 採用ライブラリは `INA226_WE`

---

## 使用予定表示器
### ST7796S ドライバ搭載 4.0インチ LCD
- 表示用として使用予定
- SPI 接続想定
- 現時点では未着手
- まだ接続・表示確認は行っていない

---

## 開発環境
### Arduino IDE
- 再インストール完了
- ESP32 ボードパッケージ導入済み
- ボードは `ESP32 Dev Module` を選択済み
- Sketchbook 保存先は以下

`C:\Users\ugono\Documents\Arduino_source`

---

## GitHub
- リポジトリ作成済み
- リポジトリ名は以下

`esp32-ina226-st7796-checker`

- 運用は原則 GitHub Web を使用する

---

## 現時点の状態まとめ
- ESP32: 最小確認完了
- INA226: 未接続、未半田付け
- ST7796S LCD: 未着手
- USB-C パススルー構成: 未着手

---

## INA226 電流・電圧測定モジュール

### 使用モジュール
INA226 電流・電圧・電力測定モジュール  
シャント抵抗：0.002Ω（R002 表記）

### 測定仕様（本プロジェクト設定）
| 項目 | 値 |
|------|----|
| シャント抵抗 | 0.002Ω |
| 最大測定電流 | 約6A |
| 最大測定電圧 | ～36V（INA226仕様） |
| 主用途 | USB-C 電力測定（～100W） |

### 端子説明
| 端子 | 役割 |
|------|------|
| VCC | モジュール電源（3.3V） |
| GND | モジュールGND |
| SDA | I2C データ |
| SCL | I2C クロック |
| V+ | 電源側 + 入力 |
| V- | 負荷側 + 出力 |
| ISENSE+ | シャント抵抗 電源側 |
| ISENSE- | シャント抵抗 負荷側 |

### 電流の流れる方向
V+ → ISENSE+ → シャント抵抗 → ISENSE- → V- → 負荷

### I2C アドレス
A0 / A1 ジャンパにより設定

| A1 | A0 | Address |
|----|----|---------|
| 0 | 0 | 0x40 |
| 0 | 1 | 0x41 |
| 1 | 0 | 0x44 |
| 1 | 1 | 0x45 |

本プロジェクトではデフォルトの **0x40** を使用する。

---

## INA226 電流・電圧・電力測定モジュール

### モジュール仕様
- センサIC：INA226
- シャント抵抗：0.002Ω（R002 表記）
- 抵抗精度：±1%
- 温度係数：50ppm/℃

### 測定レンジ（本プロジェクト設定）
| 項目 | 値 |
|------|----|
| 最大電流 | 約6A |
| 最大電圧 | 36V 以下 |
| 主用途 | USB-C 電力測定（最大100W想定） |

### 端子説明
| 端子 | 説明 |
|------|------|
| VCC | モジュール電源（3.3V） |
| GND | モジュールGND |
| SDA | I2C データ |
| SCL | I2C クロック |
| V+ | 電源入力 + |
| V- | 負荷側 + |
| ISENSE+ | シャント抵抗 電源側 |
| ISENSE- | シャント抵抗 負荷側 |

### 電流の流れる順序
V+ → ISENSE+ → シャント抵抗 → ISENSE- → V- → 負荷

### I2C アドレス設定
A0 / A1 ジャンパにより設定する。

| A1 | A0 | Address |
|----|----|---------|
| 0 | 0 | 0x40 |
| 0 | 1 | 0x41 |
| 1 | 0 | 0x44 |
| 1 | 1 | 0x45 |

デフォルト設定（ジャンパ未接続）は 0x40 とする。

---

## [ACTIVE] システム構成（2026-XX-XX確定）

### 電力ライン
USB-C入力 → 保護回路 → INA226 → USB-C出力

本ラインには最大 20V / 5A が流れる。

### 制御ライン
ESP32 を中心に以下の周辺機器を接続する。

| デバイス | 接続 | 用途 |
|----------|------|------|
| INA226 | I2C | 電圧・電流・電力測定 |
| DS3231 | I2C | RTC |
| ST7796S | SPI | TFT表示 |
| microSD | SPI | データ保存 |
| Rotary Encoder | GPIO | 操作入力 |
| PC | USB Serial | ログ出力 |

### I2Cバス
- INA226
- DS3231

### SPIバス
- TFT LCD
- microSD

### ESP32の役割
- センサ読み取り
- 電力計算
- 積算計算
- グラフデータ生成
- LCD描画
- SDカード保存
- PCログ送信
- RTC時刻取得
- UI処理

ESP32をシステムの中央制御装置とする。
---

## [UPDATE] USB Measurement Specification (2026-XX-XX)

### Measurement Target
This project measures USB power using a pass-through configuration.

Measurement line:
USB device is connected through this measurement device, and only VBUS and GND current are measured.

### Measurement Method
- High-side current sensing
- INA226 is inserted in series with VBUS line
- Only current flowing through VBUS is measured
- Data lines (D+, D-, CC) are passed through directly

### USB Measurement Range
| Item | Value |
|------|------|
| Max Voltage | 20V |
| Max Current | 5A |
| Max Power | 100W |
| Measurement Lines | VBUS and GND |

### INA226 Module Specification
| Item | Value |
|------|------|
| Shunt Resistor | 0.002Ω |
| Current Range | Up to approx. 6A |
| Measurement Type | High-side sensing |
