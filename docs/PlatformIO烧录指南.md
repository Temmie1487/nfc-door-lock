# PlatformIO 烧录指南

## 1. 环境准备

在开始前，请确认你已安装以下内容：

- VS Code
- PlatformIO IDE 插件
- Espressif 32 平台与 Arduino 框架

## 2. 打开项目

1. 使用 VS Code 打开本项目目录。
3. 确认工程根目录中包含以下关键文件：
   - platformio.ini
   - src/main.cpp
   - src/config.h
   - src/hardware/
   - src/logic/
   - src/PN532_support.cpp

## 3. 配置说明

当前项目的 PlatformIO 配置已包含：

- `platform = espressif32`
- `board = esp32dev`
- `framework = arduino`
- 本地 PN532 头文件与源码路径

## 4. 编译与上传

在项目根目录执行以下命令：

```bash
platformio run
platformio run --target upload
```

如果上传失败，可尝试按住 ESP32 的 BOOT 按钮后再重试上传。

## 5. 串口调试

- 串口波特率建议使用 115200。
- 通过串口监视器可以观察 NFC 识别、授权状态、门锁动作和门磁变化，以及 2 秒确认窗口的自动上锁流程。
- 如果你需要更改授权卡片，请修改 [src/config.h](src/config.h) 中的授权 UID 配置。

## 6. 常见问题

- PN532 无法识别：优先检查 TX/RX 交叉接线与 HSU 模式配置。
- 授权失败：确认 UID 已替换为真实卡片 UID。
- 继电器动作异常：检查继电器模块极性和控制逻辑是否与当前固件一致。
