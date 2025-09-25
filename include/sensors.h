/*
 * Embedded IMIC Project - Sensors Header
 * 
 * This file contains sensor-related data structures and function declarations.
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#ifndef SENSORS_H
#define SENSORS_H

// Sensor data structure
struct SensorData {
  float temperature;      // Temperature in Celsius
  float humidity;         // Relative humidity in %
  int lightLevel;         // Light level (0-1023)
  unsigned long timestamp; // Timestamp of reading
  bool isValid;           // Data validity flag
};

// Function declarations
void initializeSensors();
void readAllSensors();
bool validateSensorData(const SensorData& data);
void calibrateSensors();

// Sensor-specific functions
float readTemperature();
float readHumidity();
int readLightLevel();

// Data processing functions
float calculateHeatIndex(float temperature, float humidity);
String getLightLevelDescription(int lightLevel);
bool isTemperatureInRange(float temperature);
bool isHumidityInRange(float humidity);

// Data logging functions
void logSensorData(const SensorData& data);
void clearSensorLog();
int getSensorLogCount();

#endif // SENSORS_H