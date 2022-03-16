#include <ESP8266WebServer.h>

ESP8266WebServer server(80);


void handleHomePage() {
  char body[1024];
  sprintf(body, "<!DOCTYPE html> <html> <body> <h1>My First Heading</h1> <p>My first paragraph.</p> </body> </html>");
  server.send(200, "text/html", body);
}

void handleLedOff() {
  Serial.println("LED OFF");
  char body[1024];
  sprintf(body, "<!DOCTYPE html> <html> <body> <h1>LED</h1> <p>OFF</p> </body> </html>");
  digitalWrite(LED_BUILTIN, HIGH);

  server.send(200, "text/html", body);
}

void handleLedOn() {
  Serial.println("LED ON");
  char body[1024];
  sprintf(body, "<!DOCTYPE html> <html> <body> <h1>LED</h1> <p>ON</p> </body> </html>");
  digitalWrite(LED_BUILTIN, LOW);

  server.send(200, "text/html", body);
}

void callJavaScript() {
  char body[1024];
  sprintf(body, "<!DOCTYPE html><html>   <head>      <title>Javascript External Script</title>      <script src = \"/html/script.js\" type = \"text/javascript\"/></script>   </head>   <body>      <input type = \"button\" onclick = \"Hello();\" name = \"ok\" value = \"Click Me\" />   </body></html>");
  server.send(200, "text/html", body);
}

void startWebServer() {
  pinMode(LED_BUILTIN, OUTPUT);

  server.on("/", handleHomePage);
  server.on("/led/off", handleLedOff);
  server.on("/led/on", handleLedOn);
  server.on("/js", callJavaScript);

  server.begin();
}