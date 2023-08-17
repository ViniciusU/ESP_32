#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vinicius";
const char* password = "12345678";
const int adcPin1 = 34;
const int adcPin2 = 35;
const int adcPin3 = 36;
const int adcPin4 = 39;

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
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/getADCValues", HTTP_GET, handleGetADCValues); // Definindo o manipulador para o endpoint /getADCValues
  
  server.begin();
  
  Serial.println("Servidor Web iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><title>Valores do ADC</title>";
  html += "<style>";
  html += "body { background-color: #222; color: #fff; font-family: Arial, sans-serif; margin: 0; padding: 0; }";
  html += ".container { max-width: 800px; margin: 50px auto; text-align: center; }";
  html += "h1 { color: #FFD700; }";
  html += "</style>";
  html += "<script>";
  html += "function updateValues() {";
  html += "var xhr = new XMLHttpRequest();";
  html += "xhr.onreadystatechange = function() {";
  html += "if (xhr.readyState === 4 && xhr.status === 200) {";
  html += "var data = JSON.parse(xhr.responseText);";
  html += "document.getElementById('adcValue1').textContent = 'Valor ADC 1: ' + data.adcValue1;";
  html += "document.getElementById('adcValue2').textContent = 'Valor ADC 2: ' + data.adcValue2;";
  html += "document.getElementById('adcValue3').textContent = 'Valor ADC 3: ' + data.adcValue3;";
  html += "document.getElementById('adcValue4').textContent = 'Valor ADC 4: ' + data.adcValue4;";
  html += "}";
  html += "};";
  html += "xhr.open('GET', '/getADCValues', true);";
  html += "xhr.send();";
  html += "}";
  html += "setInterval(updateValues, 2000);";
  html += "</script>";
  html += "</head>";
  html += "<body>";
  html += "<div class=\"container\">";
  html += "<h1>Valores do ADC</h1>";
  html += "<p id=\"adcValue1\">Valor ADC 1: Loading...</p>";
  html += "<p id=\"adcValue2\">Valor ADC 2: Loading...</p>";
  html += "<p id=\"adcValue3\">Valor ADC 3: Loading...</p>";
  html += "<p id=\"adcValue4\">Valor ADC 4: Loading...</p>";
  html += "<p>Endereço IP atribuído: " + WiFi.localIP().toString() + "</p>";
  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleGetADCValues() {
  int adcValue1 = analogRead(adcPin1);
  int adcValue2 = analogRead(adcPin2);
  int adcValue3 = analogRead(adcPin3);
  int adcValue4 = analogRead(adcPin4);

  String json = "{";
  json += "\"adcValue1\": " + String(adcValue1) + ",";
  json += "\"adcValue2\": " + String(adcValue2) + ",";
  json += "\"adcValue3\": " + String(adcValue3) + ",";
  json += "\"adcValue4\": " + String(adcValue4);
  json += "}";

  server.send(200, "application/json", json);
}
