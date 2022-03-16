#include <Arduino.h>
#include <WebSocketsServer.h>
#include <ESP8266WiFi.h>


#define USE_SERIAL Serial1
WebSocketsServer webSocket = WebSocketsServer(81); // Recebe dados do cliente

void connectWiFi() {
  Serial.begin(9600);
  Serial.begin(115200);

  WiFi.begin("VIRUS_omicron", "EsmolA00");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}


const char *ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "thereisnospoon";   // The password required to connect to it, leave blank for an open network
void createWifiToConnections() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}


// Tratamento de eventos dos dados que vêm do cliente 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  switch(type) {
    case WStype_DISCONNECTED:
      USE_SERIAL.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED: { 
        IPAddress ip = webSocket.remoteIP(num);
        Serial.println(ip);
        webSocket.sendTXT(num, "Connected"); // send message to client
      }
      break;

    case WStype_TEXT: { 
        String text = String((char *) &payload[0]);
        Serial.println(text);
        Serial.println(num);
        Serial.println(type);
      }
      break;
  }
}

void webSocketServer() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}