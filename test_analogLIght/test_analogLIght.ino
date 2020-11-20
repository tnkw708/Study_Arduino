#define LED_PIN 0043

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i <= 255; i++) {
    analogWrite(LED_PIN, i);
    delay(100);
  }
  for(int i = 0; i <= 255; i++) {
    analogWrite(LED_PIN, 255 - i);
    delay(100);
  }
}
