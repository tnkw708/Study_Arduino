#include <SoftwareSerial.h>

SoftwareSerial mySerial(12,13);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(115200);
  delay(10);

  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  mySerial.begin(9600);
  delay(10);
  mySerial.println("AT+GMR");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if(Serial.available()) {
    mySerial.write(Serial.read());
  }
}
