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
#define M0_EN_PIN 6   // Pin D6 (Enable/Velocidad)
#define M0_IN1_PIN 5  // Pin D5 (Input 1)
#define M0_IN2_PIN 7  // Pin D7 (Input 2)

// // --- Pines Motor Izquierdo (M1) ---
#define M1_EN_PIN 3   // Pin D3 (Enable/Velocidad)
#define M1_IN1_PIN 2  // Pin D2 (Input 1)
#define M1_IN2_PIN 4  // Pin D4 (Input 2)

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

void setup() {
  setupMovimiento();  // Llama a la configuración de pines
}

void loop() {

  // Secuencia de prueba (velocidad 200 de 255)
  avanzar(200);
  delay(2000);  // Avanza por 2 segundos

  retroceder(200);
  delay(2000);  // Retrocede por 2 segundos

  girarDerecha(200);
  delay(1000);  // Gira a la derecha por 1 segundo

  girarIzquierda(200);
  delay(1000);  // Gira a la izquierda por 1 segundo

  detener();
  delay(3000);  // Detenido por 3 segundos
}
