/**
 * @file  CapteurStatus.h
 * @brief This file contains the declaration of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef HS_INC_CAPTEUR_ESP32_H_
#define HS_INC_CAPTEUR_ESP32_H_

class Capteur_ESP32
{
    private:
        int sensorPin;  // Pin du capteur infrarouge

    public:
        Capteur_ESP32(int pin);  // Constructeur avec initialisation du pin
        void setUpCapteur();     // Configure le capteur
        int getState();          // Retourne l'état du capteur
};

#endif  // HS_INC_CAPTEUR_ESP32_H_
