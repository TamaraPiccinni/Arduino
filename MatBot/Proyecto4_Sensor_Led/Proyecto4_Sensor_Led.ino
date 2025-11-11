/*
 * ==========================================================
 * Proyecto 4: Radar (Versión para sensor de 3 pines)
 *
 * Este código usa la biblioteca "NewPing", que es necesaria
 * porque nuestro cable-adaptador usa 1 solo pin para
 * Trig (enviar) y Echo (recibir).
 * ==========================================================
 */

// 1. INCLUIR LA BIBLIOTECA
// Primero, le decimos al programa que usaremos las herramientas
// que descargamos (la biblioteca NewPing).
#include <NewPing.h>

// 2. DEFINIR LOS PINES
// Definimos los "apodos" para los pines que usaremos.
// (Todos son puertos seguros, ¡sin conflictos!)
#define SENSOR_PIN 9      // Pin D9 (Puerto D9), donde conectamos el sensor
#define LED_RADAR_PIN A5  // Pin A5 (Puerto S5), donde conectamos el LED
#define MAX_DISTANCE 200  // Le decimos al sensor que no mida más allá de 200cm

// 3. CREAR EL OBJETO SENSOR (¡La "Función" Especial!)
// Aquí es donde ocurre la magia de NewPing.
// Creamos una "variable" especial (un "objeto") de tipo NewPing
// y la llamamos "sonar".
//
// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//
// Como nuestro sensor usa el MISMO pin para ambos, le pasamos
// SENSOR_PIN (o sea, 8) en los dos primeros lugares.
NewPing sonar(SENSOR_PIN, SENSOR_PIN, MAX_DISTANCE);

void setup() {
  // Configura el pin A5 como salida para el LED
  pinMode(LED_RADAR_PIN, OUTPUT); 
  Serial.begin(9600); // Inicia la comunicación para ver en la PC
}

void loop() {
  // 4. LLAMAR A LA "FUNCIÓN" DE NEWPING
  // A diferencia de la versión anterior, no necesitamos
  // una función "leerDistancia()" separada.
  // La biblioteca NewPing ya la tiene adentro.
  //
  // Para obtener la distancia, simplemente "llamamos"
  // a la función .ping_cm() de nuestro objeto "sonar".
  // La biblioteca se encarga de todo (el pulso, la escucha,
  // el cálculo) y nos devuelve un número.
  int distancia = sonar.ping_cm();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("cm");

  // Si el sensor no detecta nada, devuelve 0.
  // Lo cambiamos a 100 para que el LED no parpadee súper rápido.
  if (distancia <= 0 || distancia > 100) {
    distancia = 100;
  }

  // Mapear la distancia (1-100cm) a un tiempo de parpadeo (10-1000ms)
  int tiempoDelay = map(distancia, 1, 100, 10, 1000);

  // Hacer el parpadeo con el LED EXTERNO
  digitalWrite(LED_RADAR_PIN, HIGH);
  delay(tiempoDelay);
  digitalWrite(LED_RADAR_PIN, LOW);
  delay(tiempoDelay);
}