#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char cmd;
const int potPin = 34;
int potValue;


void setup() 
{
  SerialBT.begin("ESP32");

}

void loop() 
{
  potValue = analogRead(potPin);
  SerialBT.println("O valor do potenciometro é: ");
  SerialBT.print(potValue);
  delay(1000);


}
