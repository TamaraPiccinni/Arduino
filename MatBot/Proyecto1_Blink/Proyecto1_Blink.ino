#define LED_INTEGRADO 13 // (En el Nano, también se puede usar LED_BUILTIN)

void setup() {
  pinMode(LED_INTEGRADO, OUTPUT);
}

void loop() {
  digitalWrite(LED_INTEGRADO, HIGH); // Encender LED
  delay(1000);                      // Esperar 1 segundo
  digitalWrite(LED_INTEGRADO, LOW);  // Apagar LED
  delay(1000);                      // Esperar 1 segundo
}
