#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Pinos de comunicação com o Arduino
#define ARDUINO_RX 3
#define ARDUINO_TX 1

// Informações da rede Wi-Fi
const char* ssid = "your_ssid";
const char* password = "your_password";

// Endereço do servidor e porta
const char* server = "http://example.com";
int port = 80;

// Inicialização dos objetos
SoftwareSerial arduinoSerial(ARDUINO_RX, ARDUINO_TX);
WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600);

  // Conectar à rede Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado, endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (arduinoSerial.available()) {
    String data = arduinoSerial.readStringUntil('\n');
    Serial.print("Dados recebidos do Arduino: ");
    Serial.println(data);

    // Enviar dados para o servidor
    if (client.connect(server, port)) {
      String url = "/path/to/your/endpoint?" + data;
      http.begin(client, server, port, url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("Código de resposta HTTP: %d\n", httpCode);
      } else {
        Serial.printf("Falha na requisição, erro: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.println("Falha na conexão com o servidor");
    }
  }
}
