#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define APSSID "rs500m-da7780-1"
#define APPASSWORD "748bbbb6eedf2"

 const char *ssid = APSSID;
 const char *password = APPASSWORD;

 ESP8266WebServer server(80);

 void handleRoot() {
  server.send(200, "text/html", "<h1>Hello World</h1>");
 }

void handleLEDon() {
//  digitalWrite(?NUM?, HIGH);
  server.send(200, "text/html", "LED ON");  
}

void handleLEDoff() {
//  digitalWrite(?NUM?, LOW);
  server.send(200, "text/html", "LED OFF");  
}

void setup() {
delay(1000);
Serial.begin(115200);

//pinMode(?NUM?, OUTPUT);

Serial.println("\n\n");
Serial.println("AP Starting \n");

WiFi.softAP(ssid, password);

IPAddress myIP = WiFi.softAPIP();
Serial.println("My IP adress: ");
Serial.println(myIP);
Serial.println("\n");
server.on("/", handleRoot);
server.on("/ledon", handleLEDon);
server.on("/ledoff", handleLEDoff);
server.begin();
}

void loop() {
  server.handleClient();
}
