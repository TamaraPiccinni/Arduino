// SENSOR ULTRASÓNICO HC-SR04 + LED DE ALERTA
// Pines del sensor y salida
const int TRIG = 13;  // Trigger: genera el pulso ultrasónico
const int ECHO = 12;  // Echo: recibe el pulso reflejado
const int LED = 8;    // LED indicador de proximidad
int umbral = 20;     // Distancia de alerta en cm

void setup() {
  Serial.begin(9600);       // Inicia comunicación serial para monitorear datos
  pinMode(TRIG, OUTPUT);    // Trigger como salida
  pinMode(ECHO, INPUT);     // Echo como entrada
  pinMode(LED, OUTPUT);     // LED como salida
  digitalWrite(TRIG, LOW);  // Asegura que el Trigger empiece en LOW
}

void loop() {
  long echoTime;   // Tiempo que tarda el eco (en microsegundos)
  float distance;  // Distancia calculada (en centímetros)

  // 1. Enviar un pulso ultrasónico de 10 µs(microsegundos, valor recomendado)
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // 2. Leer el tiempo que tarda el eco en volver
  echoTime = pulseIn(ECHO, HIGH);

  // 3. Calcular distancia (usando velocidad del sonido)
  distance = echoTime * 0.0343 / 2;  // Conversión a centímetros

  // 4. Mostrar distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance, 0);
  Serial.println(" cm");

  // 5. Encender LED si la distancia es menor a 20 cm
  if (distance < umbral) {
    digitalWrite(LED, HIGH);  // Objeto cerca → LED encendido
  } else {
    digitalWrite(LED, LOW);   // Objeto lejos → LED apagado
  }

  delay(500);  // Pausa antes de repetir, modificar si es mas lejos mas delay
}

