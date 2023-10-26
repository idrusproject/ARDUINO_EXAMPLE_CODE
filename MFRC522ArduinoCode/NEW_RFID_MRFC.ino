#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #define SS_PIN 10
// #define RST_PIN 9
#define lock 2
#define buzz 4
#define SS_PIN 21
#define RST_PIN 22

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);
int out = 0;
bool trig = false;
String card1 = "04 38 80 62 68 5A 80";

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Serial.println("Start");
  pinMode(lock, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  digitalWrite(lock, 1);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Program ready to use");
}

void loop()
{
  String content = "";
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      trig = true;
      // Show UID on serial monitor
      Serial.println();
      Serial.print(" UID tag :");

      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
    }
    delay(100);
  }

  content.toUpperCase();
  // Serial.println(content);
  if (content.substring(1) == card1)
  {
    // your code here
    Serial.println("Welcome Boss");
    digitalWrite(4, 1);
    delay(100);
    digitalWrite(4, 0);
    delay(100);
    digitalWrite(4, 1);
    delay(100);
    digitalWrite(4, 0);
    trig = false;
    lcd.setCursor(0, 0);
    lcd.print(content.substring(1));
    digitalWrite(lock, 0);
    delay(1500);
    digitalWrite(lock, 1);
    lcd.clear();
  }
  else
  {
    if (trig)
    {
      Serial.println(" Access Denied ");
      lcd.setCursor(0, 0);
      lcd.print(content.substring(1));
      digitalWrite(4, 1);
      delay(3000);
      digitalWrite(4, 0);
      lcd.clear();
      trig = false;
    }
  }

  // Serial.println("end loop");
  delay(50);
}
