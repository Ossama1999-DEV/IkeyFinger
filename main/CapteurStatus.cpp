/**
 * @file CapteurStatus.cpp
 * @brief This file contains the definition of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the Capteur_ESP32 properties.
 */

#include "C:\Users\asus\OneDrive\Documents\Arduino\IkeyFinger\CapteurStatus.h"
#include <Arduino.h>

// Constructeur
Capteur_ESP32::Capteur_ESP32(int pin) : sensorPin(pin) {}

// Configuration du capteur
void Capteur_ESP32::setUpCapteur() {
    pinMode(sensorPin, INPUT);
}

// Récupération de l'état du capteur
int Capteur_ESP32::getState() {
    return digitalRead(sensorPin);
}