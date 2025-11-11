// Control de brillo con potenciómetro y LED PWM

// Definición de pines
const int potPin = A0;   // Pin analógico donde conectamos el pin central del potenciómetro
const int ledPin = 10;   // Pin digital con PWM (~) donde conectamos el LED (por ejemplo el pin 10)

// Configuración inicial (se ejecuta una sola vez)
void setup() {
  pinMode(ledPin, OUTPUT);  // Configura el LED como salida
  Serial.begin(9600);       // Inicia la comunicación serial para ver los valores del potenciómetro
}

// Bucle principal (se repite continuamente)
void loop() {
  // 1️. Leer el valor del potenciómetro (de 0 a 1023)
  int potValue = analogRead(potPin);

  // 2️. Convertir ese valor al rango que acepta analogWrite (de 0 a 255)
  int brightness = map(potValue, 0, 1023, 0, 255);

  // 3️. Enviar el valor PWM al LED (control de brillo)
  analogWrite(ledPin, brightness);

  // 4️. Mostrar el valor leído y el brillo calculado en el Monitor Serial
  Serial.print("Valor potenciómetro: ");
  Serial.print(potValue);
  Serial.print("  -> Brillo LED: ");
  Serial.println(brightness);

  delay(100);  // Pequeña pausa para evitar que los valores cambien demasiado rápido
}

