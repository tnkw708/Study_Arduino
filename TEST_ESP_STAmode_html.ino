#include <WiFi.h>
#include <WebServer.h>

 //ステーションモード設定
#define SSID "led_wifi"
#define PASSWORD "00000000" 
const char *ssid = SSID;
const char *password = PASSWORD;

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello World</h1>");  
}


void handleLEDon() {
//  digitalWrite(?NUM?, HIGH);
  Serial.println("LED ON");
  server.send(200, "text/html", "LED ON");  
}

void handleLEDoff() {
//  digitalWrite(?NUM?, LOW);
  Serial.println("LED OFF");
  server.send(200, "text/html", "LED OFF");  
}

void setup() {
  delay(1000);
  Serial.begin(115200);

//   pinMode(?NUM?, OUTPUT);
Serial.print("\n\n");

// WiFiステーションモード
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

while(WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

Serial.println("");
Serial.print("Connecred to ");
Serial.println(ssid);
Serial.print("IP address");
Serial.println(WiFi.localIP());

server.on("/", handleRoot);
server.on("/ledon", handleLEDon);
server.on("/ledoff", handleLEDoff);
server.begin();
}

void loop() {
  server.handleClient();
}