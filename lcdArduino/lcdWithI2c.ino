#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26, 16, 2);
// LiquidCrystal_I2C lcd1 (0x26, 16, 2);

void setup()
{
  Wire.begin();
  lcd.begin();
  //  lcd1.begin();
  lcd.setCursor(0, 0);
  lcd.print("GoLite Store");
  lcd.setCursor(0, 1);
  lcd.print("goli testore.id");
  delay(100);
  Serial.begin(9600);
  Serial.println("Start");
}
// untuk menghapus gunakan lcd.clear();
void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("GoLite Store");
  lcd.setCursor(0, 1);
  lcd.print("Cust : Fajar");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("  Mohamad Idrus");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("   EID MUBARAK   ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("Idul Fitri 1441H");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("   Mohon Maaf     ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print(" Lahir dan Batin");
  delay(2000);

  //  lcd1.setCursor (0, 0);
  //  lcd1.print("Dila Silvi");
  //  delay (1000);
  //  lcd1.setCursor (0, 1);
  //  lcd1.print("26 mei");
  //  delay(500);
}
