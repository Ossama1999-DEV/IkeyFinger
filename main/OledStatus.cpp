/**
 * @file OledStatus.cpp
 * @brief This file contains the definition of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties and display information such as time, date, and states.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#include "C:\Users\asus\OneDrive\Documents\Arduino\IkeyFinger\OledStatus.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Dimensions de l'écran OLED
#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels
#define OLED_RESET -1    // Pas de broche de reset (ou -1 si partagé)

// Initialisation de l'objet OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Constructeur
ESP32_OLED::ESP32_OLED() {
  // Le constructeur peut rester vide ou inclure une configuration si nécessaire
}

// Méthode pour initialiser l'OLED
void ESP32_OLED::setUpOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Adresse I2C 0x3C
    for (;;); // Bloque si l'initialisation échoue
  }
  display.clearDisplay();
  display.display();
}

// Méthode pour afficher le menu
void ESP32_OLED::Menu(const char* time, const char* date, const char* state, char logo_key) {
  display.clearDisplay(); // Efface l'écran

  // Affiche l'heure
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 5);
  display.print("Time: ");
  display.print(time);

  // Affiche la date
  display.setCursor(5, 20);
  display.print("Date: ");
  display.print(date);

  // Affiche un logo ou une clé (symbolique)
  display.setCursor(100, 5);
  display.print(logo_key);

  // Affiche l'état (OPEN/CLOSED)
  display.setTextSize(2);
  display.setCursor(30, 40);
  display.print(state);

  display.display(); // Met à jour l'écran
}
