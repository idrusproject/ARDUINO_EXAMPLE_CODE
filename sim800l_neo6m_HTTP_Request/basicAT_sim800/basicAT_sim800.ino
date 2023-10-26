// https://lastminuteengineers.com/sim800l-gsm-module-arduino-tutorial/
// Change baud : AT+IPR=4800
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
unsigned long myTimes ;

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  delay(3000);
  Serial.println("Initializing...");
  delay(2000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

  Serial.println("Setup done");
}

void loop()
{
  //  if (millis() - myTimes > 10000UL) {
  //    Serial.println("Testing");
  //    mySerial.println("ATD+ +62895384968833;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  //    updateSerial();
  //    delay(30000); // wait for 20 seconds...
  //    mySerial.println("ATH"); //hang up
  //    //    char postData[] = "field1=value1&field2=value2"; // Replace with the data you want to send
  //    //    sendPostRequest(postData);                      // Call the function to send the POST request
  //    updateSerial();
  //    myTimes = millis();
  //  }
  updateSerial();
}

//void sendPostRequest(const char *data)
//{
//  // Set the APN for Tri Indonesia
//  mySerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
//  updateSerial();
//  delay(5000);
//  mySerial.println("AT+SAPBR=3,1,\"APN\",\"redir.tri.co.id\""); // Replace "3gprs" with the correct APN if needed
//  updateSerial();
//  delay(5000);
//
//  mySerial.println("AT+SAPBR=1,1"); // Enable GPRS
//  updateSerial();
//  delay(5000);
//  mySerial.println("AT+SAPBR=2,1"); // Enable GPRS
//  updateSerial();
//  delay(5000);
//
//  mySerial.println("AT+HTTPINIT"); // Initialize HTTP service
//  updateSerial();
//
//  mySerial.println("AT+HTTPPARA=\"CID\",1"); // Set the CID (Connection ID) to 1
//  updateSerial();
//
//  mySerial.print("AT+HTTPPARA=\"URL\",\"https://webhook.site/26111565-0bbf-4a67-ac54-078660b008ac\""); // Replace with your server URL
//  updateSerial();
//
//  mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\""); // Set content type
//  updateSerial();
//
//  int dataLength = strlen(data);
//  mySerial.print("AT+HTTPDATA=");
//  mySerial.print(dataLength);
//  mySerial.print(",10000"); // Increase the timeout value if needed
//  mySerial.println();
//  delay(100);
//  mySerial.print(data);
//  delay(500);
//  updateSerial();
//
//  mySerial.println("AT+HTTPACTION=1"); // Method 1: POST
//  updateSerial();
//  delay(10000);
//
//  mySerial.println("AT+HTTPTERM"); // Terminate HTTP service
//  updateSerial();
//}

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
