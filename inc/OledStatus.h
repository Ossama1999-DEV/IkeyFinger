/**! 
 * @file ESP32_OLED.h
 * @brief This file contains the declaration of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties.
 * @version 1.0
 * @date 2021-01-15
 * @author DBIBIH OUSSAMA
 * @note This class is used to define the OLED screen properties.
 */

#ifndef HS_INC_ESP32_OLED_H_
#define HS_INC_ESP32_OLED_H_

#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>




class ESP32_OLED
{   
    public:
        ESP32_OLED();
        void setUpOled();
        void displayText(String text);
        void clearDisplay();
};  // class ESP32_OLED

#endif  // HS_INC_ESP32_OLED_H_