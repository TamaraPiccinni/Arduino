// Boton sin PULLUP con resistencia externa
// Definimos las variables que representan los pines del Arduino
int buttonPin = 4;  // Pin digital donde se conecta el botón (entrada)
int ledPin = 2;     // Pin digital donde se conecta el LED (salida)
int buttonRead;     // Variable para guardar el valor leído del botón

void setup() {
  Serial.begin(9600);         // Inicia la comunicación serial a 9600 baudios (para ver datos en el Monitor Serial)
  pinMode(buttonPin, INPUT);  // Configura el pin del botón como entrada digital
  pinMode(ledPin, OUTPUT);    // Configura el pin del LED como salida digital
}

void loop() {
  // Lee el estado actual del botón (HIGH o LOW)
  buttonRead = digitalRead(buttonPin);

  // Muestra el valor leído en el Monitor Serial (0 o 1)
  Serial.println(buttonRead);

  delay(100);  // Pequeña pausa de 100 milisegundos para evitar lecturas demasiado rápidas

  // Si el botón está presionado (lee 0 porque no tiene pull-up)
  if (buttonRead == 0) {
    digitalWrite(ledPin, 1);  // Enciende el LED
  } else {
    digitalWrite(ledPin, 0);  // Si no está presionado, apaga el LED
  }
}

