/**
 * @file main.ino
 * @brief Programme principal pour contrôler une LED et une porte avec un ESP32
 * @author Oussama DBIBIH
 * @date 2021-09-15
 * @version 1.0
 */

/* Library */
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ezButton.h>
#include "relay.h"
#include "CpEmprinte.h"

// Définition des identifiants de connexion
const char* validUser = "admin";
const char* validPass = "1234";

// Définition des paramètres du réseau WiFi
const char* ssid = "OussamaEsp32";  // Nom du réseau WiFi (SSID)
const char* password = "123456789"; // Mot de passe WiFi

// Définition de la LED
#define LED_PIN 19  // LED branchée sur GPIO 19
bool etatLed = false; // État initial de la LED

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C
ezButton button(27);  // create ezButton object that attach to the ESP32 pin GPIO27
unsigned long lastCount = 0;
// Function to display "OPEN"
void displayDoorOpen() {
    oled.clearDisplay();
    oled.setCursor(0, 10);
    oled.println("OPEN");
    oled.display();
  }
  
  // Function to display "CLOSE"
  void displayDoorClose() {
    oled.clearDisplay();
    oled.setCursor(0, 10);
    oled.println("CLOSE");
    oled.display();
  }

// Création du serveur Web
WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;

// Pin Relay and button
#define BUTTON_PIN 22  // ESP32 GPIO22 connecté au bouton
#define RELAY_PIN  27  // ESP32 GPIO27 connecté au relais

// Page HTML de connexion
const char login_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login.page</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; color: #333; }
        .container { margin-top: 100px; max-width: 300px; margin-left: auto; margin-right: auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }
        h1 { color: #007BFF; }
        input { width: 100%; padding: 10px; margin: 10px 0; border: 1px solid #ccc; border-radius: 5px; }
        .button { width: 100%; padding: 10px; border: none; cursor: pointer; border-radius: 5px; transition: 0.3s; background-color: #007BFF; color: white; font-size: 16px; }
        .button:hover { background-color: #0056b3; }
        .error { color: red; font-weight: bold; display: none; }
    </style>
    <script>
        function login() {
            var username = document.getElementById("username").value;
            var password = document.getElementById("password").value;
            
            fetch("/login?user=" + username + "&pass=" + password)
            .then(response => response.text())
            .then(data => {
                if (data === "SUCCESS") {
                    localStorage.setItem("esp32_auth", "true");
                    window.location.href = "/control";
                } else {
                    document.getElementById("error-message").style.display = "block";
                }
            });
        }

        if (localStorage.getItem("esp32_auth") === "true") {
            window.location.href = "/control";
        }
    </script>
</head>
<body>
    <div class="container">
        <h1>🔒 HOME Login</h1>
        <input type="text" id="username" placeholder="Nom d'utilisateur">
        <input type="password" id="password" placeholder="Mot de passe">
        <p class="error" id="error-message">Login ou mot de passe incorrect</p>
        <button class="button" onclick="login()">Se connecter</button>
    </div>
</body>
</html>
)rawliteral";

// Page de contrôle avec LED et Porte
const char control_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>login.page</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; color: #333; }
        .container { margin-top: 50px; }
        h1 { color: #007BFF; }
        .status { font-size: 24px; margin: 20px 0; font-weight: bold; }

        /* STYLE DES BOUTONS */
        .button { font-size: 20px; padding: 15px; border: none; cursor: pointer; border-radius: 5px; transition: 0.3s; margin: 10px; width: 150px; }
        .on { background-color: #28a745; color: white; }
        .off { background-color: #dc3545; color: white; }
        .open { background-color: #ffc107; color: white; }
        .close { background-color: #6c757d; color: white; }
        .button:hover { transform: scale(1.1); }

        /* LED INTERACTIVE */
        .led {
            width: 40px;
            height: 40px;
            border-radius: 50%;
            margin: 20px auto;
            background-color: grey;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
            transition: background-color 0.3s, box-shadow 0.3s;
        }
        .led.on { background-color: yellow; box-shadow: 0px 0px 20px yellow; }

        /* PORTE INTERACTIVE */
        .door-container {
            width: 100px;
            height: 150px;
            border: 4px solid black;
            position: relative;
            margin: 20px auto;
            overflow: hidden;
        }
        .door {
            width: 100%;
            height: 100%;
            background-color: brown;
            position: absolute;
            left: 0;
            transition: transform 1s;
        }
        .door.open { transform: translateX(100%); }
    </style>

    <script>
        function toggleLED(state) {
            fetch("/" + state)
            .then(response => response.text())
            .then(data => {
                document.getElementById("led-status").innerText = data;
                let led = document.getElementById("led-indicator");
                led.classList.toggle("on", state === "on");
            });
        }

        function toggleDoor(state) {
            fetch("/door/" + state)
            .then(response => response.text())
            .then(data => {
                document.getElementById("door-status").innerText = data;
                let door = document.getElementById("door");
                door.classList.toggle("open", state === "open");
            });
        }

        function logout() {
            localStorage.removeItem("esp32_auth");
            window.location.href = "/";
        }
    </script>
</head>
<body>
    <div class="container">
        <h1>💡 Light Control</h1>
        <div class="led" id="led-indicator"></div>
        <p class="status">LED is <span id="led-status">OFF</span></p>
        <button class="button on" onclick="toggleLED('on')">Turn ON</button>
        <button class="button off" onclick="toggleLED('off')">Turn OFF</button>

        <h1>🚪 Door Control</h1>
        <div class="door-container">
            <div class="door" id="door"></div>
        </div>
        <p class="status">Door is <span id="door-status">CLOSED</span></p>
        <button class="button open" onclick="toggleDoor('open')">OPEN</button>
        <button class="button close" onclick="toggleDoor('close')">CLOSE</button>
        <br><br>
        <button class="button close" onclick="logout()">🔒 Déconnexion</button>
    </div>
</body>
</html>
)rawliteral";

// Gestion des requêtes de connexion
void handleLogin() {
    if (server.hasArg("user") && server.hasArg("pass")) {
        String user = server.arg("user");
        String pass = server.arg("pass");

        if (user == validUser && pass == validPass) {
            server.send(200, "text/plain", "SUCCESS");
        } else {
            server.send(401, "text/plain", "ERROR");
        }
    } else {
        server.send(400, "text/plain", "Missing parameters");
    }
}

// Gestion de la page principale
void handleRoot() {
    server.send(200, "text/html", login_page);
}

// Gestion de la page de contrôle
void handleControl() {
    server.send(200, "text/html", control_page);
}

// Gestion de la LED (Correction de l'inversion)
void handleOn() {
    etatLed = false;  // La LED doit être éteinte si elle est "OFF"
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "ÉTEINTE");  // Mise à jour de l'affichage
}

void handleOff() {
    etatLed = true;  // La LED doit être allumée si elle est "ON"
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/plain", "ALLUMÉE");  // Mise à jour de l'affichage
}

// Ajoute ces fonctions et routes à ton main.ino

// Gestion de l'ouverture du relais (serrure)
void handleDoorOpen() {
    ActiveRelay(LOW);  // Active le relais (porte ouverte)
    server.send(200, "text/plain", "OPENED");
}

// Gestion de la fermeture du relais (serrure)
void handleDoorClose() {
    ActiveRelay(HIGH); // Désactive le relais (porte fermée)
    server.send(200, "text/plain", "CLOSED");
}

// Gestion du bouton physique pour le relais (en parallèle)
void handlePhysicalButton(){
    static unsigned long lastDebounceTime = 0;
    static bool lastButtonState = HIGH;

    bool buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
        lastDebounceTime = millis();
        lastButtonState = buttonState;
    }

    if ((millis() - lastDebounceTime) > 50) {  // anti-rebond
        if (buttonState == LOW) {
            ActiveRelay(LOW);  // ouvre
            Serial.println("Button pressed: Door OPEN");
        } else {
            ActiveRelay(HIGH); // ferme
            Serial.println("Button released: Door CLOSED");
        }
    }
}

// Modification dans la fonction setup()
void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display

  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  button.setCountMode(COUNT_FALLING);

  displayDoorClose(); // Default state

  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

   pinMode(LED_PIN, OUTPUT);
   digitalWrite(LED_PIN, LOW);

   pinMode(BUTTON_PIN, INPUT_PULLUP); // bouton physique

   server.on("/", handleRoot);
   server.on("/login", handleLogin);
   server.on("/control", handleControl);
   server.on("/on", handleOn);
   server.on("/off", handleOff);

   // Routes pour contrôle WiFi du relais
   
   server.on("/door/open", handleDoorOpen);
   server.on("/door/close", handleDoorClose);
   SetUpRelay();
   setupEmprinte(); // Initialiser capteur d'empreintes
   server.begin();
}

// Modification dans loop()
void loop() {
    dnsServer.processNextRequest();
    server.handleClient();

  if (CheckEmprinte()) {
    ActiveRelay(LOW); // Ouvre la porte si empreinte reconnue
    delay(5000);      // Ouvre pendant 5 secondes
    ActiveRelay(HIGH);// Referme après
    displayDoorOpen();
  }else {
    displayDoorClose();
  }

    // handlePhysicalButton(); // lecture en continu du bouton physique
}

