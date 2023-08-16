const int BOTAO = 15;
const int LED = 13;

void setup() 
{
 pinMode(BOTAO, INPUT);
 pinMode(LED, OUTPUT);
 digitalWrite(LED,0);
}

void loop() 
{

 if(!digitalRead(BOTAO))
 {
   digitalWrite(LED,1);
 }
 else
 {
   digitalWrite(LED,0);
 } 

}
