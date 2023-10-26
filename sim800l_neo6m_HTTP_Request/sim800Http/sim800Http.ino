//More information at: https://www.aeq-web.com/

#include <SoftwareSerial.h>

//String apn = "redir.tri.co.id";             //APN
String apn = "3gprs";                   //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
//String url = "http://webhook.site/26111565-0bbf-4a67-ac54-078660b008ac";  //URL of Server
String url = "http://idrusproject.com/sim800gps_idrusproject/history/updatehistory";

SoftwareSerial SWserial(2, 3); // RX, TX

void setup()
{
  Serial.begin(115200);
  Serial.println("SIM800 AT CMD Test");
  SWserial.begin(9600);
  delay(1500);
  while (SWserial.available()) {
    Serial.write(SWserial.read());
  }
  delay(2000);
  gsm_config_gprs();
}

void loop() {
  gsm_http_post("param=TestFromMySim800");
  delay(10000);
}

void gsm_http_post( String postdata) {
  Serial.println("----------- HTTP POST -----------");
  //  String testData = "{";
  //  testData += "\"Latitude\":" + String(24, 6);
  //  testData += ",\"Longitude\":" + String(24, 6);
  //  testData += ",\"Altitude\":" + String(24);
  //  testData += "}";
  gsm_config_gprs();
  int dataSize = postdata.length();
  Serial.print("Data size: ");
  Serial.println(dataSize);
  Serial.println(" --- Start GPRS & HTTP --- ");
  gsm_send_serial("AT+SAPBR=1,1");
  //  delay(1000);
  gsm_send_serial("AT+SAPBR=2,1");
  //  delay(1000);
  gsm_send_serial("AT+HTTPINIT");
  //  delay(1000);
  gsm_send_serial("AT+HTTPPARA=CID,1");
  //  delay(1000);
  gsm_send_serial("AT+HTTPPARA=URL," + url);
  //  delay(1000);
  gsm_send_serial("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  //  delay(1000);
  gsm_send_serial("AT+HTTPDATA=" + String(dataSize) + ",5000");
  //  delay(1000);
  //  gsm_send_serial(testData);
  gsm_send_serial(postdata);
  //  delay(1000);
  gsm_send_serial("AT+HTTPACTION=1");
  delay(3000);
  gsm_send_serial("AT+HTTPREAD");
  //  delay(1000);
  gsm_send_serial("AT+HTTPTERM");
  //  delay(1000);
  gsm_send_serial("AT+SAPBR=0,1");
}

void gsm_config_gprs() {
  Serial.println(" --- CONFIG GPRS --- ");
  //  gsm_send_serial("AT+SAPBR=3,1,Contype,GPRS");
  gsm_send_serial("AT+SAPBR=3,1,CONTYPE,GPRS");
  gsm_send_serial("AT+SAPBR=3,1,APN," + apn);
  if (apn_u != "") {
    gsm_send_serial("AT+SAPBR=3,1,USER," + apn_u);
  }
  if (apn_p != "") {
    gsm_send_serial("AT+SAPBR=3,1,PWD," + apn_p);
  }
}

void gsm_send_serial(String command) {
  Serial.println("Send ->: " + command);
  SWserial.println(command);
  long wtimer = millis();
  while (wtimer + 3000 > millis()) {
    while (SWserial.available()) {
      Serial.write(SWserial.read());
    }
  }
  Serial.println();
}
