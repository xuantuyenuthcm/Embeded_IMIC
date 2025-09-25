# User Manual - Embedded IMIC Project

## Overview
The Embedded IMIC project is a comprehensive microcontroller-based system that demonstrates fundamental embedded systems concepts including sensor interfacing, real-time data processing, and user interaction.

## Features
- **Real-time sensor monitoring** of temperature, humidity, and light levels
- **LCD display interface** with menu navigation
- **LED status indicators** for system status and warnings
- **Button-controlled menu system** for user interaction
- **Serial communication** for data logging and remote control
- **Data logging capabilities** with timestamp tracking

## Hardware Setup

### Required Components
See `hardware/components_list.md` for complete component specifications.

### Assembly Instructions
1. **Power Setup**
   - Connect Arduino to breadboard power rails
   - Ensure 5V and GND are properly distributed

2. **Sensor Connections**
   - Connect DHT22 to Digital Pin 2 with 10kΩ pull-up resistor
   - Connect LDR to Analog Pin A0 with 10kΩ pull-down resistor

3. **Display Connection**
   - Connect LCD I2C module: SDA to A4, SCL to A5

4. **User Interface**
   - Connect LEDs to Digital Pins 8, 9, 10 with 220Ω resistors
   - Connect buttons to Digital Pins 3, 4 (internal pull-ups used)

5. **Verification**
   - Double-check all connections against circuit diagram
   - Verify power distribution before connecting Arduino

## Software Installation

### Option 1: Arduino IDE
1. Install Arduino IDE from [arduino.cc](https://arduino.cc)
2. Install required libraries (see `libraries.txt`)
3. Open `src/main.ino` in Arduino IDE
4. Select correct board (Arduino Uno) and port
5. Upload the code

### Option 2: PlatformIO
1. Install PlatformIO IDE or extension
2. Open project folder in PlatformIO
3. Run `pio lib install` to install dependencies
4. Build and upload: `pio run --target upload`

## Operation Guide

### Initial Startup
1. Power on the Arduino (USB or external power)
2. Wait for "Embedded IMIC" welcome message on LCD
3. Status LED (green) should turn on indicating system ready

### Menu Navigation
The system has 4 main menu screens accessible via the Menu button:

#### Menu 0: Temperature/Humidity
- Displays current temperature in Celsius
- Shows relative humidity percentage
- Updates every 2 seconds

#### Menu 1: Light Level
- Shows light sensor reading (0-1023)
- Displays percentage equivalent
- Useful for ambient light monitoring

#### Menu 2: System Information
- Shows system uptime in seconds
- Displays available RAM
- System diagnostics

#### Menu 3: Data Logging
- Shows total number of sensor samples taken
- Data logging status
- Sample rate information

### Button Controls
- **Menu Button (Pin 3)**: Cycles through menu options
- **Select Button (Pin 4)**: Selects current menu item (logs to serial)

### LED Indicators
- **Green LED (Pin 8)**: System status - always on when running
- **Yellow LED (Pin 9)**: Warning - lights when temperature/humidity out of range
- **Red LED (Pin 10)**: Error - lights when sensor reading fails

### Serial Communication
Connect to serial monitor at 9600 baud for additional features:

#### Commands
- `STATUS`: Display detailed system status
- `DATA`: Show current sensor readings
- `RESET`: Reset system to initial state

#### Automatic Output
- System startup messages
- Error notifications
- Menu selection confirmations

## Troubleshooting

### Common Issues

#### LCD Not Working
- Check I2C connections (SDA/SCL)
- Verify LCD I2C address (default 0x27)
- Check power connections to LCD

#### Sensor Reading Errors
- Verify DHT22 connections and pull-up resistor
- Check sensor power supply
- Allow sensor warm-up time (2+ seconds)

#### LEDs Not Working
- Check LED polarity (longer leg is positive)
- Verify current limiting resistors
- Test with multimeter

#### Buttons Not Responding
- Check button connections
- Verify internal pull-ups are enabled in code
- Test button continuity

### Warning Thresholds
The system triggers warnings when:
- Temperature > 30°C or < 10°C
- Humidity > 80%
- Sensor reading failures

### Error Codes
- Red LED blinking: DHT sensor communication error
- No display output: LCD communication error
- No serial output: USB/power issue

## Maintenance

### Regular Checks
- Verify all connections remain secure
- Clean LCD display as needed
- Check for loose wires or components

### Calibration
- Sensors may drift over time
- Compare readings with reference instruments
- DHT22 typically maintains accuracy for years

### Updates
- Code updates can be uploaded via Arduino IDE
- Configuration changes in `include/config.h`
- Library updates through package managers

## Educational Applications

### Learning Objectives
- Embedded systems programming
- Sensor interfacing and ADC usage
- I2C communication protocol
- Real-time system design
- User interface development
- Data logging and analysis

### Experiments
1. **Temperature Monitoring**: Track room temperature over time
2. **Light Level Analysis**: Study daily light patterns
3. **Humidity Control**: Monitor environment conditions
4. **System Performance**: Analyze response times and accuracy

### Extensions
- Add data logging to SD card
- Implement wireless communication (WiFi/Bluetooth)
- Add more sensors (pressure, gas, motion)
- Create web interface for remote monitoring
- Implement PID control algorithms

## Safety Information
- Use proper ESD precautions when handling components
- Verify connections before applying power
- Use appropriate current limiting resistors
- Keep workspace clean and organized
- Never exceed component voltage/current ratings

## Support
For technical support or questions:
- Check troubleshooting section
- Review circuit diagram and connections
- Consult component datasheets
- Contact course instructor or TA