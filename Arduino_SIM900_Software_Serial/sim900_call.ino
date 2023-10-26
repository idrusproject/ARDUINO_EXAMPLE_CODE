#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
unsigned long myTimes ;

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();

}

void loop()
{
  if (millis() - myTimes >= 5000UL) {
    Serial.println("Calling !!!!");
    mySerial.println("ATD+ +6281377195681;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    delay(70000); // wait 
    Serial.println("Hang Up !!!!");
    mySerial.println("ATH"); //hang up
    myTimes = millis();
  }

}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
