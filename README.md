# Embedded IMIC - STM32F411E-DISCO

## Mô tả
Project STM32F411E-DISCO với chức năng:
- LED LD3 (Orange) nhấp nháy trên chân PD13
- Giao tiếp UART2 (115200 baud)
- Hiển thị thông báo qua Serial Monitor

## Hardware
- Board: STM32F411E-DISCO
- LEDs:
  - LD3 (Orange): PD13
  - LD4 (Green): PD12  
  - LD5 (Red): PD14
  - LD6 (Blue): PD15
- UART2: PA2 (TX), PA3 (RX)

## Software
- PlatformIO
- Framework: STM32Cube
- Upload: ST-Link

## Cách sử dụng
1. Mở project trong PlatformIO
2. Build: `pio run`
3. Upload: `pio run -t upload`
4. Monitor: `pio device monitor`

## Tác giả
Xuan Tuyen