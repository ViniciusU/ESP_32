
int potValue = 0;
int pot = 36;
void setup()
{
  Serial.begin(115200);

}

void loop() 
{
 delay(500);
 potValue = analogRead(pot);
 Serial.print(potValue);
 Serial.println();
}
