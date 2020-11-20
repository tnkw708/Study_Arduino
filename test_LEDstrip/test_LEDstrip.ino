#include <Adafruit_NeoPixel.h>

#define LED_PIN 3

int numPixels = 300;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixels, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(128, 0, 0));
  }
  
  pixels.show();
  delay(500);
  
  for(i = 0; i < pixels.numPixels(); i++) {
  pixels.setPixelColor(i, pixels.Color(0, 128, 0));
  }

  pixels.show();
  delay(500);

  for(i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(0 ,0, 128));
  }

  pixels.show();
  delay(500);

}
