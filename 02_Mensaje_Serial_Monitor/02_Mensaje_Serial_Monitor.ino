/*
Programa: Mensajes por Monitor Serial

Este programa muestra cómo enviar texto desde el Arduino al 
Monitor Serial de la PC.

- Se inicializa la comunicación serial a 9600 baudios.
- En el loop:
   1. Envía los mensajes "Hola Chicos" y "Bienvenido a Arduino".
   2. Espera 1 segundo.
   3. Se detiene con un bucle infinito, por lo que los mensajes 
      aparecen una sola vez.
*/

// Código de prueba: Mensajes por Monitor Serial

void setup() {
  // Iniciar comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Enviar mensajes al Monitor Serial
  Serial.println("Hola Chicos");
  Serial.println("Bienvenido a Arduino");
  
  // Pausa de 1 segundo
  delay(1000);

  // Detener el loop aquí
  while(true) {
    // No hace nada, queda detenido. se muestra sola 1 vez

  }
}
