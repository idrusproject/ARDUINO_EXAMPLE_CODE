#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int outputValue=0;
int rememberOutputValue;
int randNumber;
int counter = 0;
int loopCounter = 0;

#define PIN            10
#define NUMPIXELS      40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  randomSeed(analogRead(A1));
  Serial.begin(9600);
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


void loop() {
  // put your main code here, to run repeatedly

    // read the analog in value 100 times and count high levels
   int sensorValue; 
   counter = 0;
   
   for (int i=0; i < 100; i++){
    sensorValue = analogRead(A1);
    if(sensorValue > 500) counter++;
   }
  
  
  if(map(counter, 0, 60, 0, 60) > outputValue)outputValue = map(counter, 0, 40, 0, 60);
  else if(loopCounter %2 == 0)outputValue-=1;
  
  if(outputValue < 0) outputValue = 0;
  if(outputValue > 24) outputValue = 24;

 
  if(loopCounter % 60 == 0)randNumber = random(255);
  loopCounter++;

  // clear all LEDs
 for(int i=0;i < NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0, 255)); 
    
  }

 if(rememberOutputValue != outputValue){    
  for(int i=24;i > (24-outputValue) || (outputValue == 24 && i == 0);i--){
  pixels.setPixelColor(i, Wheel((randNumber) & 255));
 }
  
   pixels.show(); // This sends the updated pixel color to the hardware
}   
   rememberOutputValue = outputValue;
}
