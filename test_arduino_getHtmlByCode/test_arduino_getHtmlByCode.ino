#include <ESP8266.h>

#define SSID "rs500m-da7780-1"
#define PASSWORD "748bbbb6eedf2"
#define HOST_NAME "52.68.96.58"
#define HOST_PORT (80)
#define FILE_NAME "http://52.68.96.58/"

SoftwareSerial mySerial(12, 13);
ESP8266 wifi(mySerial);

void setup() {
  Serial.begin(9600);
  
  mySerial.begin(115200);
  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  delay(10);
  mySerial.begin(9600);
  delay(10);

  if(wifi.setOprToStation()) {
    Serial.println("wifi set OK!");
  } else {
    Serial.println("wifi set ERROR!");
    }

  if(wifi.joinAP(SSID,PASSWORD)) {
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.println("wifi getIP fail");
    }

  if(wifi.disableMUX()) {
    Serial.println("OK: Single");  
  } else {
    Serial.println("ERROR:Single");
    }
  delay(100);


//webページの取得を１度行う
    char buffer[1000] = {0};
  int i;

  strcat(buffer, "GET ");
  strcat(buffer, FILE_NAME);
  strcat(buffer, " HTTP/1.1\r\nHOST: ");
  strcat(buffer, HOST_NAME);
  strcat(buffer, "\r\nConnection: close\r\n\r\n");

  wifi.createTCP(HOST_NAME, HOST_PORT);
  wifi.send(buffer, strlen(buffer));
  delay(100);

  wifi.recv(buffer, sizeof(buffer), 100000);
  for(i = 0; i < sizeof(buffer); i++) {
    Serial.print((char)buffer[i]);
  }
  delay(60000);
}

void loop() {
  /*
  char buffer[1000] = {0};
  int i;

  strcat(buffer, "GET ");
  strcat(buffer, FILE_NAME);
  strcat(buffer, " HTTP/1.1\r\nHOST: ");
  strcat(buffer, HOST_NAME);
  strcat(buffer, "\r\nConnection: close\r\n\r\n");

  wifi.createTCP(HOST_NAME, HOST_PORT);
  wifi.send(buffer, strlen(buffer));
  delay(100);

  wifi.recv(buffer, sizeof(buffer), 100000);
  for(i = 0; i < sizeof(buffer); i++) {
    Serial.print((char)buffer[i]);
  }
  delay(60000);
  */
}
