/**
 * WebServerESP32.h - Library for creating a web server on ESP32.
 * Created by Christopher Batarlis, February 10, 2021.
 * Released into the public domain.
 * 
 * This library is used to create a web server on an ESP32 board.
 * The server can be used to control an LED connected to the board.
 * The server can be accessed by connecting to the ESP32's Wi-Fi network.
 * The server provides a simple web page with buttons to turn the LED on and off.
 * 
 */

#ifndef WEBSERVERESP32_H
#define WEBSERVERESP32_H

#include <WiFi.h>
#include <WebServer.h>

class WebServerESP32 {
  private:
    WebServer server;
    int ledPin;

  public:
    WebServerESP32(const char* ssid, const char* password, int ledPin);
    void begin();
    void handleClient();
};

#endif  // WEBSERVERESP32_H
