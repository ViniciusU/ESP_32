const int ledPino = 16;  // 16 corresponde ao GPIO16

//configuração dos parâmetros do PWM
const int freq = 10000;
const int ledCanal = 0;
const int resolucao = 8;
 
void setup(){
  // configura o PWM através dos parâmetros
  ledcSetup(ledCanal, freq, resolucao);
  
  // Anexar o canal ao GPIO
  ledcAttachPin(ledPino, ledCanal);
  ledcWrite(ledCanal, 25);   
   delay(15);
  }
}
