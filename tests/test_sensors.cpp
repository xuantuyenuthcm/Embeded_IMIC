/*
 * Test file for sensor functionality
 * This file contains unit tests for the sensor reading functions
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#include <unity.h>
#include "../include/sensors.h"
#include "../include/config.h"

// Mock DHT library for testing
class MockDHT {
public:
    float mockTemp = 25.0;
    float mockHumidity = 60.0;
    bool mockError = false;
    
    float readTemperature() {
        if (mockError) return NAN;
        return mockTemp;
    }
    
    float readHumidity() {
        if (mockError) return NAN;
        return mockHumidity;
    }
};

MockDHT mockDHT;

void setUp(void) {
    // Reset mock values before each test
    mockDHT.mockTemp = 25.0;
    mockDHT.mockHumidity = 60.0;
    mockDHT.mockError = false;
}

void tearDown(void) {
    // Clean up after each test
}

void test_temperature_reading_valid() {
    mockDHT.mockTemp = 23.5;
    float temperature = mockDHT.readTemperature();
    
    TEST_ASSERT_EQUAL_FLOAT(23.5, temperature);
    TEST_ASSERT_FALSE(isnan(temperature));
}

void test_humidity_reading_valid() {
    mockDHT.mockHumidity = 65.2;
    float humidity = mockDHT.readHumidity();
    
    TEST_ASSERT_EQUAL_FLOAT(65.2, humidity);
    TEST_ASSERT_FALSE(isnan(humidity));
}

void test_sensor_error_handling() {
    mockDHT.mockError = true;
    
    float temperature = mockDHT.readTemperature();
    float humidity = mockDHT.readHumidity();
    
    TEST_ASSERT_TRUE(isnan(temperature));
    TEST_ASSERT_TRUE(isnan(humidity));
}

void test_temperature_range_validation() {
    // Test normal temperature
    TEST_ASSERT_TRUE(isTemperatureInRange(25.0));
    
    // Test high temperature warning
    TEST_ASSERT_FALSE(isTemperatureInRange(35.0));
    
    // Test low temperature warning
    TEST_ASSERT_FALSE(isTemperatureInRange(5.0));
}

void test_humidity_range_validation() {
    // Test normal humidity
    TEST_ASSERT_TRUE(isHumidityInRange(50.0));
    
    // Test high humidity warning
    TEST_ASSERT_FALSE(isHumidityInRange(85.0));
    
    // Test edge case
    TEST_ASSERT_TRUE(isHumidityInRange(80.0));
}

void test_light_level_description() {
    String darkDesc = getLightLevelDescription(50);
    String brightDesc = getLightLevelDescription(800);
    
    TEST_ASSERT_EQUAL_STRING("Dark", darkDesc.c_str());
    TEST_ASSERT_EQUAL_STRING("Bright", brightDesc.c_str());
}

void test_heat_index_calculation() {
    // Test heat index calculation with known values
    float heatIndex = calculateHeatIndex(30.0, 70.0);
    
    // Heat index should be higher than actual temperature
    TEST_ASSERT_GREATER_THAN(30.0, heatIndex);
    TEST_ASSERT_LESS_THAN(50.0, heatIndex); // Reasonable upper bound
}

void test_sensor_data_validation() {
    SensorData validData;
    validData.temperature = 25.0;
    validData.humidity = 60.0;
    validData.lightLevel = 500;
    validData.timestamp = 1000;
    validData.isValid = true;
    
    TEST_ASSERT_TRUE(validateSensorData(validData));
}

void test_sensor_data_invalid() {
    SensorData invalidData;
    invalidData.temperature = NAN;
    invalidData.humidity = 60.0;
    invalidData.lightLevel = 500;
    invalidData.timestamp = 1000;
    invalidData.isValid = false;
    
    TEST_ASSERT_FALSE(validateSensorData(invalidData));
}

// Implementation of validation functions for testing
bool isTemperatureInRange(float temperature) {
    return (temperature >= TEMP_WARNING_LOW && temperature <= TEMP_WARNING_HIGH);
}

bool isHumidityInRange(float humidity) {
    return (humidity <= HUMIDITY_WARNING_HIGH);
}

String getLightLevelDescription(int lightLevel) {
    if (lightLevel < LIGHT_THRESHOLD_LOW) {
        return "Dark";
    } else if (lightLevel > 700) {
        return "Bright";
    } else {
        return "Normal";
    }
}

float calculateHeatIndex(float temperature, float humidity) {
    // Simplified heat index calculation for testing
    if (temperature < 27.0) return temperature;
    
    float hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + (humidity * 0.094));
    return hi;
}

bool validateSensorData(const SensorData& data) {
    if (!data.isValid) return false;
    if (isnan(data.temperature) || isnan(data.humidity)) return false;
    if (data.lightLevel < 0 || data.lightLevel > 1023) return false;
    if (data.timestamp == 0) return false;
    return true;
}

void setup() {
    UNITY_BEGIN();
    
    RUN_TEST(test_temperature_reading_valid);
    RUN_TEST(test_humidity_reading_valid);
    RUN_TEST(test_sensor_error_handling);
    RUN_TEST(test_temperature_range_validation);
    RUN_TEST(test_humidity_range_validation);
    RUN_TEST(test_light_level_description);
    RUN_TEST(test_heat_index_calculation);
    RUN_TEST(test_sensor_data_validation);
    RUN_TEST(test_sensor_data_invalid);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}