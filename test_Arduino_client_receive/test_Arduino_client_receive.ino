#include <ESP8266.h>

#define SSID "rs500m-da7780-1"
#define PASSWORD "748bbbb6eedf2" 
#define HOST_NAME "192.168.1.7"
#define HOST_PORT (1919)

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
    Serial.println("wifi set fail");
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
  int i;

  if(wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.println("OK: TCP");

    wifi.recv(msg, sizeof(msg), 10000);
    for(i = 0; i < sizeof(msg); i++) {
      Serial.print((char) msg[i]);
    }

    wifi.releaseTCP();
    
    } else {
      Serial.println("Fail: TCP");
      } 

  while(1) {
    delay(10000);  
  }
}
