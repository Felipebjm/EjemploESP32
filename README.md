# Código de ejemplo para TTGO ESP32
### Ejemplo con Arduino IDE, ESP32 de la marca TTGO con pantalla IPS y sensor DHT11

## Funcionamiento
- Los datos de temperatura y humedad se muestran en la pantalla y por prints de consola
- Cada cierto tiempo un LED parpadea 

## Librerías necesarias
- DHT Sensor Library
- Adafruit Unified Sensor Lib
- TFT_eSPI

## Configuración de la librería TFT_eSPI
1. Vaya a Documentos/Arduino/libraries/TFT_eSPI
2. En la carpeta TFT_eSPI ingrese al archivo User_Setup_Select
3. Comente la línea 27 que dice: #include <User_Setup.h>
4. Descomente la línea 58 que dice: #include <User_Setups/Setup25_TTGO_T_Display.h>
5. Guarde el archivo 

## Instrucciones
1. Seleccionar como placa el ESP32 Dev Module
2. Configurar la velocidad de transmisión en 9600 baud


## Cableado
- Conectar el LED y la alimentación del DHT11 a los 3.3V del ESP32
- DHT11: GPIO 15
- LED: GPIO 2 (Conectar resistencia de 1k)


