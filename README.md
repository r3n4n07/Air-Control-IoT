# AirControlIoT

## Descrição

AirControlIoT é um projeto de dispositivo IoT (Internet das Coisas) que lê a temperatura e a umidade do ar usando um sensor DHT11. Os dados capturados são exibidos em um display OLED e enviados para o Firebase em tempo real. O dispositivo se conecta a uma rede Wi-Fi para enviar os dados coletados.

## Funcionalidades

- **Monitoramento de Temperatura e Umidade:** O dispositivo lê continuamente a temperatura e a umidade do ambiente.
- **Exibição em Display OLED:** Os dados são exibidos em um display OLED de forma clara e legível.
- **Upload para Firebase:** Os dados são enviados para o Firebase, onde podem ser acessados e analisados remotamente.
- **Configuração Dinâmica de Wi-Fi:** O dispositivo pode obter as credenciais de Wi-Fi do Firebase para se conectar automaticamente à rede preferida.

## Componentes Utilizados

- **Hardware:**
  - ESP8266 (NodeMCU)
  - Sensor de temperatura e umidade DHT11
  - Display OLED (Adafruit SSD1306)

- **Software:**
  - Arduino IDE
  - Bibliotecas: `ArduinoJson`, `ESP8266Firebase`, `ESP8266WiFi`, `DHT`, `Adafruit_SSD1306`

## Pré-requisitos

- Arduino IDE instalado
- Bibliotecas Arduino necessárias instaladas:
  - `ArduinoJson`
  - `ESP8266Firebase`
  - `ESP8266WiFi`
  - `DHT`
  - `Adafruit_SSD1306`
