#include <Wire.h>;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Found I2C Addr 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Not Found 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("Not Found i2c\n");
  else
    Serial.println("Done\n");

  delay(2000);
}
