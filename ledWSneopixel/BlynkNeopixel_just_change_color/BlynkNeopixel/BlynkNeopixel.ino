#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define PIN D2 //pin yang di gunakan di nodemcu
#define NUMPIXELS 150 //jumllah led perbarisnya
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

BLYNK_WRITE(V2){
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);
  for(int i=0;i<NUMPIXELS;i++){
  
  pixels.setPixelColor(i, pixels.Color(R,G,B));
  
  pixels.show();
  }
}

void setup(){
  Serial.begin(9600);
  Blynk.begin("nrUi9R_FDQ7EOogpQ39h2zZMt0r9ffAV", "GoLite Store", "082322631658");
  pixels.begin();
}

void loop(){
  Blynk.run();
}
