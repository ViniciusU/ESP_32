#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Tplink";
const char* password = "12345678";
const int adcPin1 = 34;  // ADC pin for value 1
const int adcPin2 = 35;  // ADC pin for value 2
const int adcPin3 = 36;  // ADC pin for value 3
const int adcPin4 = 39;  // ADC pin for value 4

WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println();
  Serial.print("Conectado à rede Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("Endereço IP atribuído: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  
  Serial.println("Servidor Web iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  int adcValue1 = analogRead(adcPin1);
  int adcValue2 = analogRead(adcPin2);
  int adcValue3 = analogRead(adcPin3);
  int adcValue4 = analogRead(adcPin4);

  String html = "<!DOCTYPE html><html>";
  html += "<head><title>Valores do ADC</title>";
  html += "<style>";
  html += "body { background-color: #222; color: #fff; font-family: Arial, sans-serif; margin: 0; padding: 0; }";
  html += ".container { max-width: 800px; margin: 50px auto; text-align: center; }";
  html += "h1 { color: #FFD700; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<div class=\"container\">";
  html += "<h1>Valores do ADC</h1>";
  html += "<p>Valor ADC 1: " + String(adcValue1) + "</p>";
  html += "<p>Valor ADC 2: " + String(adcValue2) + "</p>";
  html += "<p>Valor ADC 3: " + String(adcValue3) + "</p>";
  html += "<p>Valor ADC 4: " + String(adcValue4) + "</p>";
  html += "<p>Endereço IP atribuído: " + WiFi.localIP().toString() + "</p>";
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
