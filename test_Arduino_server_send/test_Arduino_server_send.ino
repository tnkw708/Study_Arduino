#include <ESP8266.h>

#define SSID "rs500m-da7780-1"
#define PASSWORD "748bbbb6eedf2"
#define SERVER_PORT (9999)

SoftwareSerial mySerial(12, 13);
ESP8266 wifi(mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
  mySerial.println("AT+UART_CUR=9600, 8, 1, 0, 0");
  delay(10);
  mySerial.begin(9600);
  delay(10);

  if(wifi.setOprToStation()) {
    Serial.println("wifi set Ok");  
  } else {
    Serial.println("wifi set fail");
    }

  if(wifi.joinAP(SSID, PASSWORD)) {
    Serial.println(wifi.getLocalIP().c_str());  
  }  else {
    Serial.println("ERROR:single");
    }
  delay(100);

  if(wifi.enableMUX()) {
    Serial.println("OK:Multi");  
  } else {
    Serial.println("ERROR:Multi");
    }

  if(wifi.startTCPServer(SERVER_PORT)){
    Serial.println("OK: Set TCP");  
  } else {
    Serial.println("ERROR:Set TCP");
    }

  if(wifi.setTCPServerTimeout(10)){
    Serial.println("OK: Set timeout");
  } else {
    Serial.println("ERROR: Set timeout");
    }

  Serial.println("Server stand_by now");
  delay(100);
}

void loop() {
  char buffer[64] = {0};
  char msg[128] = {0};
  uint8_t mux_id;
  int len, i;

  len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
  if(len > 0){
    Serial.println("Connect!");

    strcat(msg, "good evening! from Arduino");

    if(wifi.send(mux_id, msg, sizeof(msg))){
      Serial.println("OK: Send data");
    } else {
      Serial.println("ERROR: Send data");
      }
    if(wifi.releaseTCP(mux_id)) {
      Serial.println("OK: Release Connect");
    } 
  }
}
