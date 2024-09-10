# Exemplo de uso de OTA (Over-the-Air) no ESP32

Aqui está um exemplo de como usar OTA (Over-the-Air) no ESP32, permitindo o upload de novos firmwares para o ESP32 sem precisar de conexão física via USB, utilizando a rede WiFi.

## Explicação:

### Incluindo Bibliotecas:

- `#include <WiFi.h>`: Biblioteca para gerenciar a conexão WiFi.
- `#include <ArduinoOTA.h>`: Biblioteca que facilita a implementação de OTA no ESP32.

### Configurações WiFi:
- `const char* ssid` e `const char* password`: Defina o nome da rede WiFi (SSID) e a senha para conectar seu ESP32 à internet.

### Conectando ao WiFi:
- `WiFi.begin(ssid, password)`: Inicia a conexão WiFi usando as credenciais definidas.
- O ESP32 tentará se conectar à rede

### Definição do IP fixo:
- `IPAddress local_IP(192, 168, 1, 100)`: Define o endereço IP fixo que você quer usar.
- `IPAddress gateway(192, 168, 1, 1)`: Define o endereço do gateway da sua rede (geralmente o roteador).
- `IPAddress subnet(255, 255, 255, 0)`: Define a máscara de sub-rede.
- `IPAddress primaryDNS(8, 8, 8, 8)` e `IPAddress secondaryDNS(8, 8, 4, 4)`: Definem os endereços de servidores DNS (opcional, mas recomendado).

### Configuração do IP fixo:
- `WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)`: Configura o ESP32 para usar o IP fixo, o gateway, a máscara de sub-rede, e os servidores DNS. Essa função deve ser chamada **antes** de `WiFi.begin()`.

### Exibição do IP no Monitor Serial:
- Quando o ESP32 se conecta ao WiFi, o endereço IP fixo é exibido no monitor serial com a função `WiFi.localIP()`.

### OTA Configurada:
- O código usa `ArduinoOTA` para habilitar o upload de firmware via rede (Over-the-Air), com callbacks para indicar o progresso, erros, e conclusão da atualização no monitor serial.


### Configurações de OTA:
- `ArduinoOTA.setHostname("ESP32_OTA")`: Define o nome que aparecerá na lista de dispositivos OTA disponíveis. Você pode dar um nome único para cada ESP32.

#### Callbacks OTA:
Essas funções são chamadas em diferentes etapas do processo de OTA:
- `onStart()`: Chamado quando a atualização OTA começa.
- `onEnd()`: Chamado quando a atualização OTA termina.
- `onProgress()`: Exibe o progresso da OTA, mostrando a porcentagem de conclusão.
- `onError()`: Exibe uma mensagem de erro se houver falha no processo OTA.

### Inicializando e processando OTA:
- `ArduinoOTA.begin()`: Inicia o serviço OTA, tornando o ESP32 pronto para receber atualizações.
- `ArduinoOTA.handle()`: Mantém o serviço OTA em execução. Ele deve ser chamado regularmente no loop principal para garantir que o ESP32 possa processar as solicitações de OTA.

### Aplicação do loop:
O `loop()` principal mantém o OTA ativo e imprime uma mensagem a cada 2 segundos. Você pode adicionar sua lógica de aplicação aqui.

## Como utilizar OTA:

1. **Carregar o código via USB**: Inicialmente, você precisa carregar este código no ESP32 via USB.

2. **Acessar OTA no Arduino IDE**:
   - Depois que o ESP32 estiver conectado ao WiFi e o serviço OTA estiver ativo, vá para o **Arduino IDE**.
   - Selecione **Ferramentas > Porta** e você verá o nome do seu ESP32 (definido em `ArduinoOTA.setHostname`) aparecer na lista de portas, indicando que o dispositivo está disponível para upload OTA.

3. **Fazer upload OTA**:
   - Selecione o dispositivo OTA e faça o upload do novo firmware como faria normalmente. O ESP32 será atualizado sem precisar de conexão USB.

## Como testar:

1. Carregar o código via USB.
2. Abrir o Monitor Serial para verificar a conexão WiFi e o comportamento do LED.
3. Verificar se o LED embutido pisca a cada 1 segundo (500ms ligado, 500ms desligado).
4. Executar o upload OTA pela IDE Arduino, selecionando a porta OTA.


