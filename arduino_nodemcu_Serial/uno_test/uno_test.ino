int a = 10;
int b = 15;
int c = 24;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome UNO Windy ");
  // put your setup code here, to run once:

}

void loop() 
{
  String ask = "";
  while (Serial.available()>0)
  {
    ask += char(Serial.read());
  }
  ask.trim();
  if(ask == "Ya")
  {
    sendData();
  }
  ask = "";
  a++;
  b++;
  c++;
  delay(1000);
  // put your main code here, to run repeatedly:

}

void sendData ()
{
  // toNode = "0#1#2"
  String toNode = String (a) + "#" + String (b) + "#" + String (c);
  Serial.println(toNode);  
}
