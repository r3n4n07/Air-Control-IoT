// --- JSON ---
#include <ArduinoJson.h>

// --- Firabase ---
#include <ESP8266Firebase.h>
#define REFERENCE_URL "https://aircontrol-a5abb-default-rtdb.firebaseio.com/"
Firebase firebase(REFERENCE_URL);

// --- WIFI ---
#include <ESP8266WiFi.h>
String ssid = "Default";       // troque pelo nome da sua rede
String password = "12345678";   // troque pela senha da sua rede
WiFiClient nodemcuClient;

// --- DHT ---
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int umidade;
int temperatura;

// --- DISPLAY ---
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

// --- SETUP ---
void setup() {
  Serial.begin(115200);
  configurarDisplay();
  conectarWifi();
  String wifiPreference = firebase.getString("wifi/preference");
  if(wifiPreference == "MyPreference"){
     ssid = firebase.getString("wifi/ssid");
     password = firebase.getString("wifi/password");
     conectarWifi();
     Serial.println("Entrou no myPreference");
  }
  firebase.json(true);
}

// --- LOOP ---
void loop() {
  medirTemperaturaUmidade();
  mostrarTemperaturaUmidade();
  publicarTemperaturaUmidadeNoTopico();
  atualizaDadosFirebase();
}

// --- FUNÇÕES AUXILIARES ---

// --- CONECTA NO WIFI ---
void conectarWifi() {
  delay(10);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Conectando ");
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
}

// --- CONFIGURA O DISPLAY ---
void configurarDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

// --- MOSTRA TEMPERATURA E UMIDADE ---
void mostrarTemperaturaUmidade() {
  mostrarMensagemNoDisplay("Temperatura", (temperatura), " C");
  mostrarMensagemNoDisplay("Umidade", (umidade), " %");
}

// --- PUBLICA MENSAGENS ---
void publicarTemperaturaUmidadeNoTopico() {
   client.publish(topicoTemperatura, String(temperatura).c_str(), true);
   client.publish(topicoUmidade, String(umidade).c_str(), true);
}

// --- EXIBE TEMPERATURA E UMIDADE NO DISPLAY ---
void mostrarMensagemNoDisplay(const char* texto1, int medicao, const char* texto2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(texto1);
    display.setTextSize(5);
    display.setCursor(20, 20);
    display.print(medicao);
    display.setTextSize(2);
    display.print(texto2);
    display.display();
    delay(10000);
}

// --- MEDIÇÃO DE TEMPERATURA E UMIDADE ---
void medirTemperaturaUmidade() {
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature(false); // Temos que colocar readTemperature como false para nos retornar a temperatura em graus celcius
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" *C");
  Serial.print(" ");
  Serial.print("Umidade: ");
  Serial.println(umidade);
  delay(10000);
}


// --- ATUALIZA OS VALORES NO FIREBASE ---
void atualizaDadosFirebase() {
   firebase.pushInt("temperaturas", temperatura);
   firebase.pushInt("umidades", umidade);
}
