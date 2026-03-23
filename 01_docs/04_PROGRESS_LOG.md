# 04_PROGRESS_LOG

## 目的
本ファイルは、本プロジェクトの進捗を時系列で記録するためのログファイルである。

動作確認が取れた内容、環境構築の完了事項、採用判断を簡潔に記録する。

---

## 2026-03-21

### 開発環境再構築
- GitHub アカウント作成完了
- GitHub リポジトリ `esp32-ina226-st7796-checker` 作成完了
- README 付き、Private 設定でリポジトリ作成
- Arduino IDE 再インストール完了

### Arduino IDE 初期設定
- Sketchbook 保存先を以下に設定

`C:\Users\ugono\Documents\Arduino_source`

- ESP32 ボードパッケージ導入完了
- ボードとして `ESP32 Dev Module` を選択完了
- ライブラリ一覧で `INA226` および `TFT_eSPI` を確認

### GitHub / ローカル連携
- GitHub 上のリポジトリをローカルへ取得
- 保存先は以下

`C:\Users\ugono\Documents\Arduino_source\esp32-ina226-st7796-checker`

- GitHub Web を基本運用とする方針を採用

### 最小スケッチ確認
- `esp32-ina226-st7796-checker.ino` を作成
- 最小スケッチを記述
- コンパイル成功
- 書き込み成功
- シリアルモニタに `ESP32 start` の表示を確認

### ライブラリ選定
- INA226 は未半田付けのため接続確認は未実施
- INA226 用ライブラリ候補を確認
- `INA226_WE` のレビジョン `1.3.0` を確認
- 初期採用ライブラリとして `INA226_WE` を決定

---

## 現時点の到達点
- 新規環境をゼロから再構築した
- ESP32 の最小動作確認が完了した
- GitHub リポジトリ運用を開始した
- INA226 の初期ライブラリ選定まで完了した

---

## 次の予定
- INA226 の役割整理
- シャント抵抗などの基礎用語整理
- INA226 実装準備
- その後 LCD 表示の検討へ進む

---

## 2026-03-XX

### INA226 理論整理
- シャント抵抗の役割を理解
- 電流はシャント電圧から計算されることを理解
- INA226 の内部計算式を理解
  - Current = Current_Register × Current_LSB
  - Power = Power_Register × Power_LSB
  - Power_LSB = 25 × Current_LSB
- Calibration Register の意味を理解
- Current LSB（最小分解能）の意味を理解

### 使用シャント抵抗確認
- モジュール搭載抵抗：R002
- 抵抗値：0.002Ω ±1%
- 大電流測定向け設定であることを確認

### 測定レンジ設計
- USB-C 最大 100W（20V / 5A）測定を想定
- 最大電流レンジを 6A に設定
- Current_LSB ≒ 0.0002A
- Calibration ≒ 12800

### INA226 配線方針決定
INA226 は電源ラインのプラス側に直列に挿入する（ハイサイド測定）。

配線順序：
電源 + → INA226 → 負荷 → GND → 電源 -

### 次の作業
- ESP32 と INA226 の I2C 接続確認
- I2C スキャナでアドレス確認
- INA226 初期化コード作成
- 低電圧（5V）で試験測定
- その後 USB-C 測定回路作成

- ---

## 2026-03-XX INA226 調査・設計

### シャント抵抗確認
- モジュール搭載抵抗：R002
- 抵抗値：0.002Ω
- 大電流測定向けシャント抵抗であることを確認

### INA226 測定原理理解
- シャント抵抗の電圧差から電流を計算する仕組みを理解
- 電力は電圧 × 電流で計算されることを理解
- INA226 は電圧測定ICであり、電流は内部計算で求めていることを理解

### INA226 内部計算理解
- Current Register
- Power Register
- Current LSB
- Calibration Register
の役割を理解

### 測定レンジ設計
USB-C 電力測定（最大100W）を想定し、以下の設計値とした。

| 項目 | 値 |
|------|----|
| シャント抵抗 | 0.002Ω |
| 最大電流 | 6A |
| Current_LSB | 約0.0002A |
| Calibration | 約12800 |

### 配線方針
INA226 は電源ラインのプラス側に直列に挿入する（ハイサイド測定）。

配線順序：
電源 + → INA226 → 負荷 → GND → 電源 -

### 次の作業
- ESP32 と INA226 の I2C 接続
- I2C スキャナでアドレス確認
- INA226 初期化コード作成
- 低電圧・小電流で動作確認
- USB-C 電力測定回路設計

---

## [DONE] システム仕様確定

以下のシステム仕様を確定した。

### 測定
- 電圧
- 電流
- 電力

### 積算
- Wh
- Ah
- 動作時間

### 表示
- 数値表示
- 1時間グラフ
  - 電圧
  - 電流
  - 電力

### 記録
- microSDカードへCSV保存
- 1秒周期ログ

### PC通信
- USBシリアル
- CSV形式で出力

### UI
- ロータリーエンコーダ
  - 回転：画面切替
  - 押下：決定
  - 長押し：設定

### RTC
- DS3231
- 時刻記録用
- 電波時計機能は採用しない

### 測定能力
- 最大 20V / 5A / 100W

### グラフ仕様
- 測定周期：0.5秒
- ログ周期：1秒
- 60秒平均
- 60点（1時間）
---

## 2026-XX-XX USB Power Logger Design Decision

### Measurement Target Decision
It was decided that this device will measure USB power using pass-through method.

Only VBUS current will be measured using INA226 high-side current sensing.

Data lines (USB communication lines) are not measured and will be directly connected.

### Measurement Specification Decision
| Item | Value |
|------|------|
| Max Voltage | 20V |
| Max Current | 5A |
| Max Power | 100W |
| Shunt Resistor | 0.002Ω |
| Current LSB | 0.0002A |
| Calibration | ~12800 |

### Reason for 5A Design
- USB-C standard supports up to 5A
- INA226 module with 0.002Ω shunt is suitable for large current
- Designing for 5A allows measurement up to 100W
- Provides sufficient margin for measurement

### Structure Decision

System structure:

USB-C IN  
→ Protection Circuit  
→ INA226  
→ USB-C OUT  

ESP32 reads INA226 via I2C and performs:
- Voltage measurement
- Current measurement
- Power calculation
- Energy integration (Wh)
- Charge integration (Ah)
- Logging to microSD
- Display on TFT
- Serial output to PC

### Current Project Phase

| Phase | Status |
|------|--------|
| ESP32 basic operation | DONE |
| INA226 theory | DONE |
| INA226 hardware connection | NEXT |
| INA226 measurement test | PENDING |
| TFT display | PENDING |
| USB power path | PENDING |
| SD logging | PENDING |
| System integration | PENDING |
