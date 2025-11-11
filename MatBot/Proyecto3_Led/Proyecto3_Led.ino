/*
 * ==========================================================
 * Proyecto 3: Blink con LED Externo
 * ==========================================================
 */

// Usaremos el pin A5 (PUERTO S5) como si fuera un pin digital.
// (Los pines Analógicos A0-A5 también pueden usarse como Digitales)


#define LED_EXTERNO_PIN A5 // Pin de señal del Puerto S5

void setup() {
  // Configurar el pin A5 como SALIDA
  pinMode(LED_EXTERNO_PIN, OUTPUT);
}

void loop() {
  // Parpadeo clásico (Blink)
  digitalWrite(LED_EXTERNO_PIN, HIGH); // Encender
  delay(1000);                         // Esperar 1 segundo
  digitalWrite(LED_EXTERNO_PIN, LOW);  // Apagar
  delay(1000);                         // Esperar 1 segundo
}
