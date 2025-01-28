/**
 * @file Capteur_ESP32.cpp
 * @brief This file contains the definition of the Capteur_ESP32 class.
 * @details This class is used to define the Capteur_ESP32 properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the Capteur_ESP32 properties.
 */

#include "Capteur_ESP32.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

void SetUp_Capteur(){
    pinMode(SENSOR_PIN, INPUT);  // Capteur IR en entrée
}

/**
 * @brief Get the State object
 * @return int 
 */
int Get_State(){
    int state = digitalRead(SENSOR_PIN);
    if (state == LOW)  // Obstacle détecté
        return state;
    else
        return -1;
}