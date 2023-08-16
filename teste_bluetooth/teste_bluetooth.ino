#include "BluetoothSerial.h"
#include <LiquidCrystal.h>

//LiquidCrystal lcd(13, 12, 14, 27, 26, 25);
BluetoothSerial SerialBT;
char cmd;
const int potPin = 34;
int potValue;
void setup() 
{
  //Serial.begin(115200);
  delay(1000);
  SerialBT.begin("ESP32");
  pinMode(13,OUTPUT);
  //lcd.begin(16, 2);
  // Clears The LCD Display
  //lcd.clear();
  //lcd.print("Hello World!");
  //lcd.setCursor(1,1);
  //lcd.print("192");

}

void loop() {
  potValue = analogRead(potPin);
  SerialBT.println(potValue);

  delay(500);
  if(SerialBT.available())
  {
    cmd = SerialBT.read();

  }
  if(cmd =='1')
  {
    digitalWrite(13, HIGH);
  }
  if(cmd == '0')
  {
    digitalWrite(13, LOW);
  }


}
