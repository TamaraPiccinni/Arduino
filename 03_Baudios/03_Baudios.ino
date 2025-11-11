/*
Programa: Comunicación Serial a distintas velocidades (baudios)

Descripción:
Este programa muestra cómo funciona la comunicación serial entre el Arduino y la PC,
probando diferentes velocidades de transmisión (baudios).

Pasos principales:
1. Se inicia la comunicación serial con `Serial.begin(115200);`.
   - El número indica la velocidad de transmisión (bits por segundo).
   - Ejemplos: 9600 (lento y confiable), 115200 (muy rápido).
2. En el loop, el Arduino envía el mensaje "Mensaje de prueba" al Monitor Serial.
3. El mensaje se envía cada 0,1 segundos gracias a `delay(100)`.

Observaciones:
- Tanto el Arduino como el Monitor Serial deben estar configurados en la misma velocidad.
- Baudios más altos → comunicación más rápida, pero más propensa a errores.
- Baudios más bajos → más lenta, pero más estable.

Valores comunes de baudios en Arduino
Velocidad	Uso típico
300	   Muy lento, casi nunca se usa
9600	 Tutoriales, ejemplos, comunicación confiable
19200	 Comunicación más rápida, aún confiable
57600	 Serial rápido, buena para datos grandes
115200 Muy rápido, útil para depuración o envío de muchos datos*/




void setup() {
  // Cambiá la velocidad a probar: 9600 o 115200
  Serial.begin(115200);  
}

void loop() {
  Serial.println("Mensaje de prueba");
  delay(100);  // Envía un mensaje cada 0.1 segundos
  
}
