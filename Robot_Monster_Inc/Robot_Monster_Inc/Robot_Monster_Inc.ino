/*
 * ==========================================================
 * PROYECTO: MONSTERS INC. (Versión 8.2 - "Avance Recto Calibrado")
 * OBJETIVO: Misión "Solo Ida" funcional.
 *
 * ¡¡NUEVOS CAMBIOS!!
 * 1. (Calibración de Motores): Se crean dos variables de
 * velocidad (IZQ y DER) para corregir la desviación.
 * 2. Se frena el motor DERECHO (de 160 a 155) para
 * evitar que el robot gire a la IZQUIERDA.
 * ==========================================================
 */

// --- 1. BIBLIOTECAS ---
#include <NewPing.h> // Para el sensor de ultrasonido

// --- 2. DEFINICIÓN DE PINES (Hardware MatBot 1.0) ---
#define M0_EN_PIN    6  // Pin D6 (Velocidad M0)
#define M0_IN1_PIN   5  // Pin D5 (Dirección M0)
#define M0_IN2_PIN   7  // Pin D7 (Dirección M0)
#define M1_EN_PIN    3  // Pin D3 (Velocidad M1)
#define M1_IN1_PIN   2  // Pin D2 (Dirección M1)
#define M1_IN2_PIN   4  // Pin D4 (Dirección M1)

// --- 3. DEFINICIÓN DE SENSORES (¡SOLO ULTRASÓNICO!) ---
#define SENSOR_PIN      13  // Puerto Digital D13
#define MAX_DISTANCE    200 // Distancia máxima a medir (cm)

// --- 4. CALIBRACIÓN Y VARIABLES GLOBALES ---

// ========================================================
// ¡¡AJUSTA ESTOS VALORES!!
// ========================================================
int distanciaObstaculo = 15;  // (15 cm)
int TIEMPO_SUSTO = 3000;  // (3 segundos)
int TIEMPO_CIEGO = 2000; // (2 segundos)
// ========================================================

int estadoDelRobot = 0;       // 0=Esperando, 1=Yendo, 2=Fin
int contadorObstaculos = 0; // Contador para el filtro anti-ruido
int contadorPuertaAbierta = 0; // Contador para "debounce"

// --- 5. CREAR EL OBJETO SENSOR ---
NewPing sonar(SENSOR_PIN, SENSOR_PIN, MAX_DISTANCE);

// --- 5.1 PROTOTIPOS DE FUNCIÓN ---
void setupMovimiento();
void avanzar(int velocidad);
void detener();

// --- 6. SETUP (Configuración Inicial) ---
void setup() {
  setupMovimiento(); 
  Serial.begin(9600); 
  Serial.println("Iniciando... Estado 0: Esperando Puerta.");
}

// --- 7. BUCLE PRINCIPAL (¡¡LÓGICA MEJORADA!!) ---
void loop() {
  int distancia = sonar.ping_cm();
  
  // --- Lógica del Filtro Anti-Ruido (para la "cama") ---
  if (distancia < distanciaObstaculo && distancia > 0) {
    contadorObstaculos++; // Aumentamos el contador
  } else {
    contadorObstaculos = 0; // Si no vemos nada, reseteamos el contador
  }
  
  // --- Lógica de Estados ---
  switch (estadoDelRobot) {
    
    case 0: // ESTADO 0: ESPERANDO
      // ¡¡LÓGICA DE PUERTA MEJORADA!!
      if (distancia > distanciaObstaculo || distancia == 0) {
        contadorPuertaAbierta++; // Vemos la puerta abierta
      } else {
        contadorPuertaAbierta = 0; // Vemos la puerta cerrada
        detener(); // Asegúrate de estar quieto
      }

      // Debe ver la puerta abierta 5 veces seguidas (aprox 250ms)
      if (contadorPuertaAbierta >= 5) {
        Serial.println("¡Puerta abierta! (Verificado)");
        Serial.println("Estado 1: Yendo... (Ignorando sensor por 2 seg)");
        
        // ¡¡TIEMPO CIEGO!!
        avanzar(1); // Arranca
        delay(TIEMPO_CIEGO); // Avanza "ciego" por 2 seg para evitar ruido
        
        estadoDelRobot = 1; // Ahora sí, empieza a buscar la cama
      }
      break; 
      
    case 1: // ESTADO 1: YENDO (Buscando la cama)
      // Si ve un obstáculo 3 veces seguidas (la "cama")
      if (contadorObstaculos >= 3) { 
        Serial.println("¡Cama detectada! Asustando...");
        detener();
        delay(TIEMPO_SUSTO); 
        estadoDelRobot = 2; // Pasa al estado final
        Serial.println("Estado 2: Misión cumplida (Frenado).");
      } else {
        // No hay obstáculo, solo AVANZA RECTO
        avanzar(1);
      }
      break; 
      
    case 2: // ESTADO 2: FIN
      // No hacer nada para siempre
      detener();
      break; 
  }
  delay(50); // Pausa de estabilidad
}

// --- 9. FUNCIONES DE MOVIMIENTO (¡¡CALIBRACIÓN DE AVANCE!!) ---

// ========================================================
// ¡¡AJUSTA ESTAS DOS VELOCIDADES!!
// Si el robot gira a la IZQUIERDA -> BAJA el número DERECHO
// Si el robot gira a la DERECHA -> BAJA el número IZQUIERDO
// ========================================================
int VELOCIDAD_AVANCE_IZQ = 145; // Motor (M1) Cambio a  140 para evitar que gire por diferencia de potencia
int VELOCIDAD_AVANCE_DER = 160; // Motor (M0)
// ========================================================


void setupMovimiento() {
  pinMode(M0_EN_PIN, OUTPUT);
  pinMode(M0_IN1_PIN, OUTPUT);
  pinMode(M0_IN2_PIN, OUTPUT);
  pinMode(M1_EN_PIN, OUTPUT);
  pinMode(M1_IN1_PIN, OUTPUT);
  pinMode(M1_IN2_PIN, OUTPUT);
}

// Lógica de AVANZAR (M1 INVERTIDO y CALIBRADO)
void avanzar(int velocidad) {
  // Motor Derecho (M0) - Avanza (HIGH/LOW)
  digitalWrite(M0_IN1_PIN, HIGH);
  digitalWrite(M0_IN2_PIN, LOW);
  analogWrite(M0_EN_PIN, VELOCIDAD_AVANCE_DER); // ¡Usa la variable DERECHA!
  // Motor Izquierdo (M1) - Avanza (LOW/HIGH - CORREGIDO)
  digitalWrite(M1_IN1_PIN, LOW);
  digitalWrite(M1_IN2_PIN, HIGH);
  analogWrite(M1_EN_PIN, VELOCIDAD_AVANCE_IZQ); // ¡Usa la variable IZQUIERDA!
}

// Lógica de DETENER
void detener() {
  analogWrite(M0_EN_PIN, 0);
  analogWrite(M1_EN_PIN, 0);
}