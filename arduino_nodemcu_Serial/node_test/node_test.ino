#include <SoftwareSerial.h>
SoftwareSerial mySerial (12,13); //RX TX

unsigned long myMillis = millis();
String arrData [3];

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Welcome Windy");
  // put your setup code here, to run once:

}

void loop() {
  if (millis() - myMillis >= 3000UL)
  {
    myMillis = millis();
    String myData = "";
    while(mySerial.available() > 0){
      myData += char (mySerial.read());
    }
    myData.trim();

    if (myData != "")
    {
      //data format "0#1#2" = array (after parsing)
      int index = 0;
      for (int i = 0; i<myData.length(); i++)
      {
        char delimiter = '#';
        if (myData[i] != delimiter)
          arrData [index] += myData[i];
        else
          index++;
      }
      if (index == 2)
      {
        Serial.println(arrData[0]);
        Serial.println(arrData[1]);
        Serial.println(arrData[2]);
        Serial.println();
      }
      arrData [0] = "";
      arrData [1] = "";
      arrData [2] = "";
    }
    mySerial.println("Ya");
  }
  // put your main code here, to run repeatedly:

}
