# NFC Smart Door Lock System

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
| PN532 RX | GPIO16 | ESP32 RX |
| PN532 TX | GPIO17 | ESP32 TX |

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
#define PN532_RX_PIN  16
#define PN532_TX_PIN  17

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

## 文档

- [硬件接线指南](docs/硬件接线指南.md) - 详细接线说明
- [PlatformIO烧录指南](docs/PlatformIO烧录指南.md) - 编译烧录步骤

## 许可证

本项目采用 [Apache License 2.0](LICENSE) 开源协议。

---

## English

### Overview

This is an ESP32-based smart door lock system featuring NFC card authentication via PN532 module (HSU mode), relay-controlled electromagnetic lock, and automatic lock functionality with door sensor.

### Features

- ✅ NFC card reading and authorization
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
| PN532 RX | GPIO16 | ESP32 RX |
| PN532 TX | GPIO17 | ESP32 TX |

### Quick Start

1. Clone the project:
```bash
git clone https://github.com/Temmie1487/nfc-door-lock.git
cd nfc-door-lock
```

2. Configure authorized card UIDs in `src/config.h`

3. Build and upload:
```bash
platformio run
platformio run --target upload
```

4. Monitor serial output at 115200 baud

### License

This project is licensed under the [Apache License 2.0](LICENSE).
