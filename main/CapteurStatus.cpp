/**
 * @file CapteurStatus.cpp
 * @brief This file contains the definition of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the Capteur_ESP32 properties.
 */

#include "C:\Users\asus\OneDrive\Documents\Arduino\IkeyFinger\inc\CapteurStatus.h"
#include <Arduino.h>

CapteurStatus::CapteurStatus(int pin) : capteurPin(pin) {}

void CapteurStatus::setUpCapteur() {
    pinMode(capteurPin, INPUT);
}

int CapteurStatus::getState() {
    return digitalRead(capteurPin);
}
