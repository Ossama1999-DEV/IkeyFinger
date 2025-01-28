/**
 * @file tes.ino
 * @brief This file contains the definition of the main function.
 * @details This file contains the definition of the main function.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This file contains the definition of the main function.
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define LED_ROUGE 19   // LED rouge pour signaler la présence d'obstacle
#define LED_VERTE 17   // LED verte pour signaler l'absence d'obstacle

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);

  // Configuration des broches
  pinMode(LED_ROUGE, OUTPUT);  // LED rouge en sortie
  pinMode(LED_VERTE, OUTPUT);  // LED verte en sortie

}

void loop() {


  if (state == LOW) {  // Obstacle détecté
    Serial.println("The obstacle is present");
    digitalWrite(LED_ROUGE, HIGH);  // Allume la LED rouge
    digitalWrite(LED_VERTE, LOW);   // Éteint la LED verte

    // Afficher "OPEN" sur l'écran OLED
    display.clearDisplay();  // Efface l'affichage précédent
    display.setTextSize(2);  // Taille du texte (2x)
    display.setTextColor(WHITE);  // Texte blanc
    display.setCursor(30, 25);  // Position du texte (centré approximativement)
    display.print("OPEN");
    display.display();

  } else {  // Pas d'obstacle détecté
    Serial.println("The obstacle is NOT present");
    digitalWrite(LED_ROUGE, LOW);   // Éteint la LED rouge
    digitalWrite(LED_VERTE, HIGH);  // Allume la LED verte

    // Afficher "CLOSE" sur l'écran OLED
    display.clearDisplay();  // Efface l'affichage précédent
    display.setTextSize(2);  // Taille du texte (2x)
    display.setTextColor(WHITE);
    display.setCursor(20, 25);
    display.print("CLOSE");
    display.display();
  }

  delay(100);  // Pause de 100 ms
}
