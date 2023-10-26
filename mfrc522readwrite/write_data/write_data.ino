#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();

  // Prepare the key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  Serial.println("System Ready To Use !!! (Write_data)");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent())
    return;

  if (!mfrc522.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("This sample only works with MIFARE Classic cards."));
    return;
  }

  byte sector = 1;
  byte blockAddr = 5;
  String data = "on_idrus";
  
  size_t dataSize = data.length() * sizeof(char);
  Serial.print("Byte size of data: ");
  Serial.println(dataSize);

  byte dataBlock[16];  // The data block size is 16 bytes
  data.getBytes(dataBlock, sizeof(dataBlock));

  // Authenticate using key A
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Delete data to the block first
  byte blankData[16] = {0}; // Blank data to overwrite the block
  status = mfrc522.MIFARE_Write(blockAddr, blankData, sizeof(blankData));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  Serial.println(F("Data deleted successfully."));

  // Write data to the block
  status = mfrc522.MIFARE_Write(blockAddr, dataBlock, sizeof(dataBlock));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.println(F("Data written successfully."));

  // Read data from the block
  byte buffer[18];
  byte bufferSize = sizeof(buffer);
  status = mfrc522.MIFARE_Read(blockAddr, buffer, &bufferSize);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Convert the byte array back to a string
  String readData;
  for (byte i = 0; i < bufferSize; i++) {
    readData += (char)buffer[i];
  }

  Serial.print("Data read from block ");
  Serial.print(blockAddr);
  Serial.print(": ");
  Serial.println(readData);

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
