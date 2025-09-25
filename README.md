# Embedded IMIC - STM32F411E-DISCO Pseudo-RTOS

## 🚀 Mô tả
Project STM32F411E-DISCO thực hiện **Pseudo-RTOS** (Real-Time Operating System) với 5 tasks đồng thời:

### 📋 **Tính năng chính:**
- ✅ **Multitasking**: 5 tasks chạy song song với chu kỳ riêng biệt
- ✅ **Message Queue**: Hệ thống hàng đợi thông báo giữa các tasks  
- ✅ **Mutex Protection**: Bảo vệ tài nguyên UART khỏi xung đột
- ✅ **Task Scheduler**: Bộ lập lịch tasks theo thời gian thực
- ✅ **Button Handling**: Xử lý nút nhấn với debouncing
- ✅ **Real-time Monitor**: Giám sát trạng thái qua UART

### 🔧 **Tasks System:**
| Task | Period | Function | LED/Hardware |
|------|--------|----------|--------------|
| Green LED | 1000ms | LED toggle | LD4 (PD12) |
| Orange LED | 1500ms | LED toggle | LD3 (PD13) |
| Red LED | 2000ms | LED toggle | LD5 (PD14) |
| UART Handler | 100ms | Message processing | UART2 |
| Button Monitor | 50ms | Button + Blue LED | PA0, LD6 (PD15) |

## 🖥️ **Hardware**
- **Board**: STM32F411E-DISCO
- **LEDs**:
  - LD3 (Orange): PD13 - 1.5s blink
  - LD4 (Green): PD12 - 1s blink
  - LD5 (Red): PD14 - 2s blink
  - LD6 (Blue): PD15 - Button toggle
- **Button**: PA0 (User button)
- **UART2**: PA2 (TX), PA3 (RX) - 115200 baud

## 💻 **Software**
- **Platform**: PlatformIO
- **Framework**: STM32Cube HAL
- **Upload**: ST-Link
- **Architecture**: Cooperative Multitasking

## 🛠️ **Cách sử dụng**
```bash
# 1. Clone repository
git clone https://github.com/xuantuyenuthcm/Embeded_IMIC.git

# 2. Build project
pio run

# 3. Upload to board  
pio run -t upload

# 4. Monitor serial output
pio device monitor -b 115200
```

## 📊 **Demo hoạt động**
1. **LEDs**: 3 LED nhấp nháy với tần số khác nhau
2. **Button**: Nhấn nút PA0 → toggle LED xanh dương  
3. **Serial**: Xem real-time status của từng task

## 👨‍💻 **Tác giả**
**Xuan Tuyen** - Embedded Systems Developer

---
*Project này thể hiện nguyên lý RTOS cơ bản mà không cần thư viện FreeRTOS phức tạp!*