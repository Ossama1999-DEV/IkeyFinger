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
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

class ESP32_OLED {
  public:
    ESP32_OLED();                              // Constructeur
    void setUpOled();                          // Initialiser l'OLED
    void Menu(const char* time, const char* date, const char* state, char logo_key); // Afficher un menu
};

#endif  // OledStatus_h