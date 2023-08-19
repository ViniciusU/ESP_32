#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char cmd;
const int potPin = 34;
int potValue;

//POT 1
int sensorValue1 = 0;        // value read from the pot



void setup()
{
  delay(1000);
  SerialBT.begin("ESP32");
  pinMode(13,OUTPUT);
  
}

void loop()
{
  //  Analogico Pot1
  sensorValue1  = analogRead(potPin);

  SerialBT.println(sensorValue1);
  SerialBT.println("/");
 
  delay(200);
}
