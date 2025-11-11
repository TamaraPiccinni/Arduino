/*
 * Código mejorado y comentado para Cesto de Basura Automático
 *
 * Componentes:
 * - Arduino UNO
 * - Servomotor (ej. SG90)
 * - Sensor ultrasónico HC-SR04
 *
 * Conexiones:
 * - Servo (PIN_SERVO): Pin 6 (Cable Naranja/Amarillo)
 * - Sensor Trig (PIN_TRIG): Pin 9
 * - Sensor Echo (PIN_ECHO): Pin 10
 * - VCC (Servo y Sensor): 5V
 * - GND (Servo y Sensor): GND
 *
 * Problemas corregidos del código original:
 * 1. La lógica de apertura/cierre estaba invertida. Ahora primero abre, espera y luego cierra.
 * 2. Se añadieron constantes (const int) para hacer más fácil la configuración.
 * 3. Se añadió un "retraso de enfriamiento" después de cerrar
 * para evitar que el sensor detecte la mano al retirarse y se vuelva a abrir inmediatamente.
 */

// Incluir la librería para controlar el servomotor
#include <Servo.h>

// --- Definición de Pines ---
// Usar 'const int' es una buena práctica para pines que no van a cambiar
const int PIN_SERVO = 6;  // Pin PWM donde se conecta el servo (el pin ~6 es PWM)
const int PIN_TRIG = 9;   // Pin TRIG del sensor ultrasónico
const int PIN_ECHO = 10;  // Pin ECHO del sensor ultrasónico

// --- Configuración de Comportamiento ---
// Puedes ajustar estos valores fácilmente
const int DISTANCIA_ACTIVACION_CM = 20; // Distancia (en cm) para que se abra el cesto (tu original era 10)
const int POS_ABIERTO = 90;             // Ángulo del servo cuando la tapa está ABIERTA
const int POS_CERRADO = 0;              // Ángulo del servo cuando la tapa está CERRADA
const int TIEMPO_ESPERA_ABIERTO_MS = 3000; // Milisegundos que la tapa queda abierta (3 segundos)
const int VELOCIDAD_MOVIMIENTO_MS = 15;  // Delay para la velocidad del servo (más bajo = más rápido)
const int RETRASO_ENTRE_LECTURAS_MS = 100;// Delay al final del loop para estabilizar la lectura

// --- Variables Globales ---
Servo servoMotor; // Crear un objeto 'servo' para controlar
long duracion;    // Variable para almacenar el tiempo del pulso del eco
int distancia;    // Variable para almacenar la distancia calculada en cm

void setup() {
  // Configurar el servomotor
  servoMotor.attach(PIN_SERVO);  // Conectar el objeto servo al pin que definimos
  servoMotor.write(POS_CERRADO); // Asegurarse de que el cesto empiece CERRADO

  // Configurar los pines del sensor
  pinMode(PIN_TRIG, OUTPUT); // Trig es un pin de SALIDA (envía el pulso)
  pinMode(PIN_ECHO, INPUT);  // Echo es un pin de ENTRADA (recibe el pulso)

  // Iniciar la comunicación serial para depuración
  // Puedes ver los mensajes en el "Monitor Serial" del IDE de Arduino
  Serial.begin(9600);
  Serial.println("Sistema de cesto automático iniciado.");
}

void loop() {
  // --- 1. Medición de Distancia ---

  // Para hacer una medición limpia, primero ponemos el pin TRIG en bajo (LOW)
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2); // Espera corta de 2 microsegundos

  // Enviamos el pulso de disparo: un pulso ALTO (HIGH) de 10 microsegundos
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW); // Apagamos el pulso

  // Leemos el tiempo que tarda en volver el eco (el pin ECHO se pondrá en ALTO)
  // pulseIn() mide ese tiempo en microsegundos y lo guarda en 'duracion'
  duracion = pulseIn(PIN_ECHO, HIGH);

  // Calculamos la distancia en centímetros
  // Fórmula: (tiempo * velocidad_del_sonido) / 2 (porque es ida y vuelta)
  // (duracion * 0.034 cm/µs) / 2
  distancia = duracion * 0.034 / 2;

  // Imprimir la distancia en el Monitor Serial (muy útil para ver si el sensor funciona bien)
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // --- 2. Lógica de Apertura/Cierre ---

  // Comprobar si la distancia medida es MENOR que la distancia de activación
  // Y también comprobar que la distancia no sea 0 (un error común de lectura del sensor)
  if (distancia < DISTANCIA_ACTIVACION_CM && distancia > 0) {
    
    Serial.println("Objeto detectado! Abriendo tapa...");
    
    // ABILR LA TAPA:
    // Mover el servo suavemente desde la posición CERRADO hasta ABIERTO
    // Usamos un 'for' para que el movimiento no sea brusco
    for (int pos = POS_CERRADO; pos <= POS_ABIERTO; pos++) {
      servoMotor.write(pos); // Mover el servo a la posición 'pos'
      delay(VELOCIDAD_MOVIMIENTO_MS); // Pequeña pausa para un movimiento suave
    }

    // MANTENER ABIERTO:
    // Esperar el tiempo configurado (3 seg) mientras la tapa está abierta
    delay(TIEMPO_ESPERA_ABIERTO_MS);

    // CERRAR LA TAPA:
    // Mover el servo desde la posición ABIERTO de vuelta a CERRADO
    Serial.println("Cerrando tapa...");
    for (int pos = POS_ABIERTO; pos >= POS_CERRADO; pos--) {
      servoMotor.write(pos);
      delay(VELOCIDAD_MOVIMIENTO_MS);
    }

    // "ENFRIAMIENTO" (Cooldown):
    // Esperar 1 segundo (1000 ms) DESPUÉS de cerrar antes de volver a medir.
    // Esto es MUY IMPORTANTE para evitar que el sensor detecte tu mano
    // mientras la retiras y vuelva a abrir la tapa inmediatamente.
    Serial.println("Cesto cerrado. Esperando...");
    delay(1000); 
  }

  // Pequeño retraso al final de cada ciclo del loop
  // Esto evita que el sensor esté midiendo constantemente y da estabilidad.
  delay(RETRASO_ENTRE_LECTURAS_MS);
}