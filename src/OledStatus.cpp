/**!
 * @file OledStatus.cpp
 * @brief This file contains the definition of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties and display information such as time, date, and states.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 * @note This class is designed for ESP32 projects with OLED displays.
 */

#include "ESP32_OLED.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Définition des dimensions de l'écran OLED
#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels
#define OLED_RESET -1    // Pas de broche de reset (ou -1 si partagé)

// Initialisation de l'objet OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * @brief Initialize the OLED display.
 */
void setUpOled() {
  // Initialisation de l'écran OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adresse I2C 0x3C
    for (;;); // Arrêter si l'initialisation échoue
  }
  display.clearDisplay(); // Efface l'écran
  display.display();      // Met à jour l'écran
}

/**
 * @brief Display the menu on the OLED screen.
 * @param time A string representing the current time (e.g., "12:45 PM").
 * @param date A string representing the current date (e.g., "2025-01-27").
 * @param state A string representing the current state (e.g., "OPEN" or "CLOSED").
 * @param logo_key A char representing a logo or symbol to display.
 */
void Menu(const char *time, const char *date, const char *state, char logo_key) {
  display.clearDisplay(); // Efface l'écran

  // Affiche l'heure
  display.setTextSize(1); // Taille de texte réduite pour ajuster les éléments
  display.setTextColor(WHITE);
  display.setCursor(5, 5); // Position de l'heure
  display.print("Time: ");
  display.print(time);

  // Affiche la date
  display.setCursor(5, 20); // Position de la date
  display.print("Date: ");
  display.print(date);

  // Affiche un logo ou une clé (symbolique)
  display.setCursor(100, 5); // Position du logo
  display.print(logo_key);

  // Affiche l'état (OPEN/CLOSED)
  display.setTextSize(2); // Taille de texte plus grande pour l'état
  display.setCursor(30, 40); // Centré pour l'état
  display.print(state);

  display.display(); // Met à jour l'écran
}
