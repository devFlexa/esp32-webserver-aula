#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// Esta aula usa uma ESP32 DevKit / ESP32-WROOM.
constexpr char AP_NAME[] = "ESP32-Aula";
constexpr char AP_PASSWORD[] = "AulaESP32"; // Minimo de 8 caracteres.
constexpr uint8_t LED_PIN = 21;

WebServer server(80);
bool ledOn = false;

void sendFile(const char *path, const char *contentType) {
  File file = SPIFFS.open(path, FILE_READ);
  if (!file) {
    server.send(404, "text/plain; charset=utf-8", "Arquivo nao encontrado no SPIFFS. Execute Upload Filesystem Image.");
    return;
  }
  server.streamFile(file, contentType);
  file.close();
}

void sendStatus() {
  server.send(200, "application/json; charset=utf-8",
              ledOn ? "{\"ligado\":true}" : "{\"ligado\":false}");
}

void setLed(bool on) {
  ledOn = on;
  digitalWrite(LED_PIN, on ? HIGH : LOW);
  sendStatus();
}

void setup() {
  Serial.begin(115200);
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  if (!SPIFFS.begin(false)) {
    Serial.println("Erro ao montar SPIFFS. Envie os arquivos da pasta data.");
  }

  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(AP_NAME, AP_PASSWORD)) {
    Serial.println("Falha ao criar a rede Wi-Fi.");
    return;
  }

  server.on("/", HTTP_GET, []() { sendFile("/index.html", "text/html; charset=utf-8"); });
  server.on("/style.css", HTTP_GET, []() { sendFile("/style.css", "text/css; charset=utf-8"); });
  server.on("/app.js", HTTP_GET, []() { sendFile("/app.js", "text/javascript; charset=utf-8"); });
  server.on("/api/status", HTTP_GET, sendStatus);
  server.on("/api/led/on", HTTP_POST, []() { setLed(true); });
  server.on("/api/led/off", HTTP_POST, []() { setLed(false); });
  server.onNotFound([]() { server.send(404, "text/plain; charset=utf-8", "Pagina nao encontrada"); });
  server.begin();

  Serial.println("Servidor iniciado.");
  Serial.print("Rede: ");
  Serial.println(AP_NAME);
  Serial.print("Abra: http://");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  server.handleClient();
}
