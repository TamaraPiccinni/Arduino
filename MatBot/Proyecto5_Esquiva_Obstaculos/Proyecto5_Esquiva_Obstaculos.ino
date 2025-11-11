/*
 * ==========================================================
 * PROYECTO 5: ROBOT ESQUIVA-OBSTÁCULOS
 * ==========================================================
 */

/*
 * ==========================================================
 * MÓDULO BASE DE MOVIMIENTO - MATBOT 1.0 
 *
 Incluir este bloque en todos los proyectos con motores.
* Mapeo M0 (Derecho): {D5, D6, D7}
 * Mapeo M1 (Izquierdo): {D2, D3, D4}

 * ==========================================================
 */

// --- Pines Motor Derecho (M0) ---
#define M0_EN_PIN    6  // Pin D6 (Enable/Velocidad)
#define M0_IN1_PIN   5  // Pin D5 (Input 1)
#define M0_IN2_PIN   7  // Pin D7 (Input 2)

// // --- Pines Motor Izquierdo (M1) ---
#define M1_EN_PIN    3  // Pin D3 (Enable/Velocidad)
#define M1_IN1_PIN   2  // Pin D2 (Input 1)
#define M1_IN2_PIN   4  // Pin D4 (Input 2)

void setupMovimiento() {
  pinMode(M0_EN_PIN, OUTPUT);
  pinMode(M0_IN1_PIN, OUTPUT);
  pinMode(M0_IN2_PIN, OUTPUT);
  pinMode(M1_EN_PIN, OUTPUT);
  pinMode(M1_IN1_PIN, OUTPUT);
  pinMode(M1_IN2_PIN, OUTPUT);
}

// --- Funciones Básicas de Movimiento ---
void avanzar(int velocidad) {
  digitalWrite(M0_IN1_PIN, HIGH); 
  digitalWrite(M0_IN2_PIN, LOW); 
  analogWrite(M0_EN_PIN, velocidad);
  digitalWrite(M1_IN1_PIN, HIGH); 
  digitalWrite(M1_IN2_PIN, LOW); 
  analogWrite(M1_EN_PIN, velocidad);
}
void retroceder(int velocidad) {
  digitalWrite(M0_IN1_PIN, LOW); 
  digitalWrite(M0_IN2_PIN, HIGH); 
  analogWrite(M0_EN_PIN, velocidad);
  digitalWrite(M1_IN1_PIN, LOW); 
  digitalWrite(M1_IN2_PIN, HIGH); 
  analogWrite(M1_EN_PIN, velocidad);
}
void girarDerecha(int velocidad) {
  digitalWrite(M1_IN1_PIN, HIGH); 
  digitalWrite(M1_IN2_PIN, LOW); 
  analogWrite(M1_EN_PIN, velocidad);
  digitalWrite(M0_IN1_PIN, LOW); 
  digitalWrite(M0_IN2_PIN, HIGH); 
  analogWrite(M0_EN_PIN, velocidad);
}
void girarIzquierda(int velocidad) {
  digitalWrite(M1_IN1_PIN, LOW); 
  digitalWrite(M1_IN2_PIN, HIGH); 
  analogWrite(M1_EN_PIN, velocidad);
  digitalWrite(M0_IN1_PIN, HIGH); 
  digitalWrite(M0_IN2_PIN, LOW); 
  analogWrite(M0_EN_PIN, velocidad);
}
void detener() {
  analogWrite(M0_EN_PIN, 0);
  analogWrite(M1_EN_PIN, 0);
}


// --- 1. INCLUIR LA BIBLIOTECA ---
// Le decimos al programa que usaremos la biblioteca "NewPing"
// que instalamos para nuestro sensor de 3 pines.
#include <NewPing.h>

// --- 2. DEFINICIÓN DE PINES ---
// Aquí definimos los "apodos" para los pines que usaremos.

#define SENSOR_PIN 9      // Pin D9 (Puerto D9), donde está el sensor
#define MAX_DISTANCE 200  // Distancia máxima que medirá el sensor (en cm)

// --- 3. CREAR EL OBJETO SENSOR ---
// Creamos una "variable" especial (un "objeto") de tipo NewPing
// y la llamamos "sonar".
// Le decimos que tanto el pin Trig como el Echo están en el
// MISMO pin (SENSOR_PIN).
NewPing sonar(SENSOR_PIN, SENSOR_PIN, MAX_DISTANCE);

// --- 4. CONFIGURACIÓN INICIAL ---
void setup() {
  // Prepara los pines de los motores (esta función
  // viene de nuestro "Módulo Base")
  setupMovimiento();
  
  // (Opcional) Inicia el monitor serie para poder ver
  // las distancias en la computadora.
  Serial.begin(9600);
}

// --- 5. BUCLE PRINCIPAL ---
void loop() {
  // --- A. MEDIR LA DISTANCIA ---
  // Usamos la función .ping_cm() de la biblioteca NewPing.
  // Esta función hace todo el trabajo (enviar pulso,
  // escuchar el eco, calcular) y nos devuelve un número
  // (la distancia en cm).
  int distancia = sonar.ping_cm();
  
  // (Opcional) Imprimimos el valor en el monitor
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // --- B. LÓGICA DE DECISIÓN (EL "CEREBRO") ---
  
  // Revisamos dos condiciones:
  // 1. ¿La distancia es menor a 20 cm? (¡Obstáculo!)
  // 2. ¿La distancia es mayor a 0? (¡Medición válida!)
  //    (NewPing devuelve 0 si hay un error o no detecta nada)
  if (distancia < 20 && distancia > 0) {
    
    // --- RUTINA DE "ESQUIVAR" ---
    // Si ambas condiciones son verdaderas, ejecutamos esta
    // secuencia de 3 pasos para evitar el choque:

    // a. ¡Frenar!
    // Detiene los motores inmediatamente.
    detener();
    delay(100); // Pausa corta para que el robot se detenga por completo.

    // b. ¡Retroceder!
    // Damos marcha atrás para tomar distancia del obstáculo.
    retroceder(150); // (150 es una velocidad media)
    delay(500);    // Lo hace por medio segundo.

    // c. ¡Girar!
    // Giramos sobre nuestro eje para buscar un nuevo camino.
    girarDerecha(200); // (200 es una velocidad de giro rápida)
    delay(500);    // Lo hace por medio segundo.

  } else {
    
    // --- RUTINA DE "AVANZAR" ---
    // Si no hay ningún obstáculo (distancia > 20 o 0),
    // simplemente seguimos adelante.
    avanzar(180); // (180 es una velocidad de avance normal)
  }
  
  // Damos una pequeña pausa de 50 milisegundos
  // antes de volver a medir. Esto da estabilidad
  // y evita lecturas erráticas del sensor.
  delay(50);
}

