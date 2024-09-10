/*
- Exemplo de como usar OTA (Over-the-Air) no ESP32, permitindo o upload de novos firmwares para o
  ESP32 sem precisar de conexão física via USB, utilizando a rede WiFi e com IP Fixo.
- Mensagens de status são enviadas para porta Serial.
  Epaminondas Lage 
  Setembro 2024  
*/


#include <WiFi.h>
#include <ArduinoOTA.h>  // Biblioteca para atualização Over-the-Air (OTA)

// Definições da rede WiFi
const char* ssid = "SEU_SSID";        // Substitua pelo nome da sua rede WiFi
const char* password = "SUA_SENHA";   // Substitua pela senha da sua rede WiFi

// Definições de IP fixo
IPAddress local_IP(192, 168, 1, 100);     // Substitua pelo IP desejado
IPAddress gateway(192, 168, 1, 1);        // Substitua pelo gateway da sua rede
IPAddress subnet(255, 255, 255, 0);       // Máscara de sub-rede
IPAddress primaryDNS(8, 8, 8, 8);         // DNS primário (opcional)
IPAddress secondaryDNS(8, 8, 4, 4);       // DNS secundário (opcional)

// Defina o pino do LED embutido (geralmente é o pino 2 no ESP32)
#define LED_PIN 2

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Inicializando...");

  // Configura o IP fixo antes de conectar ao WiFi
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Falha ao configurar IP fixo");
  }

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
  Serial.print("Endereço IP Fixo: ");
  Serial.println(WiFi.localIP());

  // Configura o LED embutido como saída
  pinMode(LED_PIN, OUTPUT);

  // Configura OTA (Over-the-Air) para atualizar o firmware
  ArduinoOTA.setHostname("ESP32_OTA");  // Define o nome do dispositivo para OTA

  // Função chamada quando o processo de OTA começa
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "atualização de firmware";
    } else { // U_SPIFFS
      type = "atualização de sistema de arquivos";
    }
    Serial.println("Iniciando " + type);
  });

  // Função chamada quando o processo de OTA termina
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA concluída!");
  });

  // Função chamada para exibir o progresso da OTA
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso da OTA: %u%%\r", (progress * 100) / total);
  });

  // Função chamada quando ocorre um erro durante a OTA
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erro[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Erro de autenticação");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Erro ao iniciar");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Erro de conexão");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Erro ao receber dados");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Erro ao finalizar");
    }
  });

  // Inicia o serviço OTA
  ArduinoOTA.begin();
  Serial.println("Pronto para OTA com IP fixo!");
}

void loop() {
  // Mantém o serviço OTA ativo
  ArduinoOTA.handle();

  // Pisca o LED embutido
  digitalWrite(LED_PIN, HIGH);  // Liga o LED
  delay(500);                   // Espera 500ms
  digitalWrite(LED_PIN, LOW);   // Desliga o LED
  delay(500);                   // Espera 500ms

  // Exibe a mensagem no monitor serial
  Serial.println("Loop principal executando normalmente...");
}
