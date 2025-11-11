/*
Programa: Semáforo simple con LEDs

Descripción:
Simula el funcionamiento de un semáforo usando 3 LEDs conectados al Arduino.
- LED Rojo en pin 10
- LED Amarillo en pin 9
- LED Verde en pin 8

Pasos principales:
1. Configurar los pines 8, 9 y 10 como salidas.
2. En el loop:
   - Encender rojo por 3 segundos.
   - Encender amarillo por 0.5 segundo (transición antes del verde).
   - Encender verde por 3 segundos.
   - Encender amarillo por 1 segundo (transición antes del rojo).
3. Repetir indefinidamente.

Observaciones:
- HIGH = encendido, LOW = apagado.
- Se pueden ajustar los tiempos de cada luz cambiando los valores de delay().
*/

const int rojo = 12;
const int amarillo = 9;
const int verde = 8;

void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
}

void loop() {
  // Rojo encendido
  digitalWrite(rojo, HIGH);
  digitalWrite(amarillo, LOW);
  digitalWrite(verde, LOW);
  delay(3000);

   // Amarillo antes del verde
  digitalWrite(rojo, LOW);
  digitalWrite(amarillo, HIGH);
  digitalWrite(verde, LOW);
  delay(500);

  // Verde encendido
  digitalWrite(rojo, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(verde, HIGH);
  delay(3000);

  // Amarillo encendido
  digitalWrite(rojo, LOW);
  digitalWrite(amarillo, HIGH);
  digitalWrite(verde, LOW);
  delay(1000);
}
