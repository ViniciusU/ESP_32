#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
char cmd;
const int potPin = 34;
int ledRed = 18;
int ledGreen = 19;
int ledBlue = 21;
int pwm_pin = 16;

int potValue;
int sensorValue1 = 0;        // value read from the pot


//configuração dos parâmetros do PWM
const int freq = 10000;
const int ledCanal = 0;
const int resolucao = 8;


void setup()
{
  delay(1000);
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledBlue,OUTPUT);
   // configura o PWM através dos parâmetros
  ledcSetup(ledCanal, freq, resolucao);
  // Anexar o canal ao GPIO
  ledcAttachPin(pwm_pin, ledCanal);
 
  
}

void loop()
{
  //  Analogico Pot1
  sensorValue1  = analogRead(potPin);
  sensorValue1 = (5*sensorValue1/(0.01*4096));
  SerialBT.println(sensorValue1);
  SerialBT.println("/");

  int valor = SerialBT.read();

   if (SerialBT.available())
  {
    valor = SerialBT.read();
    Serial.println(valor);

  }
  if (valor == 245) digitalWrite(ledRed, HIGH);
    if (valor == 246) digitalWrite(ledRed, LOW);
    if (valor == 247) digitalWrite(ledGreen, HIGH);
    if (valor == 248) digitalWrite(ledGreen, LOW);
    if (valor == 249) digitalWrite(ledBlue, HIGH);
    if (valor == 250) digitalWrite(ledBlue, LOW);
    if ((valor >= 0) && (valor < 240))
    {
       ledcWrite(ledCanal, valor);
    
    
    }


 
  delay(200);
}
