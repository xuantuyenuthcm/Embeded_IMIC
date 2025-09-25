/*
 * Embedded IMIC Project - Display Header
 * 
 * This file contains display-related function declarations and constants.
 * 
 * Author: Embedded Systems Course
 * Date: 2024
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "sensors.h"

// Display menu items
enum MenuItems {
  MENU_TEMP_HUMIDITY = 0,
  MENU_LIGHT_LEVEL = 1,
  MENU_SYSTEM_INFO = 2,
  MENU_DATA_LOGGING = 3
};

// Function declarations
void initializeDisplay();
void updateDisplay();
void displayWelcomeMessage();
void displaySensorData(const SensorData& data);

// Menu-specific display functions
void displayTemperatureHumidity();
void displayLightLevel();
void displaySystemInfo();
void displayDataLogging();

// Utility display functions
void displayMessage(const String& line1, const String& line2);
void displayError(const String& errorMsg);
void displayWarning(const String& warningMsg);
void clearDisplay();

// Animation and effects
void displayLoadingAnimation();
void displayScrollingText(const String& text);

// Custom characters for LCD
void createCustomCharacters();

#endif // DISPLAY_H