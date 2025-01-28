/**
 * @file main.ino
 * @brief This file contains the definition of the main function.
 * @details This file contains the main logic to control the LEDs, OLED, and sensor.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#include "LedStatus.h"
#include "CapteurStatus.h"
#include "OledStatus.h"

// Définition des broches
#define SENSOR_PIN 18  // Pin du capteur infrarouge (IR) d'évitement d'obstacle
#define LED_ROUGE 19   // LED rouge pour signaler la présence d'obstacle
#define LED_VERTE 17   // LED verte pour signaler l'absence d'obstacle
#define BUZZER_PIN -1  // Ajoutez cette ligne si vous prévoyez un buzzer

// Instanciation des classes
LedStatus led(LED_ROUGE, LED_VERTE);       // Objet pour gérer les LEDs
Capteur_ESP32 capteur(SENSOR_PIN);         // Objet pour gérer le capteur
ESP32_OLED oled;                           // Objet pour gérer l'OLED

void setup() {
  // Initialiser les composants
  Serial.begin(9600);          // Communication série pour le débogage
  led.setupLED();              // Configure les LEDs
  capteur.setUpCapteur();      // Configure le capteur
  oled.setUpOled();            // Configure l'écran OLED

  // Afficher l'état initial sur l'OLED
  oled.Menu("12:00 PM", "2025-01-27", "READY", '*');  // État initial : READY
  led.setLedState(LED_ROUGE, HIGH);  // Allume la LED rouge en permanence
}

void loop() {
  // Vérifie l'état du capteur
  int state = capteur.getState();

  if (state == LOW) {  // Obstacle détecté
    // Allume la LED verte et éteint la rouge
    led.setLedState(LED_ROUGE, LOW);
    led.setLedState(LED_VERTE, HIGH);

    // Affiche "OPEN" sur l'OLED
    oled.Menu("12:00 PM", "2025-01-27", "OPEN", '*');

    // Maintient la LED verte allumée pendant 3 secondes
    delay(3000);

    // Restaure l'état initial
    led.setLedState(LED_VERTE, LOW);
    led.setLedState(LED_ROUGE, HIGH);

    // Affiche "READY" sur l'OLED
    oled.Menu("12:00 PM", "2025-01-27", "READY", '*');
  }

  delay(100); // Petite pause pour éviter les lectures trop rapides
}
