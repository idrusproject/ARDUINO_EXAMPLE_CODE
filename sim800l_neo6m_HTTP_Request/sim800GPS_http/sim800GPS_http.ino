#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

//String apn = "redir.tri.co.id";             //APN
String apn = "3gprs";                   //APN
//String apn_u = "";                     //APN-Username
//String apn_p = "";                     //APN-Password
//String url = "http://webhook.site/70ed8292-2bde-40d6-be3a-e372bd526618";  //URL of Server
String url = "http://idrusproject.com/sim800gps_idrusproject/history/updatehistory";

TinyGPSPlus gps;
SoftwareSerial simSerial(2, 3); // 2 = RX, 9 = TX
AltSoftSerial gpsSerial(8, 9); // 8 = RX, 9 = TX

#define led 13

void setup()
{
  Serial.begin(115200);
  Serial.println("SIM800 GPS NEO 6M HTTP Requests Setup");
  simSerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(led, OUTPUT);
  delay(1500);
  while (simSerial.available()) {
    Serial.write(simSerial.read());
  }
  delay(2000);
  gsmConfigGprs();
  digitalWrite(led, 0);
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      gpsInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while (true);
  }
  delay(10000);
}

void gsmHttpPost(float latitude, float longitude, float altitude) {
  Serial.println("----------- HTTP POST -----------");
  //  String postData = "lat=" + String(latitude, 6) + "&lng=" + String(longitude, 6);

  // x-www-form-urlencoded
  String postData = "Latitude=" + String(latitude, 6);
  postData += "&Longitude=" + String(longitude, 6);
  postData += "&Altitude=" + String(altitude);

  //  JSON
  //  String postData = "{";
  //  postData += "\"Latitude\":" + String(latitude, 6);
  //  postData += ",\"Longitude\":" + String(longitude, 6);
  //  postData += ",\"Altitude\":" + String(altitude);
  //  postData += "}";

  gsmConfigGprs();
  int dataSize = postData.length();
  Serial.print("Data size: ");
  Serial.println(dataSize);
  Serial.println(" --- Start GPRS & HTTP --- ");
  Serial.println("1/12");
  gsmATCommand("AT+SAPBR=1,1");
  Serial.println("2/12");
  gsmATCommand("AT+SAPBR=2,1");
  Serial.println("3/12");
  gsmATCommand("AT+HTTPINIT");
  Serial.println("4/12");
  gsmATCommand("AT+HTTPPARA=CID,1");
  Serial.println("5/12");
  gsmATCommand("AT+HTTPPARA=URL," + url);
  Serial.println("6/12");
  gsmATCommand("AT+HTTPPARA=Content-Type,application/x-www-form-urlencoded");
  //  gsmATCommand("AT+HTTPPARA=Content-Type,application/json");
  Serial.println("7/12");
  gsmATCommand("AT+HTTPDATA=" + String(dataSize) + ",5000");
  Serial.println("8/12");
  gsmATCommand(postData);
  Serial.println("9/12");
  gsmATCommand("AT+HTTPACTION=1");
  delay(5000);
  Serial.println("10/12");
  gsmATCommand("AT+HTTPREAD");
  Serial.println("11/12");
  gsmATCommand("AT+HTTPTERM");
  Serial.println("12/12");
  gsmATCommand("AT+SAPBR=0,1");
}

void gsmConfigGprs() {
  Serial.println(" --- CONFIG GPRS --- ");
  //  gsmATCommand("AT+SAPBR=3,1,Contype,GPRS");
  gsmATCommand("AT+SAPBR=3,1,CONTYPE,GPRS");
  gsmATCommand("AT+SAPBR=3,1,APN," + apn);
  //  if (apn_u != "") {
  //    gsmATCommand("AT+SAPBR=3,1,USER," + apn_u);
  //  }
  //  if (apn_p != "") {
  //    gsmATCommand("AT+SAPBR=3,1,PWD," + apn_p);
  //  }
}

void gsmATCommand(String command) {
  Serial.println("Send ->: " + command);
  simSerial.println(command);
  long wtimer = millis();
  while (wtimer + 3000 > millis()) {
    while (simSerial.available()) {
      Serial.write(simSerial.read());
    }
  }
  Serial.println();
}
