#include "BluetoothSerial.h"


BluetoothSerial SerialBT;
char cmd;
const int led = 2;


void setup() 
{
  delay(1000);
  SerialBT.begin("ESP32");
  pinMode(led, OUTPUT);


}

void loop() 
{
  delay(500);
  if(SerialBT.available())
  {
    cmd = SerialBT.read();

  }
  if(cmd =='1')
  {
    digitalWrite(led, HIGH);
    SerialBT.println("Led ligado");
  }
  if(cmd == '0')
  {
    digitalWrite(led, LOW);
    SerialBT.println("Led desligado");
  }
}
