/**!
 * @file ESP32_OLED.cpp
 * @brief This file contains the definition of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the OLED screen properties.
 */


#include "ESP32_OLED.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Définition des broches
#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels
#define OLED_RESET -1 // Pas de broche de reset (ou -1 si partagé)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setUpOled(){
    // Initialisation de l'écran OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Adresse I2C 0x3C
    for (;;);  // Ne pas continuer si l'initialisation échoue
  }
  display.clearDisplay();
}


void Menu(char *etat){ 

    display.clearDisplay();
    display.setTextSize(2);  // Taille du texte (2x)
    display.setTextColor(WHITE);  // Texte blanc
    display.setCursor(, );
    display.print(time);
    
    display.setCursor(, );
    display.print(date);

    display.setCursor(, );
    display.print(logo_key); // logo de la clé

    display.setCursor(, );
    display.print(date);
        
    display.setCursor(30, 25);  // Position du texte (centré approximativement)
    display.print("OPEN");
    display.display();
}