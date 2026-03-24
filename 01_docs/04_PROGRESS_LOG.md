# 04_進捗ログ・作業ログ (04_Progress Log)

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

## 2026-03-21

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

## 2026-03-21
## INA226 調査・設計

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

## 2026-03-21
## USB Power Logger Design Decision

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

## Next Session Start Procedure

### Current Repository Structure
01_esp32-ina226-st7796-checker/
├─ README.md
├─ 01_docs/
├─ 02_hardware/
├─ 03_arduino/
│   └─ checker_main/
│       └─ checker_main.ino
├─ 04_data/
├─ 05_lib/
└─ 06_tools/

### Completed
- GitHub Desktop environment initialized
- Local repository created
- Remote repository connected
- Project folder structure created
- Documentation files placed in 01_docs
- Initial commit completed
- Arduino project checker_main created

### Next Tasks
1. Normalize documentation structure
2. Update documentation files
3. Define software architecture
4. Implement ESP32 serial output test
5. Implement I2C scanner
6. Start INA226 communication test

### Git Commit Rules
Commit message format:

type: 内容

Types:
- init : 初期作成
- docs : ドキュメント
- code : コード
- hw   : ハード
- calc : 計算
- test : テスト
- fix  : 修正
- refactor : 整理
- arch : 設計変更

## Development Phase Definition

| Phase | Description |
|------|-------------|
| Phase 1 | ESP32 basic operation |
| Phase 2 | INA226 measurement |
| Phase 3 | TFT display |
| Phase 4 | SD logging |
| Phase 5 | RTC integration |
| Phase 6 | UI implementation |
| Phase 7 | Graph implementation |
| Phase 8 | System integration |
| Phase 9 | Accuracy verification |
| Phase 10 | Final device build |

Current phase: Phase 2 (INA226 measurement preparation)

---

## 2026-03-24

### INA226 実装着手方針

#### 今回の到達目標
INA226 実装の最初の到達目標を以下とした。

- ESP32 と INA226 の I2C 通信を成立させる
- I2C スキャナで INA226 のアドレスを確認する
- INA226 の初期化コードを作成する
- Bus Voltage / Shunt Voltage / Current / Power をシリアルへ表示する
- まだ TFT 表示、SD 保存、RTC 連携には進まない

#### この方針を採用した理由
今回は最小構成で動作確認してから次へ進む方針を優先する。

INA226 の値取得確認の段階で、
- 配線ミス
- I2C 未接続
- アドレス違い
- 初期化失敗
- 測定値の解釈違い
が同時に混ざると切り分けが難しくなるため、
まずは ESP32 + INA226 + Serial のみで確認することにした。

#### 現時点の未実施事項
- INA226 モジュール本体は未接続
- INA226 は未だブレッドボード実装前
- I2C スキャナでのアドレス確認は未実施
- INA226 レジスタ読取は未実施
- 実負荷を使った測定確認は未実施

#### ハード準備に関する判断
INA226 はまだヘッダーピン未半田付けのため、
まずはヘッダーピンのみ半田付けして実装準備を進める方針とした。

この段階では、
- ESP32 との配線確認
- I2C 通信確認
- 初期化確認
を優先する。

高電力系の本配線や USB-C パススルー回路はまだ実施しない。

#### 直近の実装手順
1. INA226 にヘッダーピンを半田付けする
2. ESP32 と INA226 を I2C 接続する
3. I2C スキャナでアドレスを確認する
4. INA226 初期化コードを作成する
5. シリアルモニタへ測定値を表示する
6. 無負荷時の値を確認する
7. 低電圧・小電流条件で既知負荷を用いた確認に進む

#### 成功条件
今回の実装成功条件は以下とする。

- I2C スキャナで INA226 が検出される
- 初期化エラーなく起動する
- 電圧値が読める
- 電流値と電力値が取得できる
- シリアル出力が継続して安定する

#### 未確認事項
- 使用する INA226 モジュールの A0 / A1 配線状態
- 実際の I2C アドレスが 0x40 のままかどうか
- 使用ライブラリの calibration 設定方法
- Current LSB と Calibration Register の実装値
- ライブラリ値と手計算値の一致確認

#### 次に確認すべきこと
- I2C アドレス
- INA226 初期化の成否
- Bus Voltage の妥当性
- Shunt Voltage が 0 付近になるか
- 無負荷時 Current がほぼ 0A になるか
- Power 値が Voltage × Current と大きく矛盾しないか

#### 今回の学習上の重要点
INA226 実装は、最初から表示や保存まで同時に進めず、
まず通信と測定値取得だけに絞る。

ライブラリを使うが、
- Current LSB
- Calibration Register
- Shunt Voltage から電流を求める関係
は後続作業で必ず確認する。

### INA226 無負荷読取確認

INA226 の初期化および測定値読取を確認した。

確認結果:
- Bus Voltage は 0.000000 V で一定
- Shunt Voltage は 0 mV 近傍で微小揺らぎあり
- Current は 0 mA 近傍で微小揺らぎあり
- Power は 0.000000 mW で一定

現時点では測定対象のバス電圧・負荷を接続していないため、
この結果は正常範囲と判断する。

少なくとも以下は確認できた:
- I2C 通信成立
- INA226 初期化成功
- レジスタ読取成功
- 無負荷時ゼロ近傍読取成功

次は低電圧・小電流条件で既知の電源と負荷を接続し、
Bus Voltage / Current / Power が変化することを確認する。

### INA226 端子台実装確認

INA226 基板に端子台を半田付けした。

テスターで確認した結果:
- V+ は他端子とのショートなし
- V- は他端子とのショートなし
- ISENS+ と ISENS- の間のみ導通を確認

ISENS+ と ISENS- の導通は、基板上のシャント抵抗を介したものと判断する。
現時点では、端子台実装に起因する明確なショートは見られない。

次は USB-C PD トリガ基板を組み立て、5V 出力を単体確認する。

### USB-C PD トリガ基板 5V 出力確認

USB-C PD トリガ基板にピンヘッダを半田付けした。
テスターでピンヘッダ間ショートがないことを確認した。

外部給電して電圧確認を行った結果、
以下の各点で 5.143V を確認した。

- スルーホール + → スルーホール -
- ピンヘッダ V+ → ピンヘッダ GND
- スルーホール + → ピンヘッダ GND
- ピンヘッダ V+ → スルーホール -

以上より、USB-C 基板から 5V 系電源を正常に取り出せると判断する。

次は USB-C 基板の V+ / GND を INA226 の V+ / V- に接続し、
Bus Voltage が約 5V になることを確認する。

