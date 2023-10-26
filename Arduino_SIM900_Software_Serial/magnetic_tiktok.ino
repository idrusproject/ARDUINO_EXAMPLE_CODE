#include <SoftwareSerial.h>

#define led 2
#define buzzer 3
#define magnetic 13

bool isOpen = false;
bool wasOpen = false;

SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
bool callTrig = 1;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(magnetic, INPUT_PULLUP);

  // Initialize LED and buzzer state
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);

  //Handshaking with SIM900
  mySerial.println("AT");
  updateSerial();
}

void loop() {
  // Read the state of the magnetic sensor
  isOpen = digitalRead(magnetic);

  // Check if the sensor state has changed from closed to open
  if (isOpen && !wasOpen) {
    // Beep the buzzer once
    if (callTrig) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      mySerial.println("ATD+ +628xxxxxxxxxx;");
      updateSerial();
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);
      delay(20000);
      mySerial.println("ATH"); //hang up
      updateSerial();
    } else {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+628xxxxx\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
      updateSerial();
      mySerial.print("PINTU TERBUKA"); //text content
      updateSerial();
      mySerial.write(26);
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);
      updateSerial();
    }

  }

  // Store the current state for the next iteration
  wasOpen = isOpen;
  delay(200);
}

void updateSerial() {
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
      Serial.println("Serial OK");
    }

    delay(100);
  }
}
