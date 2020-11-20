#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "rs500m-da7780-1";
const char *password = "748bbbb6eedf2";

char count = 0;

ESP8266WebServer server(80);

char *msg[] = {"Good morning!","Good afternoon!","Good evening!"};

void handleRoot() {
  char temp[400];

  snprintf(temp, 400,
    "<html>\
      <head>\
        <meta http-equiv='refresh' content='10'/>\
        <title>WifiBrick_Test</title>\
        <style>\
          body { background-color: #ff0000; font-family: Arial, Helvetica, Sans-Serif; Color: #ffffff; }\
        </style>\
      </head>\
      <body>\
        <h1>FROM #305WiFiBrick WebServer!</h1>\
        <h1>Sucess!</h1>\
        <h1>%s</h1>\
      </body>\
    </html>", msg[count % 3]
);
  server.send(200, "text/html", temp);
  count++;
}

void setup(void) {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");  
  }

  Serial.println("");
  Serial.print("SSID=");
  Serial.println(ssid);
  Serial.print("IP=");
  Serial.println(WiFi.localIP());

  if(MDNS.begin("esp8266")){
    Serial.println("MDNS responder started");
  }

server.on("/", handleRoot);
server.begin();
Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
