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
    Serial.println("Ok:multi");
    } else {
      Serial.println("ERROR:Multi");
      }

  if(wifi.startTCPServer(SERVER_PORT)){
    Serial.println("OK: Server");
  } else {
    Serial.println("ERROR: Server");
    }

  if(wifi.setTCPServerTimeout(10)){
    Serial.println("OK: Timeout");  
  } else {
    Serial.println("EEROR: Timeout");
    }
  Serial.println("Server stand now!");
  delay(100);
}

void loop() {
  char buffer[128] = {0};
  uint8_t mux_id;
  int len, i;

  len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
  if(len > 0) {
    Serial.println("Ok:Connect");
  
    for(i = 0; i <len; i++) {
      Serial.print((char)buffer[i]); 
    }
    
    Serial.println("");
  
    if(wifi.releaseTCP(mux_id)){
    Serial.println("OK:Release TCP");  
    }
  }
}
