/* Encender Led usando Variables
Este programa hace parpadear un LED conectado al pin 8 del Arduino.

- Primero se configura el pin 8 como salida.
- En el loop:
   1. Se enciende el LED (digitalWrite en HIGH).
   2. Se mantiene encendido por el tiempo definido en "tiempoEncendido".
   3. Se apaga el LED (digitalWrite en LOW).
   4. Se mantiene apagado por el tiempo definido en "tiempoApagado".
- Estos pasos se repiten una y otra vez.

Con las variables "tiempoEncendido" y "tiempoApagado" se puede ajustar 
fácilmente cuánto tiempo permanece prendido o apagado el LED.
*/

// Defino el pin del LED
const int ledPin = 8;  

// Defino tiempos (en milisegundos)
int tiempoEncendido = 1000;  // 1 segundo
int tiempoApagado   = 500;   // 0,5 segundos

void setup() {
  // Configuro el pin como salida
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Enciendo el LED
  digitalWrite(ledPin, HIGH);
  delay(tiempoEncendido);

  // Apago el LED
  digitalWrite(ledPin, LOW);
  delay(tiempoApagado);
}


