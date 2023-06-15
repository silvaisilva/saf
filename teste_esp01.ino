#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // Configura os pinos RX (2) e TX (3) para a comunicação com o ESP01

void setup() {
  Serial.begin(9600);         // Inicializa a comunicação serial do Arduino
  espSerial.begin(9600);      // Inicializa a comunicação serial com o ESP01

  delay(1000);                // Aguarda 1 segundo para estabilizar a conexão

  espSerial.println("AT");    // Envia o comando AT para verificar a comunicação com o ESP01
}

void loop() {
  if (espSerial.available()) {
    Serial.write(espSerial.read());  // Exibe os dados recebidos do ESP01 no Monitor Serial do Arduino
  }

  if (Serial.available()) {
    espSerial.write(Serial.read());  // Envia os dados digitados no Monitor Serial do Arduino para o ESP01
  }
}
