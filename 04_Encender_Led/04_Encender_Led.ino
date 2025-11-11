/*Encender led
Programa: Blink en pin 8

Descripción:
Hace parpadear un LED conectado al pin 8 del Arduino.

Pasos principales:
1. Se configura el pin 8 como salida con `pinMode(8, OUTPUT);`.
2. En el loop:
   - Enciende el LED con `digitalWrite(8, HIGH);`.
   - Espera 1 segundo (`delay(1000);`).
   - Apaga el LED con `digitalWrite(8, LOW);`.
   - Espera 0,5 segundos (`delay(500);`).
3. El ciclo se repite indefinidamente, generando el parpadeo.

Observaciones:
- HIGH = 5V → LED encendido.
- LOW = 0V → LED apagado.
- Los valores de delay pueden modificarse para cambiar la velocidad del parpadeo.
*/

void setup() {
  // Configuro el pin 8 como salida (donde conectaré el LED o la luz)
  pinMode(8, OUTPUT);
}

void loop() {
  // Enciendo el LED (aplico voltaje al pin 8)
  digitalWrite(8, HIGH);
  
  // Espero 1 segundo (1000 milisegundos)
  delay(1000);
  
  // Apago el LED (pongo el pin 8 en 0V)
  digitalWrite(8, LOW);
  
  // Espero medio segundo (500 milisegundos)
  delay(500);
}
