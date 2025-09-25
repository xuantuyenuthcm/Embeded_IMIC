/*
 * Embedded IMIC Project - Main Application
 * 
 * This is the main Arduino sketch for the embedded systems course project.
 * It demonstrates sensor reading, LCD display, and real-time data processing.
 * 
 * Hardware Connections:
 * - DHT22: Data pin to Digital Pin 2
 * - LCD I2C: SDA to A4, SCL to A5
 * - LDR: Analog Pin A0 (with 10K pulldown resistor)
 * - LEDs: Digital Pins 8, 9, 10
 * - Buttons: Digital Pins 3, 4 (with pullup resistors)
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "config.h"
#include "sensors.h"
#include "display.h"

// Global variables
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// System state variables
int currentMenu = 0;
unsigned long lastSensorRead = 0;
bool systemRunning = true;

// Sensor data structure
SensorData sensorData;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_BAUD);
  Serial.println("=== Embedded IMIC Project Starting ===");
  
  // Initialize hardware
  initializePins();
  initializeSensors();
  initializeDisplay();
  
  Serial.println("System initialized successfully!");
  displayWelcomeMessage();
  
  delay(2000);
}

void loop() {
  // Read sensors periodically
  if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL) {
    readAllSensors();
    lastSensorRead = millis();
  }
  
  // Handle button inputs
  handleButtonInputs();
  
  // Update display based on current menu
  updateDisplay();
  
  // Update LED indicators
  updateLEDIndicators();
  
  // Send data via serial if requested
  if (Serial.available()) {
    handleSerialCommands();
  }
  
  delay(LOOP_DELAY);
}

void initializePins() {
  // Configure LED pins as outputs
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  
  // Configure button pins as inputs with pullup
  pinMode(BUTTON_MENU, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  
  // Turn on status LED to indicate system is running
  digitalWrite(LED_STATUS, HIGH);
}

void initializeSensors() {
  dht.begin();
  // Initialize other sensors here
  Serial.println("Sensors initialized");
}

void initializeDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.println("Display initialized");
}

void displayWelcomeMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Embedded IMIC");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
}

void readAllSensors() {
  // Read DHT22 sensor
  sensorData.temperature = dht.readTemperature();
  sensorData.humidity = dht.readHumidity();
  
  // Read light sensor
  sensorData.lightLevel = analogRead(LDR_PIN);
  
  // Update timestamp
  sensorData.timestamp = millis();
  
  // Validate readings
  if (isnan(sensorData.temperature) || isnan(sensorData.humidity)) {
    Serial.println("Error reading DHT sensor!");
    digitalWrite(LED_ERROR, HIGH);
  } else {
    digitalWrite(LED_ERROR, LOW);
  }
}

void handleButtonInputs() {
  static bool menuButtonPressed = false;
  static bool selectButtonPressed = false;
  
  // Menu button handling
  if (digitalRead(BUTTON_MENU) == LOW && !menuButtonPressed) {
    currentMenu = (currentMenu + 1) % 4; // Cycle through 4 menu options
    menuButtonPressed = true;
    delay(50); // Debounce
  } else if (digitalRead(BUTTON_MENU) == HIGH) {
    menuButtonPressed = false;
  }
  
  // Select button handling
  if (digitalRead(BUTTON_SELECT) == LOW && !selectButtonPressed) {
    handleMenuSelection();
    selectButtonPressed = true;
    delay(50); // Debounce
  } else if (digitalRead(BUTTON_SELECT) == HIGH) {
    selectButtonPressed = false;
  }
}

void updateDisplay() {
  switch (currentMenu) {
    case 0:
      displayTemperatureHumidity();
      break;
    case 1:
      displayLightLevel();
      break;
    case 2:
      displaySystemInfo();
      break;
    case 3:
      displayDataLogging();
      break;
  }
}

void displayTemperatureHumidity() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(sensorData.temperature, 1);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(sensorData.humidity, 1);
  lcd.print("%");
}

void displayLightLevel() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light Level:");
  
  lcd.setCursor(0, 1);
  lcd.print(sensorData.lightLevel);
  lcd.print(" (");
  lcd.print(map(sensorData.lightLevel, 0, 1023, 0, 100));
  lcd.print("%)");
}

void displaySystemInfo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Uptime: ");
  lcd.print(millis() / 1000);
  lcd.print("s");
  
  lcd.setCursor(0, 1);
  lcd.print("Free RAM: ");
  lcd.print(getFreeRAM());
}

void displayDataLogging() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Data Logging");
  
  lcd.setCursor(0, 1);
  lcd.print("Samples: ");
  lcd.print(millis() / SENSOR_READ_INTERVAL);
}

void updateLEDIndicators() {
  // Status LED - always on when system running
  digitalWrite(LED_STATUS, systemRunning);
  
  // Warning LED - temperature or humidity out of range
  bool warning = (sensorData.temperature > TEMP_WARNING_HIGH || 
                  sensorData.temperature < TEMP_WARNING_LOW ||
                  sensorData.humidity > HUMIDITY_WARNING_HIGH);
  digitalWrite(LED_WARNING, warning);
}

void handleMenuSelection() {
  switch (currentMenu) {
    case 0:
      Serial.println("Temperature/Humidity selected");
      break;
    case 1:
      Serial.println("Light level selected");
      break;
    case 2:
      Serial.println("System info selected");
      break;
    case 3:
      Serial.println("Data logging selected");
      break;
  }
}

void handleSerialCommands() {
  String command = Serial.readString();
  command.trim();
  
  if (command == "STATUS") {
    printSystemStatus();
  } else if (command == "DATA") {
    printSensorData();
  } else if (command == "RESET") {
    systemReset();
  } else {
    Serial.println("Unknown command. Available: STATUS, DATA, RESET");
  }
}

void printSystemStatus() {
  Serial.println("=== System Status ===");
  Serial.print("Uptime: ");
  Serial.print(millis() / 1000);
  Serial.println(" seconds");
  Serial.print("Current Menu: ");
  Serial.println(currentMenu);
  Serial.print("Free RAM: ");
  Serial.print(getFreeRAM());
  Serial.println(" bytes");
}

void printSensorData() {
  Serial.println("=== Sensor Data ===");
  Serial.print("Temperature: ");
  Serial.print(sensorData.temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(sensorData.humidity);
  Serial.println(" %");
  Serial.print("Light Level: ");
  Serial.print(sensorData.lightLevel);
  Serial.println(" (0-1023)");
  Serial.print("Timestamp: ");
  Serial.println(sensorData.timestamp);
}

void systemReset() {
  Serial.println("System reset requested...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resetting...");
  delay(1000);
  
  // Reset variables
  currentMenu = 0;
  lastSensorRead = 0;
  
  displayWelcomeMessage();
  Serial.println("System reset complete");
}

int getFreeRAM() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}