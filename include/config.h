/*
 * Embedded IMIC Project - Configuration Header
 * 
 * This file contains all the system configuration constants
 * including pin definitions, timing parameters, and thresholds.
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#ifndef CONFIG_H
#define CONFIG_H

// Serial communication settings
#define SERIAL_BAUD 9600

// DHT22 sensor configuration
#define DHT_PIN 2
#define DHT_TYPE DHT22

// LCD I2C configuration
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Pin definitions for LEDs
#define LED_STATUS 8
#define LED_WARNING 9
#define LED_ERROR 10

// Pin definitions for buttons
#define BUTTON_MENU 3
#define BUTTON_SELECT 4

// Sensor pins
#define LDR_PIN A0

// Timing parameters (in milliseconds)
#define SENSOR_READ_INTERVAL 2000  // Read sensors every 2 seconds
#define LOOP_DELAY 100             // Main loop delay
#define DISPLAY_UPDATE_INTERVAL 500 // Update display every 500ms

// Warning thresholds
#define TEMP_WARNING_HIGH 30.0     // Temperature warning threshold (°C)
#define TEMP_WARNING_LOW 10.0      // Low temperature threshold (°C)
#define HUMIDITY_WARNING_HIGH 80.0 // High humidity threshold (%)
#define LIGHT_THRESHOLD_LOW 200    // Low light threshold (0-1023)

// System parameters
#define MAX_SENSOR_READINGS 100    // Maximum stored sensor readings
#define EEPROM_START_ADDRESS 0     // EEPROM starting address for data storage

// Menu system
#define MAX_MENU_ITEMS 4

// Communication protocol
#define COMMAND_BUFFER_SIZE 32

#endif // CONFIG_H