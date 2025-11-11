// Boton con PULLUP
// Definimos las variables que representan los pines del Arduino
const int buttonPin = 4;  // Pin digital donde se conecta el botón (entrada)
const int ledPin = 2;     // Pin digital donde se conecta el LED (salida)

void setup() {
  Serial.begin(9600);                // Inicia la comunicación serial a 9600 baudios (para ver los valores en el Monitor Serial)
  pinMode(buttonPin, INPUT_PULLUP);  // Activa la resistencia interna pull-up: el pin lee HIGH por defecto y LOW al presionar
  pinMode(ledPin, OUTPUT);           // Configura el pin del LED como salida
}

void loop() {
  // Lee el estado actual del botón (HIGH o LOW)
  int estado = digitalRead(buttonPin);

  // Muestra el valor leído en el Monitor Serial (1 = sin presionar, 0 = presionado)
  Serial.println(estado);

  // Como usamos INPUT_PULLUP, el botón está "al revés":
  // HIGH (sin presionar) → !estado = 0 → LED apagado
  // LOW (presionado)     → !estado = 1 → LED encendido
  digitalWrite(ledPin, !estado);  // Enciende el LED al presionar

  delay(200);  // Pausa para evitar lecturas demasiado rápidas
}


