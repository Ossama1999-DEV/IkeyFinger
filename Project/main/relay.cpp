#include "relay.h"

#define RELAY_PIN  27  // ESP32 GPIO27 connecté au relais

void SetUpRelay() {
    pinMode(RELAY_PIN, OUTPUT); // Définir GPIO comme sortie
}

void ActiveRelay(int state) {
    if (state == LOW) {
        digitalWrite(RELAY_PIN, HIGH); // Active le relais (serrure ouverte)
    } else {
        digitalWrite(RELAY_PIN, LOW);  // Désactive le relais (serrure fermée)
    }
}
