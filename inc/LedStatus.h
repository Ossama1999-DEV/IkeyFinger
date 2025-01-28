/**
 * @file LedStatus.h
 * @brief This file contains the declaration of the LedStatus class.
 * @details This class is used to define the LedStatus properties.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#ifndef HS_INC_LEDSTATUS_H_
#define HS_INC_LEDSTATUS_H_

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

#endif  // HS_INC_LEDSTATUS_H_
