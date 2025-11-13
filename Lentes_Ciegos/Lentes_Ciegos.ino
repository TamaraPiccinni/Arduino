/*
 * PROYECTO: LENTES DE ASISTENCIA PARA NO VIDENTES
 * Placa: NodeMCU (ESP8266)
 * Sensor: HC-SR04
 * Autor: [Tu Nombre/Nombre de la Escuela]
 */

// --- Definición de Pines ---
// Usamos los nombres de los pines de la placa (D1, D2, D5)
const int PIN_TRIG = 5; // GPIO5 - Pin "Trig" del sensor
const int PIN_ECHO = 27; // GPIO4 - Pin "Echo" del sensor
const int PIN_BUZZER = 14; // GPIO14 - Pin positivo del buzzer

// --- Constantes del Proyecto ---
// Distancia máxima (en cm) a la que queremos detectar.
// Más allá de esto, los lentes estarán en silencio.
const int DISTANCIA_MAXIMA = 200; // 2 metros

// Distancia mínima (en cm) para la alerta más rápida.
const int DISTANCIA_MINIMA = 10; 

// --- Variables Globales ---
long duracion; // Variable para guardar el tiempo del pulso ultrasónico
int distancia_cm; // Variable para guardar la distancia calculada

void setup() {
  // Inicializamos la comunicación serial (para pruebas en la PC)
  Serial.begin(115200); 
  
  // Configuramos los pines
  pinMode(PIN_TRIG, OUTPUT); // El pin Trig envía un pulso
  pinMode(PIN_ECHO, INPUT);  // El pin Echo recibe un pulso
  pinMode(PIN_BUZZER, OUTPUT); // El pin Buzzer envía sonido
  
  Serial.println("Sistema de Lentes iniciado. Esperando detección...");
}

void loop() {
  // 1. Medir la distancia
  distancia_cm = medirDistancia();

  // 2. Imprimir la distancia en el monitor (para depuración)
  Serial.print("Distancia: ");
  Serial.print(distancia_cm);
  Serial.println(" cm");

  // 3. Lógica del Sonido
  if (distancia_cm <= DISTANCIA_MAXIMA && distancia_cm > 0) {
    // Si el objeto está dentro del rango...
    
    // Mapeamos la distancia a una pausa.
    // - Si está muy cerca (10cm), la pausa es corta (50ms).
    // - Si está lejos (200cm), la pausa es larga (1000ms).
    int pausa = map(distancia_cm, DISTANCIA_MINIMA, DISTANCIA_MAXIMA, 50, 1000);

    // Hacemos un "BIP"
    // tone(pin, frecuencia, duracion_del_bip)
    tone(PIN_BUZZER, 1000, 100); // Un bip de 1000Hz por 100ms
    
    // Esperamos el tiempo de pausa calculado
    delay(pausa); 

  } else {
    // Si no hay nada en el rango, nos aseguramos de que el buzzer esté apagado.
    noTone(PIN_BUZZER);
    delay(100); // Una pequeña pausa para no saturar el loop
  }
}

/**
 * @brief Mide la distancia con el sensor HC-SR04.
 * @return La distancia calculada en centímetros.
 */
int medirDistancia() {
  // Aseguramos que el pin Trig esté apagado
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  // Enviamos el pulso ultrasónico
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10); // El pulso dura 10 microsegundos
  digitalWrite(PIN_TRIG, LOW);

  // Medimos el tiempo que tarda en volver el eco
  // pulseIn() mide el tiempo (en microsegundos) que el pin Echo está en ALTA
  duracion = pulseIn(PIN_ECHO, HIGH);

  // Calculamos la distancia
  // Fórmula: (tiempo * velocidad_del_sonido) / 2
  // Velocidad del sonido = 0.034 cm/microsegundo
  return (duracion * 0.034) / 2;
}




