/**
 * @file OledStatus.cpp
 * @brief This file contains the definition of the ESP32_OLED class.
 * @details This class is used to define the OLED screen properties and display information such as time, date, and states.
 * @version 1.0
 * @date 2025-01-27
 * @author DBIBIH OUSSAMA
 */

#include "OledStatus.h"

Adafruit_SSD1306 OledStatus::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OledStatus::OledStatus() {}

void OledStatus::initOLED() {
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Échec de l'initialisation de l'OLED !");
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 10);
    display.println("Welcome");
    display.display();
}

void OledStatus::displayMessage(const char* message) {
    display.clearDisplay();
    display.setCursor(20, 10);
    display.println(message);
    display.display();
}

void OledStatus::displayStatus(const char* time, const char* date, const char* status) {
    display.clearDisplay();
    
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // Affichage de l'heure
    display.setCursor(10, 5);
    display.print("Time: ");
    display.print(time);

    // Affichage de la date
    display.setCursor(10, 20);
    display.print("Date: ");
    display.print(date);

    // Affichage de l'état
    display.setTextSize(2);
    display.setCursor(30, 40);
    display.print(status);

    display.display();
}

void OledStatus::displayDoorOpen() {
    display.clearDisplay();
    display.setCursor(30, 20);
    display.setTextSize(2);
    display.println("OPEN");
    display.display();
}

void OledStatus::displayDoorClose() {
    display.clearDisplay();
    display.setCursor(30, 20);
    display.setTextSize(2);
    display.println("CLOSE");
    display.display();
}
