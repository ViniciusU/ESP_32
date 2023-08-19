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
  SerialBT.print("O valor do potenciometro é: ");
  SerialBT.print(potValue);
  SerialBT.println();
  delay(1000);


}
