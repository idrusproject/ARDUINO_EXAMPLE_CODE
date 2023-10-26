#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define btn_1 2
#define btn_2 3
#define btn_3 4

LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  Serial.println("Initializing...");
  delay(1000);
  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP);
  pinMode(btn_3, INPUT_PULLUP);
  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();
  lcd.setCursor(0, 1);
  lcd.print("Done...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready To Use.");
}

void loop()
{
  if (digitalRead(btn_1) == 0) {
    while (digitalRead(btn_1) == 0) {
      delay(100);
    }
    lcd.setCursor(0, 1);
    lcd.print("Menelvon !!!          ");
    Serial.println("Calling !!!!");
    mySerial.println("ATD+ +62895384968833;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    updateSerial();
  }
  if (digitalRead(btn_2) == 0) {
    while (digitalRead(btn_2) == 0) {
      delay(100);
    }
    lcd.setCursor(0, 1);
    lcd.print("Mematikan !!!          ");
    Serial.println("Hang Up !!!!");
    mySerial.println("ATH"); //hang up
    updateSerial();
  }
  if (digitalRead(btn_3) == 0) {
    while (digitalRead(btn_3) == 0) {
      delay(100);
    }
    Serial.println("Texting !!!!");
    lcd.setCursor(0, 1);
    lcd.print("Kirim SMS !!!          ");
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+62895384968833\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print("Pesan Dari GoLite Store Bandung"); //text content
    updateSerial();
    mySerial.write(26);
  }
  updateSerial();
  delay(100);
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
    String myString = mySerial.readString();
    Serial.print("SIM900 Data : ");
    Serial.println(myString);//Forward what Software Serial received to Serial Port
    if (myString == "OK") {
      lcd.setCursor(0, 3);
      lcd.print("MSG:");
      lcd.print(myString);
      Serial.println("Serial OK");
    }
    
    delay(100);
  }
}
