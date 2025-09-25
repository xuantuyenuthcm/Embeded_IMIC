/*
 * Simple Sensor Test - Embedded IMIC Project
 * 
 * This is a basic test program to verify that all sensors are working correctly.
 * Use this before running the main application to troubleshoot hardware issues.
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Pin definitions
#define DHT_PIN 2
#define LDR_PIN A0
#define LED_PIN 13

// Sensor initialization
DHT dht(DHT_PIN, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Sensor Test Program ===");
  
  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  // Initialize DHT sensor
  dht.begin();
  Serial.println("DHT22 sensor initialized");
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Test");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  
  Serial.println("All components initialized");
  delay(2000);
}

void loop() {
  Serial.println("\n--- Sensor Reading ---");
  
  // Test DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    
    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature, 1);
    lcd.print("C H:");
    lcd.print(humidity, 0);
    lcd.print("%");
    
    digitalWrite(LED_PIN, HIGH);
  }
  
  // Test LDR sensor
  int lightLevel = analogRead(LDR_PIN);
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.println(" (0-1023)");
  
  // Display light level on second line
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightLevel);
  
  delay(3000);
}