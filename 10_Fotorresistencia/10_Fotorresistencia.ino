// SENSOR DE LUZ CON LDR Y CONTROL DE BRILLO DE LED

const int sensorPin = A0;  // Pin analógico conectado al punto medio del divisor (LDR + resistencia)
const int ledPin = 9;      // Pin PWM (~) para controlar el brillo del LED

void setup() {
  pinMode(ledPin, OUTPUT);  // LED como salida
  Serial.begin(9600);       // Comunicación serial para observar los valores del sensor
}

void loop() {
  // 1. Leer el valor del sensor de luz (0 a 1023)
  int lightValue = analogRead(sensorPin);

  // 2️. Convertir (mapear) el valor a rango de brillo (0 a 255)
  // Nota: En este circuito, más luz = valor más alto, por eso invertimos el brillo
  int brightness = map(lightValue, 0, 1023, 255, 0);

  // 3️. Ajustar el brillo del LED según la cantidad de luz
  analogWrite(ledPin, brightness);

  // 4️. Mostrar el valor leído en el Monitor Serial
  Serial.print("Valor de luz: ");
  Serial.print(lightValue);
  Serial.print("  -> Brillo LED: ");
  Serial.println(brightness);

  delay(100);  // Pequeña pausa para estabilidad
}


