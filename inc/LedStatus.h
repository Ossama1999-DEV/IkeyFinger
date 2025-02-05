/**
 * @file LedStatus.h
 * @brief This file contains the declaration of the LedStatus class.
 * @details This class is used to define the LedStatus properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef LedStatus_h
#define LedStatus_h

class LedStatus
{
    private:
        int ledRougePin;  // Pin de la LED rouge
        int ledVertePin;  // Pin de la LED verte

    public:
        LedStatus(int rougePin, int vertePin);  // Constructeur
        void setupLED();                        // Configure les LEDs
        void setLedState(int led, int state);   // Change l'état d'une LED
};


#endif  // LedStatus_h