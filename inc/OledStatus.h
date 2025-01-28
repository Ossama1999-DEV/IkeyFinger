/**! 
 * @file OledStatus.h
 * @brief This file contains the declaration of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef HS_INC_ESP32_OLED_H_
#define HS_INC_ESP32_OLED_H_

#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

class ESP32_OLED
{   
    public:
        ESP32_OLED();                     // Constructeur
        void setUpOled();                 // Initialisation de l'écran OLED
        void displayText(String text);    // Afficher un texte simple
        void clearDisplay();              // Effacer l'écran OLED
        void Menu(const char *time, const char *date, const char *state, char logo_key); // Affiche le menu
};  

#endif  // HS_INC_ESP32_OLED_H_
