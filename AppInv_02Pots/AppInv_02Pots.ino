#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char cmd;
const int potPin = 34;
int potValue;

//POT 1
const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue1 = 0;        // value read from the pot
int sensorValue1_old = 0;        // value read from the pot - before
int outputValue1 = 0;        // value output to the PWM (analog out)


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
  SerialBT.println(potPin);
  if ((sensorValue1 > (sensorValue1_old + 20)) || (sensorValue1 < (sensorValue1_old - 20 )))
  { sensorValue1_old = sensorValue1;
  }


  SerialBT.println(sensorValue1);
  SerialBT.println("/");
 
  delay(200);
}
