/**
 * @file WebServerESP32.cpp
 * @brief Implementation of the WebServerESP32 class.
 * @author DBIBIH Oussama
 * @version 0.1
 * @date 2021-02-10
 * 
 * This file contains the implementation of the WebServerESP32 class.
 */

#include "C:\Users\asus\OneDrive\Documents\Arduino\IkeyFinger\WebServerESP32.h"

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 LED Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 50px; }
        h2 { color: #333; }
        button { padding: 15px 30px; font-size: 20px; margin: 10px; cursor: pointer; }
        .on { background-color: green; color: white; }
        .off { background-color: red; color: white; }
    </style>
</head>
<body>
    <h2>Contrôle de la LED ESP32</h2>
    <button class="on" onclick="sendRequest('/on')">Allumer</button>
    <button class="off" onclick="sendRequest('/off')">Éteindre</button>

    <script>
        function sendRequest(url) {
            fetch(url).then(response => console.log("Commande envoyée"));
        }
    </script>
</body>
</html>
)rawliteral";

WebServerESP32::WebServerESP32(const char* ssid, const char* password, int pin) : server(80), ledPin(pin) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    server.on("/", [this]() { server.send(200, "text/html", htmlPage); });
    server.on("/on", [this]() { digitalWrite(ledPin, HIGH); server.send(200, "text/plain", "LED ON"); });
    server.on("/off", [this]() { digitalWrite(ledPin, LOW); server.send(200, "text/plain", "LED OFF"); });
}

void WebServerESP32::begin() {
    server.begin();
}

void WebServerESP32::handleClient() {
    server.handleClient();
}
