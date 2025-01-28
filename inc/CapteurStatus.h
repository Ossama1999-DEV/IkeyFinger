/**
 * @file 
 * @brief This file contains the declaration of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the Capteur_ESP32 properties.
 */

// Définition des broches
#define SENSOR_PIN 18  // Pin du capteur infrarouge (IR) d'évitement d'obstacle


#ifndef HS_INC_CAPTEUR_ESP32_H_
#define HS_INC_CAPTEUR_ESP32_H_

#include <Adafruit_GFX.h>

protected:
    int SENSOR_PIN = 18;  // Pin du capteur infrarouge (IR) d'évitement d'obstacle


class Capteur_ESP32
{
    public:
        Capteur_ESP32();
        void SetUp_Capteur();
};  // class Capteur_ESP32

#endif  // HS_INC_CAPTEUR_ESP32_H_