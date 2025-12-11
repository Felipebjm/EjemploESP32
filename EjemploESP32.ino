// Requiere instalar las siguientes librerias:
// - DHT Sensor Library 
// - Adafruit Unified Sensor Lib

#include "DHT.h"

#define DHTPIN 15     // Pin conectado al sensor

#define DHTTYPE DHT11   

// Inicializar el sensor DHT11
// Se crea un objeto llamado dht de la clase DHT (clase incluida en la libreria)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); //La velocidad de comunicacion
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Timer de 2 segundo entre mediciones
  delay(2000);

  //Lectura de datos del sensor
  float humedad = dht.readHumidity();
  float temperaturaCel = dht.readTemperature();
  float temperaturaFah = dht.readTemperature(true);

  // Verificacion y mensaje de error 
  if (isnan(humedad) || isnan(temperaturaCel) || isnan(temperaturaFah)) {
    Serial.println(F("Fallo al leer datos del sensor"));
    return;
  }

  // Cálculos de índices de calor
  float indiceCel = dht.computeHeatIndex(temperaturaCel, humedad);
  float indiceFah = dht.computeHeatIndex(temperaturaFah, humedad, false);

  // Prints
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
}
