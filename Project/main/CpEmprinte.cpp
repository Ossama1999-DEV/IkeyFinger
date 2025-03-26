#include "CpEmprinte.h"
#include <DFRobot_ID809.h>

// Définir les broches RX et TX pour le capteur d'empreintes
#define FP_RX 16
#define FP_TX 17

HardwareSerial mySerial(1);
DFRobot_ID809 fingerprint;

void setupEmprinte() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, FP_RX, FP_TX);
  fingerprint.begin(mySerial);

  while (!fingerprint.isConnected()) {
    Serial.println("Échec de la communication avec le capteur. Vérifiez les connexions.");
    delay(1000);
  }
}

void SetEmprinte() {
  uint8_t id = fingerprint.getEmptyID();
  if (id == ERR_ID809) {
    Serial.println("Aucun ID disponible pour l'enregistrement.");
    return;
  }

  Serial.print("Enregistrement de l'empreinte sous l'ID : ");
  Serial.println(id);

  for (int i = 0; i < 3; i++) {
    Serial.println("Veuillez placer votre doigt sur le capteur.");
    while (!fingerprint.detectFinger());

    if (fingerprint.collectionFingerprint(10) == ERR_ID809) {
      Serial.println("Échec de la collecte de l'empreinte. Veuillez réessayer.");
      return;
    }

    Serial.println("Empreinte collectée. Veuillez retirer votre doigt.");
    while (fingerprint.detectFinger());
    delay(1000);
  }

  if (fingerprint.storeFingerprint(id) != ERR_ID809) {
    Serial.println("Empreinte enregistrée avec succès !");
  } else {
    Serial.println("Échec de l'enregistrement de l'empreinte.");
  }
}

// Nouvelle fonction pour tester une empreinte enregistrée
bool CheckEmprinte() {
  if (!fingerprint.detectFinger()) {
    return false;
  }

  if (fingerprint.collectionFingerprint(10) == ERR_ID809) {
    Serial.println("Erreur de lecture empreinte.");
    return false;
  }

  uint8_t result = fingerprint.search();
  if (result != 0) {
    Serial.print("Empreinte reconnue avec ID: ");
    Serial.println(result);
    return true;
  }

  Serial.println("Empreinte non reconnue.");
  return false;
}
