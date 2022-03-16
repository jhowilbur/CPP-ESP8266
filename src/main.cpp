#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WebSocket.h"
#include "WebServer.h"

#define DEBUG true

void callWebSocket() {
  // createWifiToConnections();
  webSocketServer();
}



void setup() {
  connectWiFi();
  delay(5000);
  // createWifiToConnections();

  // callWebSocket();
  startWebServer();
}

void loop() {
    // webSocket.loop();
    server.handleClient();
}  