# Components List - Embedded IMIC Project

## Microcontroller
- **Arduino Uno R3** or compatible
  - Microchip ATmega328P
  - 14 digital I/O pins
  - 6 analog inputs
  - USB connection
  - Power jack

## Sensors
- **DHT22 (AM2302)** - Digital Temperature and Humidity Sensor
  - Operating voltage: 3.3-6V DC
  - Temperature range: -40°C to 80°C (±0.5°C accuracy)
  - Humidity range: 0-100% RH (±2-5% accuracy)
  - Digital signal output

- **LDR (Light Dependent Resistor)**
  - Resistance range: 1MΩ (dark) to 10kΩ (bright)
  - Response time: 20-30ms
  - Peak sensitivity: ~540nm

## Display
- **16x2 LCD Display with I2C Backpack**
  - HD44780 controller
  - I2C interface (reduces pin usage)
  - Blue backlight
  - 5V operating voltage

## User Interface
- **2x Tactile Push Buttons**
  - 6x6mm momentary switches
  - SPST (Single Pole Single Throw)
  - Operating force: 2.55N

## Indicators
- **3x LEDs (5mm)**
  - 1x Red LED (Error indicator)
  - 1x Yellow/Amber LED (Warning indicator)
  - 1x Green LED (Status indicator)
  - Forward voltage: 2.0-2.2V
  - Forward current: 20mA

## Resistors
- **3x 220Ω Resistors** (Current limiting for LEDs)
  - 1/4W carbon film
  - 5% tolerance

- **1x 10kΩ Resistor** (DHT22 pull-up)
  - 1/4W carbon film
  - 5% tolerance

- **1x 10kΩ Resistor** (LDR pull-down)
  - 1/4W carbon film
  - 5% tolerance

## Connection Materials
- **Breadboard** (830 tie points)
- **Jumper Wires**
  - Male-to-Male (for breadboard connections)
  - Male-to-Female (for sensor connections)
- **USB Cable** (A to B type for Arduino programming)

## Optional Components
- **External Power Supply** (7-12V DC, 500mA)
- **Enclosure/Case** for finished project
- **Mounting Hardware** (standoffs, screws)

## Tools Required
- Multimeter (for testing connections)
- Wire strippers
- Small screwdriver set
- Computer with Arduino IDE or PlatformIO

## Estimated Cost
- Arduino Uno: $20-25
- DHT22: $5-8
- LCD I2C: $3-5
- LEDs, resistors, buttons: $2-3
- Breadboard and wires: $5-8
- **Total: ~$35-50 USD**

## Suppliers
- **Arduino Official Store**
- **Adafruit**
- **SparkFun**
- **Local electronics stores**
- **Online marketplaces** (Amazon, eBay, AliExpress)

## Safety Notes
- Handle components with care
- Check polarity before connecting
- Avoid short circuits
- Use appropriate current limiting resistors