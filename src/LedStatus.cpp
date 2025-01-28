/**
 * @file LedStatus.cpp
 * @brief This file contains the definition of the LedStatus class.
 * @details This class is used to define the LedStatus properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the LedStatus properties.
 */

#include <Arduino.h>

#define LED_ROUGE 19   // LED rouge pour signaler la présence d'obstacle
#define LED_VERTE 17   // LED verte pour signaler l'absence d'obstacle

void SetUp_Led(){
    pinMode(LED_ROUGE, OUTPUT);  // LED rouge en sortie
    pinMode(LED_VERTE, OUTPUT);  // LED verte en sortie
}