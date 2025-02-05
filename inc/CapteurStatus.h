/**
 * @file  CapteurStatus.h
 * @brief This file contains the declaration of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef CAPTEURSTATUS_H
#define CAPTEURSTATUS_H

#include <Arduino.h>

class CapteurStatus {
public:
    CapteurStatus(int pin);
    void setUpCapteur();
    int getState();

private:
    int capteurPin;
};

#endif // CAPTEURSTATUS_H


