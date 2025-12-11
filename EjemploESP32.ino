// Requiere instalar las siguientes librerias:
// - DHT Sensor Library 
// - Adafruit Unified Sensor Lib
// - TFT_eSPI

#include "DHT.h"
#include <TFT_eSPI.h>

// --Pines--
#define DHTPIN 15 
#define LED_PIN 2

#define DHTTYPE DHT11   

//Por default se incializa el led encendido
//False=encendido True=apagado
bool estadoLED = false;

// Inicializar el sensor DHT11
// Se crea un objeto llamado dht de la clase DHT (clase incluida en la libreria)
DHT dht(DHTPIN, DHTTYPE);

//Inicializar la pantalla
TFT_eSPI tft = TFT_eSPI(135, 240);

void setup() {
  Serial.begin(9600); //La velocidad de comunicacion
  Serial.println(F("DHTxx test!"));

  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  
  // --Mensaje incial de la pantalla--
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(2); 
  tft.setCursor(0, 0);
  tft.drawString("Hola mundo!", tft.width() / 2, tft.height() / 2 - 18);
  tft.drawString("__________", tft.width() / 2, tft.height() / 2 );
  tft.setTextColor(TFT_BLUE);
  tft.drawString("Ejemplo DHT11", tft.width() / 2, tft.height() / 2 + 18);
  tft.drawString(":D", tft.width() / 2, tft.height() / 2 + 50); 
}

void loop() {
   
  //Timer entre las mediciones y los prints
  delay(500);

  estadoLED = !estadoLED;               // Cambia estado del led (encido o apagado)
  digitalWrite(LED_PIN, estadoLED);     // Lo aplica

  // --Lectura de datos del sensor--
  float humedad = dht.readHumidity();
  float temperaturaCel = dht.readTemperature();
  float temperaturaFah = dht.readTemperature(true);

  // --Verificacion y mensaje de error-- 
  if (isnan(humedad) || isnan(temperaturaCel) || isnan(temperaturaFah)) {
    Serial.println(F("Fallo al leer datos del sensor"));
    return;
  }

  // Cálculos de índices de calor
  float indiceCel = dht.computeHeatIndex(temperaturaCel, humedad);
  float indiceFah = dht.computeHeatIndex(temperaturaFah, humedad, false);

  // --Prints de consola--
  Serial.print(F("Humedad: "));
  Serial.print(humedad);
  Serial.print(F("%  Temperatura: "));
  Serial.print(temperaturaCel);
  Serial.print(F("°C "));
  Serial.print(temperaturaFah);
  Serial.print(F("°F  índice de calor: "));
  Serial.print(indiceCel);
  Serial.print(F("°C "));
  Serial.print(indiceFah);
  Serial.println(F("°F"));

  if(estadoLED == true){
    Serial.println("Led apagado");
  } else{
    Serial.println("led encencido");
  }

  // --Prints de la pantalla--
  tft.fillScreen(TFT_RED);
  
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Temperatura:", tft.width() / 2, 30);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(temperaturaCel) + " C", tft.width() / 2, 50);

  tft.setTextColor(TFT_BLUE);
  tft.drawString("Humedad:", tft.width() / 2, 80);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(humedad) + " %", tft.width() / 2, 100);
}
