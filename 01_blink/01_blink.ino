/*
Programa Blink
---------------
Este programa enciende y apaga el LED integrado en la placa Arduino (pin 13)
a intervalos regulares.

Funcionamiento:
1. En setup():
   - Se configura el pin 13 como salida.
2. En loop():
   - Se enciende el LED (HIGH).
   - Se espera 1 segundo (delay de 1000 ms).
   - Se apaga el LED (LOW).
   - Se espera 1 segundo más.
3. Este ciclo se repite indefinidamente, haciendo parpadear el LED.

Es el ejemplo básico de Arduino y se usa como prueba inicial
para comprobar que la placa funciona correctamente.
*/

// No es obligatorio en el IDE incluir Arduino.h, 
// pero no afecta si lo dejas
#include <Arduino.h>

// Blink: enciende y apaga el LED integrado en el pin 13
void setup() {
  pinMode(13, OUTPUT); // Configura el pin 13 como salida
}

void loop() {
  digitalWrite(13, HIGH); // Enciende el LED
  delay(1000);            // Espera 1 segundo
  digitalWrite(13, LOW);  // Apaga el LED
  delay(1000);            // Espera 1 segundo
}
