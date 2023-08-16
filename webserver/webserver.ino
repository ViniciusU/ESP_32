#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Tplink";
const char* password = "camilla15";
const int ledPin = 13;

WebServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);

  // Conexão ao roteador Wi-Fi doméstico
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

  // Definição das rotas do servidor Web
  server.on("/", handleRoot);
  server.on("/ligar", handleLigar);
  server.on("/desligar", handleDesligar);

  server.begin();

  Serial.println("Servidor Web iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><title>Controle do LED</title>";
  html += "<style>";
  html += "body { background-color: #222; color: #fff; font-family: Arial, sans-serif; margin: 0; padding: 0; }";
  html += ".container { max-width: 800px; margin: 50px auto; text-align: center; }";
  html += "h1 { color: #FFD700; }";
  html += "a { display: inline-block; padding: 10px 20px; margin: 10px; background-color: #FFD700; color: #222; text-decoration: none; font-weight: bold; border-radius: 5px; }";
  html += "a:hover { background-color: #222; color: #FFD700; }";
  html += "</style>";
  html += "<script>";
  html += "function redirectToHome() { window.location.href = '/'; }";
  html += "</script>";
  html += "</head>";
  html += "<body>";
  html += "<div class=\"container\">";
  html += "<h1>Controle do LED</h1>";
  html += "<a href=\"/ligar\" onclick=\"redirectToHome()\">Ligar</a>";
  html += "<a href=\"/desligar\" onclick=\"redirectToHome()\">Desligar</a>";
  html += "<p>Endereço IP atribuído: ";
  html += WiFi.localIP().toString();
  html += "</p>";
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLigar() {
  digitalWrite(ledPin, HIGH);
  delay(1000); // Pequeno atraso para indicar que o LED foi ligado
  redirectToHome();
  server.send(200, "text/plain", "LED ligado");
}

void handleDesligar() {
  digitalWrite(ledPin, LOW);
  delay(1000); // Pequeno atraso para indicar que o LED foi desligado
  redirectToHome();
  server.send(200, "text/plain", "LED desligado");
}

void redirectToHome() {
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", ""); // Redireciona para a rota inicial com status 302 (Found/Redirect)
}
