#include "BluetoothSerial.h" // Biblioteca para la comunicación Bluetooth
#include "FS.h"              // Usar el sistema de archivos
#include "SPIFFS.h"          // Usar el sistema interno de la ESP32

BluetoothSerial SerialBT;    // Inicializar el Bluetooth

float temperaturaAmbiente, humedad, temperatura, ph; // Definir variables

void setup() {
  // Configuración inicial
  Serial.begin(115200);                // Monitoreo en el puerto serial
  SerialBT.begin("ESP32-Bluetooth");   // Nombre del dispositivo Bluetooth
  randomSeed(analogRead(0));           // Iniciar valores aleatorios
  Serial.println("ESP32 - Fermentación Cacao Iniciada");
}

void loop() {
  // Generar datos aleatorios para simular los sensores
  temperatura = random(20, 35);            // Temperatura interna entre 20°C y 35°C
  humedad = random(60, 80);                // Humedad entre 60% y 80%
  temperaturaAmbiente = random(20, 35);    // Temperatura ambiente entre 20°C y 35°C
  ph = random(5, 7);                       // pH entre 5 y 7

  unsigned long currentTime = millis();    // Tiempo en milisegundos desde que se inició el programa

  // Crear una cadena en formato CSV
  String datosCSV = String(currentTime) + "," + 
                    String(temperatura) + "," + 
                    String(humedad) + "," + 
                    String(temperaturaAmbiente) + "," + 
                    String(ph);

  // Enviar los datos por Bluetooth si hay un cliente conectado
  if (SerialBT.hasClient()) {
    SerialBT.println(datosCSV);            // Enviar los datos a la aplicación en formato CSV
    Serial.println("Enviando: " + datosCSV); // Mostrar en el monitor serie para debug
  }

  // Retraso de 1 segundo antes de enviar los próximos datos
  delay(1000);
}
