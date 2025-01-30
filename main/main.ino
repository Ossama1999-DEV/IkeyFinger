/**
 * ESP32 Web Server - Contrôle de la LED à distance
 * 
 */
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>


// Définition des paramètres du réseau WiFi
const char* ssid = "OussamaEsp32";    // Nom du réseau WiFi (SSID)
const char* password = "123456789";    // Mot de passe WiFi

// Définition de la LED
#define LED_PIN 19  // LED branchée sur GPIO 19
bool etatLed = false; // État initial de la LED

// Création du serveur Web
WebServer server(80);

// Page HTML stockée en mémoire
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 LED Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; color: #333; }
        .container { margin-top: 50px; }
        h1 { color: #007BFF; }
        .status { font-size: 24px; margin: 20px 0; font-weight: bold; }
        .button { font-size: 20px; padding: 15px; border: none; cursor: pointer; border-radius: 5px; transition: 0.3s; margin: 10px; width: 150px; }
        .on { background-color: #28a745; color: white; }
        .off { background-color: #dc3545; color: white; }
        .button:hover { transform: scale(1.1); }
    </style>
    <script>
        function toggleLED(state) {
            fetch("/" + state)  // Corrigé pour envoyer les requêtes "/on" et "/off"
            .then(response => response.text())
            .then(data => {
                document.getElementById("led-status").innerText = data;
            });
        }
    </script>
</head>
<body>
    <div class="container">
        <h1>Contrôle de la LED ESP32</h1>
        <p class="status">LED est <span id="led-status">%STATE%</span></p>
        <button class="button on" onclick="toggleLED('on')">Allumer</button>
        <button class="button off" onclick="toggleLED('off')">Éteindre</button>
    </div>
</body>
</html>
)rawliteral";

// Fonction pour mettre à jour l'état de la LED dans la page HTML
String processor(const String& var) {
    if (var == "STATE") {
        return (etatLed) ? "ALLUMÉE" : "ÉTEINTE";
    }
    return "";
}

// Gestion de la page principale
void handleRoot() {
    String page = index_html;
    page.replace("%STATE%", (etatLed) ? "ALLUMÉE" : "ÉTEINTE");
    server.send(200, "text/html", page);
}

// Allumer la LED
void handleOn() {
    etatLed = false;  // <-- Change de "true" à "false"
    digitalWrite(LED_PIN, LOW);  // <-- Change de "HIGH" à "LOW"
    server.send(200, "text/plain", "ALLUMÉE");
}

// Éteindre la LED
void handleOff() {
    etatLed = true;  // <-- Change de "false" à "true"
    digitalWrite(LED_PIN, HIGH);  // <-- Change de "LOW" à "HIGH"
    server.send(200, "text/plain", "ÉTEINTE");
}

DNSServer dnsServer;
const byte DNS_PORT = 53;

// Configuration initiale
void setup() {
    Serial.begin(115200);
    Serial.println("Démarrage de l'ESP32 en mode Point d'Accès...");

    // Démarrage du WiFi en mode AP
    bool success = WiFi.softAP(ssid, password);

    if (success) {
        Serial.println("WiFi AP démarré !");
        Serial.print("Adresse IP du serveur : ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("Échec de la création du WiFi AP !");
    }

    // Configuration du DNS captif
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());  // Redirige toutes les requêtes vers l'ESP32

    // Configurer la LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Définir les routes du serveur Web
    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);

    // Démarrer le serveur Web
    server.begin();
}

// Boucle principale
void loop() {
    dnsServer.processNextRequest();  // Gère les requêtes DNS
    server.handleClient();  // Gère les requêtes HTTP
}
