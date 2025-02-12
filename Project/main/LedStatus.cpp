/**
 * @file LedStatus.cpp
 * @brief This file contains the definition of the LedStatus class.
 * @details This class is used to define the LedStatus properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the LedStatus properties.
 */

#include "C:\Users\asus\OneDrive\Documents\Arduino\IkeyFinger\inc\LedStatus.h"
#include <Arduino.h>

// Constructeur
LedStatus::LedStatus(int rougePin, int vertePin)
    : ledRougePin(rougePin), ledVertePin(vertePin) {}

// Configuration des LEDs
void LedStatus::setupLED() {
    pinMode(ledRougePin, OUTPUT);
    pinMode(ledVertePin, OUTPUT);
}

// Change l'état d'une LED
void LedStatus::setLedState(int led, int state) {
    digitalWrite(led, state);
}
