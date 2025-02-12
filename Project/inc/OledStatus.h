/**! 
 * @file OledStatus.h
 * @brief This file contains the declaration of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef OledStatus_h
#define OledStatus_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Définition des dimensions et broches OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SDA_PIN 21
#define SCL_PIN 22

class OledStatus {
  public:
    OledStatus();  
    void initOLED();  
    void displayMessage(const char* message);  
    void displayStatus(const char* time, const char* date, const char* status); // Nouvelle fonction
  private:
    static Adafruit_SSD1306 display;
};

#endif  // OledStatus_h
