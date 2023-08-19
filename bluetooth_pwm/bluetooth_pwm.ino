
#include "BluetoothSerial.h"


BluetoothSerial SerialBT;
char cmd[5]; // Dados Bluetooth

//configuração dos parâmetros do PWM
const int freq = 10000;
const int ledCanal = 0;
const int resolucao = 8;
int valor;

void setup() 
{
  delay(1000);
  SerialBT.begin("ESP32");

  ledcSetup(ledCanal, freq, resolucao);
  // Anexar o canal ao GPIO
  ledcAttachPin(16, ledCanal);

}

void loop() 
{
  
  if(SerialBT.available())
  {
    valor = SerialBT.read();
    //valor = cmd.toInt();
  }
  if(valor > 254)
  {
    ledcWrite(ledCanal, 254);
  }
  else
  {
  ledcWrite(ledCanal, valor);
  
  }
  SerialBT.print(valor); 
  delay(1000);
}
