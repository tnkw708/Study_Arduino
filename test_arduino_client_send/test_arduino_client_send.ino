#include <ESP8266.h>

#define SSID "rs500m-da7780-1"
#define PASSWORD "748bbbb6eedf2" 
#define HOST_NAME "192.168.1.7"
#define HOST_PORT (4545)

SoftwareSerial mySerial(12, 13);
ESP8266 wifi(mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  delay(10);
  mySerial.begin(9600);
  delay(10);

  if(wifi.setOprToStation()){
    Serial.println("wifi set OK");
  } else {
    Serial.println("wifi set ERROR");
    }

  if(wifi.joinAP(SSID, PASSWORD)) {
    Serial.println(wifi.getLocalIP().c_str());  
  } else {
    Serial.println("wifi getAP fail");
    }

  if(wifi.disableMUX()) {
    Serial.println("OK: Sigle");  
  } else {
    Serial.println("ERROR:Single");
    }
   delay(100);
  }

void loop() {
  char msg[128] = {0};

  strcat(msg, "Hi! from Arduino.");

  if(wifi.createTCP(HOST_NAME, HOST_PORT)){
    Serial.println("OK: TCP");
    wifi.send(msg, strlen(msg));
    wifi.releaseTCP();
  } else {
    Serial.println("fail: TCP");
    }

  while(1) {
      delay(10000);
  }
}
