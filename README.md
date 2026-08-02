# NFC Smart Door Lock

A compact ESP32-based smart door lock project using PN532 NFC over HSU/UART, a relay-driven electromagnetic lock, and a door sensor.

- [中文](#中文)
- [English](#english)
- [Hardware Guide](docs/%E7%A1%AC%E4%BB%B6%E6%8E%A5%E7%BA%BF%E6%8C%87%E5%8D%97.md)
- [PlatformIO Guide](docs/PlatformIO%E7%83%A7%E5%8D%B7%E6%8C%87%E5%8D%97.md)

---

## 中文

### 项目简介

本项目实现了一个基于 ESP32 的智能门禁系统，支持通过 NFC 卡片或内部按钮开门，并在门被打开后自动上锁。系统适用于家庭、办公室或小型门禁场景。

### 功能特点

- 使用 PN532 模块读取 NFC 卡片并进行授权验证
- 支持内部物理按钮开门
- 解锁后监测门磁状态，并在门关闭并保持 2 秒后确认自动上锁
- 提供 10 秒安全超时，防止长时间保持解锁
- 对门磁传感器增加消抖逻辑，降低误判概率

### 硬件组成

- ESP32 DevKit V1
- PN532 NFC 模块（HSU / UART 模式）
- 光耦隔离继电器模块
- 电磁锁
- 干簧管 / 门磁传感器
- 6x6x5 微动按钮

### 硬件接线

| 功能 | ESP32 引脚 | 说明 |
| --- | --- | --- |
| 继电器控制 | GPIO13 | 当前固件逻辑：HIGH = 开锁，LOW = 上锁 |
| 内部按钮 | GPIO4 | 按下时为 LOW |
| 门磁传感器 | GPIO27 | 关门时为 HIGH，开门时为 LOW |
| PN532 TXD | GPIO16 | ESP32 RX（接收 PN532 发出的数据） |
| PN532 RXD | GPIO17 | ESP32 TX（发送给 PN532 的数据） |

> 说明：PN532 需配置为 HSU/UART 模式，且 TX/RX 线需要交叉连接。

### 项目结构

```text
nfc-door-lock/
├── .github/workflows/           # GitHub Actions 自动构建
├── docs/                        # Markdown 文档
├── include/                     # PN532 相关头文件
├── src/
│   ├── main.cpp                # 主流程入口
│   ├── config.h                # 引脚、延时、授权卡配置
│   ├── hardware/               # 按钮、继电器、门磁、NFC、日志模块
│   ├── logic/                  # 状态机与授权逻辑模块
│   └── PN532_support.cpp       # PN532 实现源码接入文件
├── platformio.ini              # PlatformIO 配置
├── README.md                   # 项目说明
└── LICENSE                     # Apache 2.0 许可证
```

### 快速开始

1. 安装 VS Code 与 PlatformIO IDE 插件。
2. 打开本项目目录。
3. 将 [src/config.h](src/config.h) 中的授权 UID 示例替换为你自己的真实卡片 UID。
4. 在项目根目录执行：

```bash
platformio run
platformio run --target upload
```

5. 使用串口监视器查看 NFC、授权、门锁和门磁状态日志。

### CI / 自动构建

项目已配置 GitHub Actions，提交代码或创建 Pull Request 时会自动执行 PlatformIO 构建检查。

### 许可证

本项目采用 Apache License 2.0 授权，详情请参见 [LICENSE](LICENSE)。

---

## English

### Overview

This project implements a smart door lock based on the ESP32 platform. It supports unlocking with an authorized NFC card or an internal button, and it automatically relocks the door after the door is opened and closed.

### Features

- Reads NFC cards through a PN532 module and validates authorized access
- Supports unlocking via an internal physical button
- Monitors the door sensor and performs automatic relocking after a confirmed close event
- Includes a 10-second safety timeout to prevent long-term unlock states
- Adds debouncing for the door sensor to reduce false triggers

### Hardware Requirements

- ESP32 DevKit V1
- PN532 NFC module (HSU/UART mode)
- Opto-isolated relay module
- Electromagnetic lock
- Reed switch / door sensor
- 6x6x5 tactile push button

### Wiring Summary

| Function | ESP32 Pin | Description |
| --- | --- | --- |
| Relay control | GPIO13 | Current logic: HIGH = unlock, LOW = lock |
| Internal button | GPIO4 | LOW when pressed |
| Door sensor | GPIO27 | HIGH when door is closed, LOW when open |
| PN532 TXD | GPIO16 | ESP32 RX pin |
| PN532 RXD | GPIO17 | ESP32 TX pin |

> Note: The PN532 must be configured in HSU/UART mode, and the TX/RX lines must be connected crosswise.

### Project Structure

```text
nfc-door-lock/
├── .github/workflows/    # GitHub Actions CI
├── docs/                 # Markdown guides
├── include/              # PN532 header files
├── src/
│   ├── main.cpp         # Main firmware entrypoint
│   ├── config.h         # Pins, timing, and authorized-card config
│   ├── hardware/        # Relay, button, door sensor, NFC, and logger modules
│   ├── logic/           # State machine and access-control modules
│   └── PN532_support.cpp # PN532 implementation integration
├── platformio.ini       # PlatformIO configuration
├── README.md            # Project documentation
└── LICENSE              # Apache 2.0 license
```

### Quick Start

1. Install VS Code and the PlatformIO IDE extension.
2. Open this project folder.
3. Replace the example UID in [src/config.h](src/config.h) with your own authorized NFC card UID.
4. Build and upload with:

```bash
platformio run
platformio run --target upload
```

5. Use the serial monitor at 115200 baud to inspect NFC, authorization, lock, and door sensor events.

### CI / Automated Build

This repository is configured with GitHub Actions so the PlatformIO build is checked automatically on pushes and pull requests.

### License

This project is licensed under the Apache License 2.0. See [LICENSE](LICENSE) for details.
