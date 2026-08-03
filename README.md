# NFC Smart Door Lock System

[中文](#zhongwen) | [English](#english)

<details>
<summary><h2 id="zhongwen">📖 中文文档 (点击展开)</h2></summary>

基于ESP32的智能门禁系统，使用PN532 NFC模块（HSU模式）、继电器控制电磁锁，并配备门磁传感器实现自动上锁功能。

## 快速开始

### 环境要求

- VS Code + PlatformIO IDE 插件
- ESP32开发板（ESP32 DevKit）
- PN532 NFC模块（配置为HSU/UART模式）

### 安装与烧录

1. 克隆本项目：
```bash
git clone https://github.com/Temmie1487/nfc-door-lock.git
cd nfc-door-lock
```

2. 配置授权卡片UID（`src/config.h`）：
```cpp
static const NFCCard authorizedCards[] = {
    {{0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 4},  // 替换为你的卡片UID
};
```

3. 编译并烧录：
```bash
platformio run
platformio run --target upload
```

4. 查看串口日志（波特率：115200）

## 功能特性

- ✅ NFC卡片识别与授权验证
- ✅ 物理按钮开门
- ✅ 门磁传感器检测
- ✅ 自动上锁（门关闭后2秒确认）
- ✅ 安全超时（10秒未操作自动上锁）
- ✅ 信号消抖处理

## 硬件接线

| 模块 | ESP32引脚 | 说明 |
| --- | --- | --- |
| 继电器 | GPIO13 | HIGH=开锁，LOW=上锁 |
| 按钮 | GPIO4 | 按下为LOW |
| 门磁传感器 | GPIO27 | 关门HIGH，开门LOW |
| PN532 RX | GPIO18 | ESP32 RX |
| PN532 TX | GPIO19 | ESP32 TX |

> ⚠️ PN532需设置为HSU/UART模式，TX/RX需交叉连接

详细接线说明请查看 [硬件接线指南](docs/硬件接线指南.md)

## 项目结构

```
nfc-door-lock/
├── docs/                      # 文档
│   ├── 硬件接线指南.md
│   └── PlatformIO烧录指南.md
├── include/                   # PN532库文件
│   ├── PN532/
│   └── PN532_HSU/
├── src/
│   ├── main.cpp              # 主程序入口
│   ├── config.h              # 配置（引脚/延时/授权卡）
│   ├── hardware/             # 硬件抽象层
│   │   ├── nfc.cpp/h         # NFC读取模块
│   │   ├── relay.cpp/h       # 继电器控制
│   │   ├── button.cpp/h      # 按钮检测
│   │   ├── door_sensor.cpp/h # 门磁传感器
│   │   └── logger.cpp/h      # 日志输出
│   └── logic/                # 业务逻辑层
│       ├── door_lock_state.cpp/h  # 门锁状态机
│       └── access_control.cpp/h   # 授权控制
├── platformio.ini            # PlatformIO配置
├── README.md
└── LICENSE                   # Apache 2.0
```

## 系统工作流程

```
1. 系统启动 → 初始化各模块
2. 检测输入：
   - NFC刷卡 → 验证UID → 授权成功则开锁
   - 按钮按下 → 直接开锁
3. 解锁后状态监测：
   - 门被打开 → 等待关门
   - 门关闭保持2秒 → 确认关门 → 自动上锁
   - 10秒内无操作 → 安全超时 → 自动上锁
```

## 配置说明

所有配置集中在 `src/config.h`：

```cpp
// 引脚定义
#define RELAY_PIN     13
#define BUTTON_PIN    4
#define MAGNET_PIN    27
#define PN532_RX_PIN  18
#define PN532_TX_PIN  19

// 时间参数（毫秒）
#define DOOR_CLOSE_CONFIRM_MS   2000  // 关门确认时间
#define SAFE_TIMEOUT_MS         10000 // 安全超时
#define BUTTON_DEBOUNCE_MS      50    // 按钮消抖
#define DOOR_DEBOUNCE_MS        100   // 门磁消抖
#define NFC_COOLDOWN_MS         2000  // NFC读取冷却时间
#define NFC_READ_TIMEOUT_MS     100   // NFC读取超时
```

## 常见问题

### NFC无法识别
- 检查PN532是否设置为HSU模式
- 确认TX/RX交叉连接
- 查看串口日志是否有PN532固件版本信息

### 授权失败
- 通过串口日志获取卡片UID
- 更新`config.h`中的授权卡片列表

### 继电器动作异常
- 检查继电器模块极性
- 确认GPIO13输出电平

### 烧录失败（Failed to connect to ESP32）
- **原因1：** PN532 连接在 GPIO16/17（UART0）会与烧录通信冲突
- **原因2：** PN532 的 TX/RX 接反了（正确接法：PN532 TXD→ESP32 RXD，PN532 RXD→ESP32 TXD）
- **解决方案：** 检查 TX/RX 是否交叉连接，或换到 UART2 引脚（GPIO18/19），烧录前也可拔掉 TX/RX 线

## 文档

- [硬件接线指南](docs/硬件接线指南.md) - 详细接线说明
- [PlatformIO烧录指南](docs/PlatformIO烧录指南.md) - 编译烧录步骤

## 许可证

本项目采用 [Apache License 2.0](LICENSE) 开源协议。

</details>

---

<details>
<summary><h2 id="english">📖 English Documentation (Click to expand)</h2></summary>

### Overview

An ESP32-based smart door lock system using PN532 NFC module (HSU mode), relay-controlled electromagnetic lock, and door sensor for automatic lock functionality.

### Requirements

- VS Code + PlatformIO IDE extension
- ESP32 DevKit board
- PN532 NFC module (configured for HSU/UART mode)

### Quick Start

1. Clone the project:
```bash
git clone https://github.com/Temmie1487/nfc-door-lock.git
cd nfc-door-lock
```

2. Configure authorized card UIDs (`src/config.h`):
```cpp
static const NFCCard authorizedCards[] = {
    {{0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 4},  // Replace with your card UID
};
```

3. Build and upload:
```bash
platformio run
platformio run --target upload
```

4. Monitor serial output (baud rate: 115200)

### Features

- ✅ NFC card reading and authorization verification
- ✅ Physical button unlock
- ✅ Door sensor monitoring
- ✅ Auto-lock after door close (2-second confirmation)
- ✅ Safety timeout (10-second auto-lock)
- ✅ Signal debouncing

### Hardware Wiring

| Module | ESP32 Pin | Description |
| --- | --- | --- |
| Relay | GPIO13 | HIGH=unlock, LOW=lock |
| Button | GPIO4 | LOW when pressed |
| Door Sensor | GPIO27 | HIGH=closed, LOW=open |
| PN532 RX | GPIO18 | ESP32 RX |
| PN532 TX | GPIO19 | ESP32 TX |

> ⚠️ PN532 must be configured for HSU/UART mode; TX/RX must be cross-connected

For detailed wiring instructions, see [Hardware Wiring Guide](docs/硬件接线指南.md)

### Project Structure

```
nfc-door-lock/
├── docs/                      # Documentation
│   ├── 硬件接线指南.md
│   └── PlatformIO烧录指南.md
├── include/                   # PN532 library
│   ├── PN532/
│   └── PN532_HSU/
├── src/
│   ├── main.cpp              # Main entry point
│   ├── config.h              # Config (pins/timing/authorized cards)
│   ├── hardware/             # Hardware abstraction layer
│   │   ├── nfc.cpp/h         # NFC reader module
│   │   ├── relay.cpp/h       # Relay control
│   │   ├── button.cpp/h      # Button detection
│   │   ├── door_sensor.cpp/h # Door sensor
│   │   └── logger.cpp/h      # Serial logging
│   └── logic/                # Business logic layer
│       ├── door_lock_state.cpp/h  # Door lock state machine
│       └── access_control.cpp/h   # Access control
├── platformio.ini            # PlatformIO config
├── README.md
└── LICENSE                   # Apache 2.0
```

### System Workflow

```
1. System startup → Initialize all modules
2. Input detection:
   - NFC card swipe → Verify UID → Unlock if authorized
   - Button press → Direct unlock
3. Post-unlock monitoring:
   - Door opened → Wait for door to close
   - Door closed for 2 seconds → Confirm closed → Auto-lock
   - No action for 10 seconds → Safety timeout → Auto-lock
```

### Configuration

All configurations are in `src/config.h`:

```cpp
// Pin definitions
#define RELAY_PIN     13
#define BUTTON_PIN    4
#define MAGNET_PIN    27
#define PN532_RX_PIN  18
#define PN532_TX_PIN  19

// Timing parameters (milliseconds)
#define DOOR_CLOSE_CONFIRM_MS   2000  // Door close confirmation time
#define SAFE_TIMEOUT_MS         10000 // Safety timeout
#define BUTTON_DEBOUNCE_MS      50    // Button debounce
#define DOOR_DEBOUNCE_MS        100   // Door sensor debounce
#define NFC_COOLDOWN_MS         2000  // NFC read cooldown
#define NFC_READ_TIMEOUT_MS     100   // NFC read timeout
```

### Troubleshooting

#### NFC not recognized
- Check if PN532 is configured for HSU mode
- Confirm TX/RX are cross-connected
- Check serial logs for PN532 firmware version info

#### Authorization failed
- Get card UID from serial logs
- Update authorized card list in `config.h`

#### Relay malfunction
- Check relay module polarity
- Verify GPIO13 output level

#### Upload Failed (Failed to connect to ESP32)
- **Cause 1:** PN532 connected to GPIO16/17 (UART0) conflicts with upload communication
- **Cause 2:** PN532 TX/RX are connected backwards (correct: PN532 TXD→ESP32 RXD, PN532 RXD→ESP32 TXD)
- **Solution:** This project now uses GPIO18/19 (UART2) by default. If still failing, check if TX/RX are cross-connected

### Documentation

- [Hardware Wiring Guide](docs/硬件接线指南.md) - Detailed wiring instructions
- [PlatformIO Upload Guide](docs/PlatformIO烧录指南.md) - Build and upload steps

### License

This project is licensed under the [Apache License 2.0](LICENSE).

</details>
